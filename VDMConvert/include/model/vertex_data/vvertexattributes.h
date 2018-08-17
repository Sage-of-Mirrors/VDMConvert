#pragma once
#include "vvertexattributet.h"

class VVertexAttributeVector2 : public VVertexAttributeT<aiVector2D> {
protected:
	virtual void WriteDataValue(bStream::CFileStream * writer, const aiVector2D & value) override {
		writer->writeFloat(value.x);
		writer->writeFloat(value.y);
	}
public:
	VVertexAttributeVector2(AttributeID id, uint8_t type) : VVertexAttributeT(id, type)
	{ }
};

class VVertexAttributeVector3 : public VVertexAttributeT<aiVector3D> {
protected:
	virtual void WriteDataValue(bStream::CFileStream * writer, const aiVector3D & value) override {
		writer->writeFloat(value.x);
		writer->writeFloat(value.y);
		writer->writeFloat(value.z);
	}
public:
	VVertexAttributeVector3(AttributeID id, uint8_t type) : VVertexAttributeT(id, type)
	{ }
};

class VVertexAttributeColor4 : public VVertexAttributeT<aiColor4D> {
protected:
	virtual void WriteDataValue(bStream::CFileStream * writer, const aiColor4D & value) override {
		writer->writeFloat(value.r);
		writer->writeFloat(value.g);
		writer->writeFloat(value.b);
		writer->writeFloat(value.a);
	}
public:
	VVertexAttributeColor4(AttributeID id, uint8_t type) : VVertexAttributeT(id, type)
	{ }
};