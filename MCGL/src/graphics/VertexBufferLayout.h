#pragma once
#include <vector>

struct VertexBufferElement
{
	unsigned int countOfValues;
	unsigned int valuesType;
	unsigned int isNormalized;
};

class VertexBufferLayout
{
public:
	VertexBufferLayout() = default;

	/*template <typename T>
	void PushElement(uint32_t layoutIndex, uint32_t nOfValues, uint32_t stride, uint32_t offset)
	{
		m_Elements.push_back({layoutIndex, nOfValues, T, GL_FALSE, stride, offset});
	}*/

	void PushElement(uint32_t type, uint32_t countOfValues) 
	{
		m_Elements.push_back({ countOfValues, type, GL_FALSE });
		m_Stride += countOfValues * sizeof(float);
	}

	const auto& GetElements() const
	{
		return m_Elements;
	}

	uint32_t GetStride() const { return m_Stride; }

private:
	std::vector<VertexBufferElement> m_Elements;
	uint32_t m_Stride;
	uint32_t m_LayoutIndexCount = 0;
};
