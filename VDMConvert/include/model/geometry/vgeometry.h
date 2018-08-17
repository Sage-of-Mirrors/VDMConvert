#pragma once
#include <assimp/mesh.h>
#include "util/bstream.h"
#include "util/streamutil.h"
#include "util/array.h"
#include "vmesh.h"
#include "model/vertex_data/vvertexdata.h"
#include "model/vertex_data/vvertexattributes.h"

class VGeometry {
private:
	const int id = 1447513428;
	CArrayT<VMesh*> mesh_data;
public:
	VGeometry(aiMesh** meshes, int count, VVertexData * vtx_data);
	~VGeometry();

	void Write(bStream::CFileStream* writer);
};