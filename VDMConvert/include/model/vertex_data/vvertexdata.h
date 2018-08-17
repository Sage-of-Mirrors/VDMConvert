#pragma once
#include "util/bstream.h"
#include "util/streamutil.h"
#include "model/vertex_data/vvertexattributeBase.h"
#include "model/vertex_data/vvertexattributes.h"

class VVertexData {
private:
	const int id = 1448498264;
	CArrayT<VVertexAttributeBase*> Attributes;
public:
	VVertexData(aiMesh** meshes, int count);
	~VVertexData();

	VVertexAttributeBase* GetAttribute(AttributeID attribId);
	void Write(bStream::CFileStream* writer);
};