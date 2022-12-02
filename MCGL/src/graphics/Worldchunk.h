#pragma once
#include "Chunk.h"

#define MAX_CHUNKS 8

class Worldchunk
{	
public:

private:
	std::array<Chunk, MAX_CHUNKS> chunks;
};

