#pragma once
#include "../../util/bstream.h"
#include "../../util/streamutil.h"
#include "vvertexattributeBase.h"
#include "vvertexattributes.h"
#include <vector>

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