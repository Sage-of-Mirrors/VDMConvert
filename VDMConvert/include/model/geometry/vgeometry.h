#pragma once
#include <assimp/mesh.h>
#include "util/bstream.h"
#include "util/streamutil.h"
#include "util/array.h"
#include "vmesh.h"

class VGeometry {
private:
	const int id = 1447513428;
	CArrayT<VMesh*> mesh_data;
public:
	VGeometry(aiMesh** meshes, int count);
	~VGeometry();

	void Write(bStream::CFileStream* writer);
};