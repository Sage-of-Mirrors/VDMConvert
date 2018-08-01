#pragma once
#include "vdvertexattributet.h"

class VDVertexAttributeVector2 : public VDVertexAttributeT<aiVector2D> {
protected:
	virtual void WriteDataValue(bStream::CFileStream * writer, const aiVector2D & value) override {
		writer->writeFloat(value.x);
		writer->writeFloat(value.y);
	}
public:
	VDVertexAttributeVector2(AttributeID id, uint8_t type) : VDVertexAttributeT(id, type)
	{ }
};

class VDVertexAttributeVector3 : public VDVertexAttributeT<aiVector3D> {
protected:
	virtual void WriteDataValue(bStream::CFileStream * writer, const aiVector3D & value) override {
		writer->writeFloat(value.x);
		writer->writeFloat(value.y);
		writer->writeFloat(value.z);
	}
public:
	VDVertexAttributeVector3(AttributeID id, uint8_t type) : VDVertexAttributeT(id, type)
	{ }
};

class VDVertexAttributeColor4 : public VDVertexAttributeT<aiColor4D> {
protected:
	virtual void WriteDataValue(bStream::CFileStream * writer, const aiColor4D & value) override {
		writer->writeFloat(value.r);
		writer->writeFloat(value.g);
		writer->writeFloat(value.b);
		writer->writeFloat(value.a);
	}
public:
	VDVertexAttributeColor4(AttributeID id, uint8_t type) : VDVertexAttributeT(id, type)
	{ }
};