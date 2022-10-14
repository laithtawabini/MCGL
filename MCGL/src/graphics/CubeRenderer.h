#pragma once

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "../world/Cube.h"
#include "../Texture.h"

#include "../vendor/glm/glm.hpp"

class CubeRenderer
{
public:
	CubeRenderer(const VertexArray& va, const Shader& shader);

	void DrawCube(const glm::vec3& position, Texture& texture);

	void SetVertexArray(VertexArray& va) { m_CubeVA = va; }
	void SetShader(const Shader& shader) { m_Shader = shader; }

private:
	VertexArray m_CubeVA;
	Shader m_Shader;
};

