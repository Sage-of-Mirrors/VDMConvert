#pragma once
#include <string>

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "util/bstream.h"
#include "vertex_data/vvertexdata.h"
#include "geometry/vgeometry.h"

class VModel {
private:
	const int id = 1447904332;
	VVertexData * vertData;
	VGeometry * geomData;
public:
	VModel(const std::string file_path);
	~VModel();

	void WriteVDM(const std::string file_path);
};