#pragma once
#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"
#include "vendor/glm/gtc/type_ptr.hpp"

#define CHUNK_XYZ_RANGE 16

class Chunk
{
public:
	
	//a chunk is a set of blocks with unique positions
	//the set is 16 * 16 * 16 size
	//a chunk must have a position in the world, 
};