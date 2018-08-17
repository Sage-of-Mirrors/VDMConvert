#pragma once
#include <stdint.h>
#include <assimp/mesh.h>

#include "util/array.h"
#include "../GX_Enums.h"
#include "util/bstream.h"

class VVertexAttributeBase {
protected:
	AttributeID attributeId;
	bool isColor;
	uint8_t attributeType;
	uint8_t componentCount;
	uint8_t exponent;
	uint32_t vertexCount;
public:
	AttributeID GetAttributeId();
	bool GetIsColor();
	uint8_t GetAttributeType();
	uint8_t GetComponentCount();
	uint32_t GetVertexCount();

	void SetAttributeId(AttributeID attribId);
	void SetIsColor(bool isColor);
	void SetAttributeType(DataType dataType);
	void SetAttributeType(ColorDataType colorDataType);
	void SetComponentCount(uint8_t compCount);
	void Write(bStream::CFileStream* writer);
};