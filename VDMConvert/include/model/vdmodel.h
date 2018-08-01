#pragma once
#include <string>

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "util/bstream.h"
#include "vertex_data/vdvertexdata.h"

class VDModel {
private:
	const int id = 1447316804;
	VDVertexData * vertData;
public:
	VDModel(const std::string file_path);
	~VDModel();

	void WriteVDM(const std::string file_path);
};