#include "Chunk.h"
//std::unordered_set<glm::ivec2> Chunk::s_OccupiedChunkPositions;

Chunk::Chunk(int xStart, int zStart) 
{
	//xStart *= XC;
	//zStart *= ZC;

	/*s_OccupiedChunkPositions.insert(glm::ivec2(xStart, zStart));

	if (s_OccupiedChunkPositions.contains(glm::ivec2(xStart, zStart)))
	{
		std::cout << "Cant load chunk at: (" << xStart << ", " << zStart << ") ALREADY EXISTS!\n";
			return;
	}*/

	memset(m_Blocks, (int)BlockType::DIRT, sizeof(m_Blocks));
	
	for (int x = xStart; x < XC; x++) {
		for (int y = 0; y < YC; y++) {
			for (int z = zStart; z < ZC; z++) {
				m_Blocks[x][y][z] = (BlockType)(rand() % 4);
			}
		}
	}

	changed = true;
}

void Chunk::Render(VertexArray& va, Shader& shader)
{
	if (changed)
		Update();

	va.Bind();
	shader.Use();
	
	// 5 bytes for each vertix 3 for position and 2 for texture
	glDrawArrays(GL_TRIANGLES, 0, m_BlocksVertices.size() * 5);
}



std::vector<GLbyte> Chunk::RetrieveData()
{
	std::cout << m_BlocksVertices.size();

	if (m_BlocksVertices.size() == 0)
	{
		std::cout << "Chunk is empty!";
		exit(-1);
	}

	std::vector<GLbyte> vData;
	vData.reserve(m_BlocksVertices.size() * 5);

	for (auto& vertex : m_BlocksVertices)
	{
		vData.push_back(vertex.x);
		vData.push_back(vertex.y);
		vData.push_back(vertex.z);
		vData.push_back(vertex.texX);
		vData.push_back(vertex.texY);
		//vData.push_back(vertex.blockText);
	}

	return vData;
}


void Chunk::Update()
{
	changed = false;

	m_BlocksVertices.clear();
	//36 because each block has 36 vertices, XC * YC * ZC = number of blocks
	m_BlocksVertices.reserve(XC * YC * ZC * 36);

	for (int x = 0; x < XC; x++) {
		for (int y = 0; y < YC; y++) {
			for (int z = 0; z < ZC; z++) {
				SetBlockAt(x,y,z);
			}
		}
	}

}


void Chunk::SetBlockAt(int x, int y, int z)
{
	if (x >= XC || y >= YC || z >= ZC)
		return;

	if (m_Blocks[x][y][z] == BlockType::AIR)
		return;

	int blockTexture = (uint32_t)m_Blocks[x][y][z];

	//Making sure grass stays on top only
	if (blockTexture == (int)BlockType::GRASS)
		if ((y < YC - 1 && m_Blocks[x][y + 1][z] != BlockType::AIR))
			blockTexture = (int)BlockType::DIRT;

	//everything under represents vertices for 1 cube (block) + pixel texture coardinates and finally, the texture used

	//left face
	if (x == 0 || (x > 0 && m_Blocks[x - 1][y][z] == BlockType::AIR))
	{
		m_BlocksVertices.push_back({ x, y, z + 1,			0,0   , blockTexture });
		m_BlocksVertices.push_back({ x, y, z,				32,0  , blockTexture });
		m_BlocksVertices.push_back({ x, y + 1, z,			32,32 , blockTexture });
		m_BlocksVertices.push_back({ x, y + 1, z,			32,32 , blockTexture });
		m_BlocksVertices.push_back({ x, y + 1, z + 1,		0,32  , blockTexture });
		m_BlocksVertices.push_back({ x, y, z + 1,			0,0   , blockTexture });
	}

	//right face
	if (x == XC - 1 || (x <= (XC - 1) && m_Blocks[x + 1][y][z] == BlockType::AIR))
	{
		m_BlocksVertices.push_back({ x + 1, y, z + 1,		0,0    , blockTexture });
		m_BlocksVertices.push_back({ x + 1, y, z,			32,0   , blockTexture });
		m_BlocksVertices.push_back({ x + 1, y + 1, z,		32,32  , blockTexture });
		m_BlocksVertices.push_back({ x + 1, y + 1, z,		32,32  , blockTexture });
		m_BlocksVertices.push_back({ x + 1, y + 1, z + 1,	0,32   , blockTexture });
		m_BlocksVertices.push_back({ x + 1, y, z + 1,		0,0    , blockTexture });
	}

	//front face // ISSUE
	if (z == 0 || (z > 0 && m_Blocks[x][y][z - 1] == BlockType::AIR))
	{
		m_BlocksVertices.push_back({ x, y, z,				0,0    , blockTexture });
		m_BlocksVertices.push_back({ x + 1, y, z,			32,0   , blockTexture });
		m_BlocksVertices.push_back({ x + 1, y + 1, z,		32,32  , blockTexture });
		m_BlocksVertices.push_back({ x + 1, y + 1, z,		32,32  , blockTexture });
		m_BlocksVertices.push_back({ x, y + 1, z,			0,32   , blockTexture });
		m_BlocksVertices.push_back({ x, y, z,				0,0    , blockTexture });
	}

	
	//back face
	if (z == ZC - 1 || (z < ZC - 1 && m_Blocks[x][y][z + 1] == BlockType::AIR))
	{
		m_BlocksVertices.push_back({ x, y, z + 1,			0,0   , blockTexture });
		m_BlocksVertices.push_back({ x + 1, y, z + 1,		32,0  , blockTexture });
		m_BlocksVertices.push_back({ x + 1, y + 1, z + 1,	32,32 , blockTexture });
		m_BlocksVertices.push_back({ x + 1, y + 1, z + 1,	32,32 , blockTexture });
		m_BlocksVertices.push_back({ x, y + 1, z + 1,		0,32  , blockTexture });
		m_BlocksVertices.push_back({ x, y, z + 1,			0,0   , blockTexture });

	}

	//top face
	if (y == YC - 1 || (y < YC - 1 && m_Blocks[x][y + 1][z] == BlockType::AIR))
	{
		m_BlocksVertices.push_back({ x, y + 1, z,			  64,0  , blockTexture });
		m_BlocksVertices.push_back({ x + 1, y + 1, z,		  96,0  , blockTexture });
		m_BlocksVertices.push_back({ x + 1, y + 1, z + 1,	  96,32 , blockTexture });
		m_BlocksVertices.push_back({ x + 1, y + 1, z + 1,	  96,32 , blockTexture });
		m_BlocksVertices.push_back({ x, y + 1, z + 1,		  64,32 , blockTexture });
		m_BlocksVertices.push_back({ x, y + 1, z,			  64,0  , blockTexture });
	}

	//bottom face
	if (y == 0 || (y > 0 && m_Blocks[x][y - 1][z] == BlockType::AIR))
	{
		m_BlocksVertices.push_back({ x, y, z,				32,0  , blockTexture });
		m_BlocksVertices.push_back({ x + 1, y, z,			64,0  , blockTexture });
		m_BlocksVertices.push_back({ x + 1, y, z + 1,		64,32 , blockTexture });
		m_BlocksVertices.push_back({ x + 1, y, z + 1,		64,32 , blockTexture });
		m_BlocksVertices.push_back({ x, y, z + 1,			32,32 , blockTexture });
		m_BlocksVertices.push_back({ x, y, z,				32,0  , blockTexture });
	}
}