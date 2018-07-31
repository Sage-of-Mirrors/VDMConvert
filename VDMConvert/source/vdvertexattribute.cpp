#include "../include/vdvertexattribute.h"

template <typename T>
AttributeID VDVertexAttributeT<T>::GetAttributeId() {
	return attributeId;
}

template <typename T>
bool VDVertexAttributeT<T>::GetIsColor() {
	return isColor;
}

template <typename T>
uint8_t VDVertexAttributeT<T>::GetAttributeType() {
	return attributeType;
}

template <typename T>
uint8_t VDVertexAttributeT<T>::GetComponentCount() {
	return componentCount;
}

template <typename T>
void VDVertexAttributeT<T>::SetAttributeId(AttributeID attribId) {
	attributeId = attribId;
}

template <typename T>
void VDVertexAttributeT<T>::SetIsColor(bool isColor) {
	this->isColor = isColor;
}

template <typename T>
void VDVertexAttributeT<T>::SetAttributeType(DataType dataType) {
	attributeType = static_cast<uint8_t>(dataType);
	isColor = false;
}

template <typename T>
void VDVertexAttributeT<T>::SetAttributeType(ColorDataType colorDataType) {
	attributeType = static_cast<uint8_t>(colorDataType);
	isColor = true;
}

template <typename T>
void VDVertexAttributeT<T>::SetComponentCount(uint8_t compCnt) {
	compnentCount = compCnt;
}