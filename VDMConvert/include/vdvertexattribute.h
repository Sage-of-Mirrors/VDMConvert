#pragma once
#include <stdint.h>
#include <assimp/mesh.h>
#include "util/array.h"
#include "GX_Enums.h"

struct VDVertexAttributeBase {
protected:
	AttributeID attributeId;
	bool isColor;
	uint8_t attributeType;
	uint8_t componentCount;
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
};

template <typename T>
struct VDVertexAttributeT : VDVertexAttributeBase {
private:
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

	CArrayT<T>* GetData() {
		return data;
	}
	
	void AddData(const T* data, int count) {
		for (int i = 0; i < count; i++)
		{
			if (!this->data->contains(data[i]))
				this->data->append(data[i]);
		}
	}
};