#pragma once
#include "../../util/bstream.h"
#include "../../util/streamutil.h"
#include "vdvertexattributeBase.h"
#include "vdvertexattributes.h"
#include <vector>

class VDVertexData {
private:
	const int id = 1447319128;
	CArrayT<VDVertexAttributeBase*> Attributes;
public:
	VDVertexData(aiMesh** meshes, int count);
	~VDVertexData();

	VDVertexAttributeBase* GetAttribute(AttributeID attribId);
	void Write(bStream::CFileStream* writer);
};