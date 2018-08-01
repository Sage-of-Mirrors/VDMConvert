#include "../include/model/vertex_data/vdvertexattributebase.h"

AttributeID VDVertexAttributeBase::GetAttributeId()
{
	return attributeId;
}

bool VDVertexAttributeBase::GetIsColor()
{
	return isColor;
}

uint8_t VDVertexAttributeBase::GetAttributeType()
{
	return attributeType;
}

uint8_t VDVertexAttributeBase::GetComponentCount()
{
	return componentCount;
}

void VDVertexAttributeBase::SetAttributeId(AttributeID attribId)
{
	attributeId = attribId;
}

void VDVertexAttributeBase::SetIsColor(bool isColor)
{
	this->isColor = isColor;
}

void VDVertexAttributeBase::SetAttributeType(DataType dataType)
{
	attributeType = static_cast<uint8_t>(dataType);
	isColor = false;
}

void VDVertexAttributeBase::SetAttributeType(ColorDataType colorDataType)
{
	attributeType = static_cast<uint8_t>(colorDataType);
	isColor = true;
}

void VDVertexAttributeBase::SetComponentCount(uint8_t compCnt)
{
	componentCount = compCnt;
}

void VDVertexAttributeBase::Write(bStream::CFileStream* writer)
{
	writer->writeUInt32(static_cast<uint32_t>(attributeId));
	writer->writeUInt8(attributeType);
	writer->writeUInt8(componentCount);
	writer->writeUInt8(exponent);
	writer->writeInt8(-1);
	writer->writeInt32(0);
	writer->writeInt32(0);
}