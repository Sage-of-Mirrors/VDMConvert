#pragma once
#include <assimp/mesh.h>
#include "util/bstream.h"
#include "model/GX_Enums.h"
#include "model/vertex_data/vvertexdata.h"

class VMesh {
private:
	std::string name;
	uint32_t attributes;
	CArrayT<uint16_t> indices;
	aiVector3D min_bounds;
	aiVector3D max_bounds;

	void SetAttributes(aiMesh * mesh);
	void SetIndices(aiMesh * mesh, VVertexData * vtx_data);
	void FindBounds(CArrayT<aiVector3D> positions);
public:
	VMesh(aiMesh* mesh, VVertexData * vtx_data);
	
	void Write(bStream::CFileStream * writer);
	void WritePrimitives(bStream::CFileStream * writer);
	void WriteName(bStream::CFileStream * writer);
};