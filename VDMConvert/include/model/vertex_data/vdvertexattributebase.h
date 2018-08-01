#pragma once
#include <stdint.h>
#include <assimp/mesh.h>

#include "util/array.h"
#include "../GX_Enums.h"
#include "util/bstream.h"

class VDVertexAttributeBase {
protected:
	AttributeID attributeId;
	bool isColor;
	uint8_t attributeType;
	uint8_t componentCount;
	uint8_t exponent;
public:
	AttributeID GetAttributeId();
	bool GetIsColor();
	uint8_t GetAttributeType();
	uint8_t GetComponentCount();

	void SetAttributeId(AttributeID attribId);
	void SetIsColor(bool isColor);
	void SetAttributeType(DataType dataType);
	void SetAttributeType(ColorDataType colorDataType);
	void SetComponentCount(uint8_t compCount);
	void Write(bStream::CFileStream* writer);
};