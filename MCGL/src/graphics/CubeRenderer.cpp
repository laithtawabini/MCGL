#include "CubeRenderer.h"

Cube cube;

CubeRenderer::CubeRenderer(const VertexArray& va, const Shader& shader)
	: m_CubeVA(va), m_Shader(shader) { }

void CubeRenderer::DrawCube(const glm::vec3& position, Texture& texture)
{
	m_CubeVA.Bind();
	m_Shader.Use();
	texture.Bind();

	glm::mat4 model = glm::translate(glm::mat4(1.0f), position);
	m_Shader.SetUniformMat4("model", model);

	//glDrawArrays(GL_TRIANGLES, 0, facesToRender.size() * 6);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void CubeRenderer::DrawFaceOfCube(const glm::vec3& position, Cube::Face face)
{
	
}


