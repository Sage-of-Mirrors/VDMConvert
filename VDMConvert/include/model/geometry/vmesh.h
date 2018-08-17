#pragma once
#include <assimp/mesh.h>
#include "util/bstream.h"
#include "model/GX_Enums.h"

class VMesh {
private:
	std::string name;
	uint32_t attributes;

	void SetAttributes(aiMesh* mesh);
public:
	VMesh(aiMesh* mesh);
	
	void Write(bStream::CFileStream * writer);
	void WriteName(bStream::CFileStream * writer);
};