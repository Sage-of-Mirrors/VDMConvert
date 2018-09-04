#pragma once
#include <assimp/mesh.h>
#include <vector>
#include "util/bstream.h"
#include "model/vertex_data/vvertexdata.h"

class VMesh {
private:
	std::string name;
	uint32_t attributes;
	uint16_t num_faces;
	CArrayT<uint16_t> indices;
	aiVector3D min_bounds;
	aiVector3D max_bounds;

	void SetAttributes(aiMesh * mesh);
	void FindBounds(aiVector3D * positions, int count);
public:
	VMesh(aiMesh* mesh, VVertexData * vtx_data);
	
	void Write(bStream::CFileStream * writer);
	int WritePrimitives(bStream::CFileStream * writer);
	void WriteName(bStream::CFileStream * writer);
};