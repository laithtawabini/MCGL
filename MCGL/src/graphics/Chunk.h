#pragma once

#include <array>
#include "CubeRenderer.h"
#include "Shader.h"
#include <random>
#include <unordered_set>

#define XC 16
#define YC 16
#define ZC 16

enum class BlockType : int {
	AIR, GRASS, DIRT, STONE
};


struct bvec5 {
	bvec5(int x, int y, int z, int texX, int texY, int blockTexture)
	{
		this->x = x;
		this->y = y;
		this->z = z;

		this->texX = texX;
		//up by 32 depending on tilemap selected texture
		this->texY = texY + (32 * (blockTexture - 1));
	}

	GLbyte x, y, z, texX, texY;
};

class Chunk
{
public:
	Chunk(int, int);

	void Update();

	void Render(VertexArray& va, Shader& shader);

	void SetBlockAt(int x, int y, int z);

	auto& GetVertices() { return m_BlocksVertices; }
	std::vector<GLbyte> RetrieveData();

private:
	static std::unordered_set<glm::ivec2> s_OccupiedChunkPositions;
	BlockType m_Blocks[XC][YC][ZC];
	std::vector<bvec5> m_BlocksVertices;
	bool changed;
};

