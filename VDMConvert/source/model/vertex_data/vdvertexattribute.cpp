#include "model/vertex_data/vvertexattributebase.h"

AttributeID VVertexAttributeBase::GetAttributeId()
{
	return attributeId;
}

bool VVertexAttributeBase::GetIsColor()
{
	return isColor;
}

uint8_t VVertexAttributeBase::GetAttributeType()
{
	return attributeType;
}

uint8_t VVertexAttributeBase::GetComponentCount()
{
	return componentCount;
}

uint32_t VVertexAttributeBase::GetVertexCount()
{
	return vertexCount;
}

void VVertexAttributeBase::SetAttributeId(AttributeID attribId)
{
	attributeId = attribId;
}

void VVertexAttributeBase::SetIsColor(bool isColor)
{
	this->isColor = isColor;
}

void VVertexAttributeBase::SetAttributeType(DataType dataType)
{
	attributeType = static_cast<uint8_t>(dataType);
	isColor = false;
}

void VVertexAttributeBase::SetAttributeType(ColorDataType colorDataType)
{
	attributeType = static_cast<uint8_t>(colorDataType);
	isColor = true;
}

void VVertexAttributeBase::SetComponentCount(uint8_t compCnt)
{
	componentCount = compCnt;
}

void VVertexAttributeBase::Write(bStream::CFileStream* writer)
{
	writer->writeUInt32(static_cast<uint32_t>(attributeId));
	writer->writeUInt8(attributeType);
	writer->writeUInt8(componentCount);
	writer->writeUInt8(exponent);
	writer->writeInt8(-1);
	writer->writeInt32(0);
	writer->writeInt32(0);
}