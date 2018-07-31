#pragma once
#include <stdint.h>
#include <assimp/mesh.h>
#include "util/array.h"
#include "GX_Enums.h"

template <typename T>
struct VDVertexAttributeT {
private:
	AttributeID attributeId;
	bool isColor;
	uint8_t attributeType;
	uint8_t componentCount;
	
	uint32_t valueCount;
	CArrayT<T>* data;
public:
	VDVertexAttributeT(AttributeID attribId, uint8_t attribType) {
		data = new CArrayT<T>();
		attributeType = attribType;
		attributeId = attribId;
	}

	~VDVertexAttributeT()
	{
		delete data;
	}

	AttributeID GetAttributeId();
	bool GetIsColor();
	uint8_t GetAttributeType();
	uint8_t GetComponentCount();

	CArrayT<T>* GetData() {
		return data;
	}

	void SetAttributeId(AttributeID attribId);
	void SetIsColor(bool isColor);
	void SetAttributeType(DataType dataType);
	void SetAttributeType(ColorDataType colorDataType);
	void SetComponentCount(uint8_t compCount);
	
	void AddData(const T* data, int count) {
		for (int i = 0; i < count; i++)
		{
			if (!this->data->contains(data[i]))
				this->data->append(data[i]);
		}
	}
};