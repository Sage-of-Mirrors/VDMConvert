#pragma once
#include "../model/GX_Enums.h"

class EnumUtil {
public:
	static AttributeID StringToAttributeId(const std::string& str);
	static ComponentCount StringToComponentCount(const std::string& str);
	static ComponentType StringToComponentType(const std::string& str);
};