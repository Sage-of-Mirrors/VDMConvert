#pragma once
#include "vdvertexattribute.h"

class VDVertexData {
private:
	const int id = 1447319128;
	CArrayT<VDVertexAttributeBase*> Attributes;
public:
	VDVertexData(aiMesh** meshes, int count);
	~VDVertexData();

	VDVertexAttributeBase* GetAttribute(AttributeID attribId);
	void Write();
};