#include "../../include/util/enumutil.h"

AttributeID EnumUtil::StringToAttributeId(const std::string& str) {
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

ComponentCount EnumUtil::StringToComponentCount(const std::string& str) {
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

ComponentType EnumUtil::StringToComponentType(const std::string& str) {
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