#pragma once
#include "../util/json.hpp"

enum PrimitiveType {
	TRIANGLES = 0x90,
	TRIANGLE_STRIP = 0x98,
	TRIANGLE_FAN = 0xA0,
	LINES = 0xA8,
	LINE_STRIP = 0xB0,
	POINTS = 0xB8
};

enum AttributeID {
	POSITION_MATRIX_ID_X,
	TEX_0_MATRIX_INDEX,
	TEX_1_MATRIX_INDEX,
	TEX_2_MATRIX_INDEX,
	TEX_3_MATRIX_INDEX,
	TEX_4_MATRIX_INDEX,
	TEX_5_MATRIX_INDEX,
	TEX_6_MATRIX_INDEX,
	TEX_7_MATRIX_INDEX,
	POSITION,
	NORMAL,
	COLOR_0,
	COLOR_1,
	TEX_0,
	TEX_1,
	TEX_2,
	TEX_3,
	TEX_4,
	TEX_5,
	TEX_6,
	TEX_7,

	MAX_ATTRIBUTE_ID
};

AttributeID StringToAttributeId(const std::string& str) {
	if (str == "POSITION") {
		return AttributeID::POSITION;
	}
	else if (str == "NORMAL") {
		return AttributeID::NORMAL;
	}
	else if (str == "COLOR_0") {
		return AttributeID::COLOR_0;
	}
	else if (str == "COLOR_1") {
		return AttributeID::COLOR_1;
	}
	else if (str == "TEX_0") {
		return AttributeID::TEX_0;
	}
	else if (str == "TEX_1") {
		return AttributeID::TEX_1;
	}
	else if (str == "TEX_2") {
		return AttributeID::TEX_2;
	}
	else if (str == "TEX_3") {
		return AttributeID::TEX_3;
	}
	else if (str == "TEX_4") {
		return AttributeID::TEX_4;
	}
	else if (str == "TEX_5") {
		return AttributeID::TEX_5;
	}
	else if (str == "TEX_6") {
		return AttributeID::TEX_6;
	}
	else if (str == "TEX_7") {
		return AttributeID::TEX_7;
	}
	else {
		assert(false);
	}
}

enum ComponentType {
	UNSIGNED_8 = 0,
	SIGNED_8,
	UNSIGNED_16,
	SIGNED_16,
	FLOAT_32,

	RGB_565 = 0,
	RGB_8,
	RGBX_8,
	RGBA_4,
	RGBA_6,
	RGBA_8,

	MAX_DATA_TYPE
};

ComponentType StringToComponentType(const std::string& str) {
	if (str == "UNSIGNED_8") {
		return ComponentType::UNSIGNED_8;
	}
	else if (str == "SIGNED_8") {
		return ComponentType::SIGNED_8;
	}
	else if (str == "UNSIGNED_16") {
		return ComponentType::UNSIGNED_16;
	}
	else if (str == "SIGNED_16") {
		return ComponentType::SIGNED_16;
	}
	else if (str == "FLOAT_32") {
		return ComponentType::FLOAT_32;
	}
	else if (str == "RGB_565") {
		return ComponentType::RGB_565;
	}
	else if (str == "RGB_8") {
		return ComponentType::RGB_8;
	}
	else if (str == "RGBX_8") {
		return ComponentType::RGBX_8;
	}
	else if (str == "RGBA_4") {
		return ComponentType::RGBA_4;
	}
	else if (str == "RGBA_6") {
		return ComponentType::RGBA_6;
	}
	else if (str == "RGBA_8") {
		return ComponentType::RGBA_8;
	}
	else {
		assert(false);
	}
}

enum ComponentCount {
	POS_XY = 0,
	POS_XYZ,

	NRM_XYZ = 0,
	NRM_NBT,
	NRM_NBT3,

	CLR_RGB = 0,
	CLR_RGBA,

	TEX_S = 0,
	TEX_ST
};

ComponentCount StringToComponentCount(const std::string& str) {
	if (str == "POS_XY") {
		return ComponentCount::POS_XY;
	}
	else if (str == "POS_XYZ") {
		return ComponentCount::POS_XYZ;
	}
	else if (str == "NRM_XYZ") {
		return ComponentCount::NRM_XYZ;
	}
	else if (str == "NRM_NBT") {
		return ComponentCount::NRM_NBT;
	}
	else if (str == "NRM_NBT3") {
		return ComponentCount::NRM_NBT3;
	}
	else if (str == "CLR_RGB") {
		return ComponentCount::CLR_RGB;
	}
	else if (str == "CLR_RGBA") {
		return ComponentCount::CLR_RGBA;
	}
	else if (str == "TEX_S") {
		return ComponentCount::TEX_S;
	}
	else if (str == "TEX_ST") {
		return ComponentCount::TEX_ST;
	}
	else {
		assert(false);
	}
}