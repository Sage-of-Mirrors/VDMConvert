#include "model/vertex_data/vvertexdata.h"

VVertexData::VVertexData(aiMesh** meshes, int count) {
	for (int i = 0; i < 21; i++) {
		mActiveAttributes[i] = false;
	}

	// Position is the one required attribute
	SetAttribute(AttributeID::POSITION);

	for (int i = 0; i < count; i++) {
		ProcessMesh(meshes[i]);
	}
}

VVertexData::~VVertexData() {

}

void VVertexData::Initialize() {
	for (int i = 0; i < 21; i++) {
		mActiveAttributes[i] = false;
	}

	mPositions.clear();
	mNormals.clear();

	for (int i = 0; i < 2; i++) {
		mColors[i].clear();
	}

	for (int i = 0; i < 8; i++) {
		mUVs[i].clear();
	}
}

bool VVertexData::GetAttribute(AttributeID id) {
	return mActiveAttributes[static_cast<int>(id)];
}

void VVertexData::SetAttribute(AttributeID id) {
	mActiveAttributes[static_cast<int>(id)] = true;
}

void VVertexData::ProcessMesh(aiMesh* mesh) {
	for (int i = 0; i < mesh->mNumVertices; i++) {
		if (!mPositions.contains(mesh->mVertices[i])) {
			mPositions.append(mesh->mVertices[i]);
		}
	}

	if (mesh->HasNormals()) {
		SetAttribute(AttributeID::NORMAL);

		for (int i = 0; i < mesh->mNumVertices; i++) {
			if (!mNormals.contains(mesh->mNormals[i])) {
				mNormals.append(mesh->mNormals[i]);
			}
		}
	}

	for (int i = 0; i < 2; i++) {
		if (mesh->HasVertexColors(i)) {
			SetAttribute(static_cast<AttributeID>(11 + i));

			for (int j = 0; j < mesh->mNumVertices; j++) {
				if (!mColors[i].contains(mesh->mColors[i][j])) {
					mColors[i].append(mesh->mColors[i][j]);
				}
			}
		}
	}

	for (int i = 0; i < 8; i++) {
		if (mesh->HasVertexColors(i)) {
			SetAttribute(static_cast<AttributeID>(13 + i));

			for (int j = 0; j < mesh->mNumVertices; j++) {
				aiVector2D vec2 = aiVector2D(mesh->mTextureCoords[i][j].x, 1 - mesh->mTextureCoords[i][j].y);

				if (!mUVs[i].contains(vec2)) {
					mUVs[i].append(vec2);
				}
			}
		}
	}
}

void VVertexData::Write(bStream::CFileStream * writer, nlohmann::json attribute_settings) {
	long curOffset = writer->tell();

	int num_active_attributes = 0;

	for (int i = 0; i < 21; i++) {
		if (mActiveAttributes[i]) {
			num_active_attributes++;
		}
	}

	writer->writeUInt32(id);
	writer->writeInt32(0); // Placeholder for size
	writer->writeInt32(num_active_attributes);
	writer->writeInt32(-1); // Padding

	// Placeholders for attribute data headers
	for (int i = 0; i < num_active_attributes; i++) {
		writer->writeInt32(0); // Attribute ID
		writer->writeInt32(0); // Type/component count/exponent/padding
		writer->writeInt32(0); // Count
		writer->writeInt32(0); // Offset
	}

	// Set the stream to the first attribute data header
	writer->seek(curOffset + 0x10);

	WritePositions(writer, curOffset, attribute_settings["Settings"][0]);

	if (GetAttribute(AttributeID::NORMAL)) {
		WriteNormals(writer, curOffset, attribute_settings["Settings"][1]);
	}

	for (int i = 0; i < 2; i++) {
		if (GetAttribute(static_cast<AttributeID>(11 + i))) {
			WriteColors(writer, i, curOffset, attribute_settings["Settings"][2 + i]);
		}
	}

	for (int i = 0; i < 8; i++) {
		if (GetAttribute(static_cast<AttributeID>(13 + i))) {
			WriteUVs(writer, i, curOffset, attribute_settings["Settings"][4 + i]);
		}
	}

	writer->seek(curOffset + 4);
	writer->writeUInt32(writer->getSize() - curOffset);
	writer->seek(writer->getSize());
}

CArrayT<aiVector3D> * VVertexData::GetPositions() {
	if (GetAttribute(AttributeID::POSITION)) {
		return &mPositions;
	}
	else {
		return NULL;
	}
}

CArrayT<aiVector3D> * VVertexData::GetNormals() {
	if (GetAttribute(AttributeID::NORMAL)) {
		return &mNormals;
	}
	else {
		return NULL;
	}
}

CArrayT<aiColor4D> * VVertexData::GetColors(int index) {
	assert(index > 0 && index < 2);

	if (GetAttribute(static_cast<AttributeID>(11 + index))) {
		return &mColors[index];
	}
	else {
		return NULL;
	}
}

CArrayT<aiVector2D> * VVertexData::GetUVs(int index) {
	assert(index > 0 && index < 7);

	if (GetAttribute(static_cast<AttributeID>(13 + index))) {
		return &mUVs[index];
	}
	else {
		return NULL;
	}
}

void VVertexData::WriteAttributeHeader(bStream::CFileStream * writer, AttributeID id, ComponentCount cmp_cnt,
	ComponentType cmp_type, int fixed_point_exponent, int obj_count, int offset) {

	writer->writeInt32(static_cast<int32_t>(id));
	writer->writeInt8(static_cast<int8_t>(cmp_cnt));
	writer->writeInt8(static_cast<int8_t>(cmp_type));
	writer->writeInt8(fixed_point_exponent);
	writer->writeInt8(-1);
	writer->writeInt32(obj_count);
	writer->writeInt32(writer->getSize() - offset);

	writer->seek(writer->getSize());
}

void VVertexData::WritePositions(bStream::CFileStream * writer, long vertex_data_start, nlohmann::json settings) {
	ComponentCount cmp_cnt = EnumUtil::StringToComponentCount(settings["ComponentCount"]);
	ComponentType cmp_type = EnumUtil::StringToComponentType(settings["ComponentType"]);
	int fixed_point = settings["FixedPointExponent"];

	float scale_factor = static_cast<float>(1 << fixed_point);


	WriteAttributeHeader(writer, AttributeID::POSITION, cmp_cnt, cmp_type, fixed_point, mPositions.size(), vertex_data_start);
	long next_header_offset = writer->tell() - vertex_data_start;
	writer->seek(writer->getSize());

	for (int i = 0; i < mPositions.size(); i++) {
		switch (cmp_type) {
		case ComponentType::UNSIGNED_8: {
			uint8_t x_u8 = mPositions[i].x * scale_factor;
			uint8_t y_u8 = mPositions[i].y * scale_factor;
			uint8_t z_u8 = mPositions[i].z * scale_factor;

			writer->writeUInt8(x_u8);
			writer->writeUInt8(y_u8);

			if (cmp_cnt == ComponentCount::POS_XYZ) {
				writer->writeUInt8(z_u8);
			}
		}
			break;
		case ComponentType::SIGNED_8: {
			int8_t x_s8 = mPositions[i].x * scale_factor;
			int8_t y_s8 = mPositions[i].y * scale_factor;
			int8_t z_s8 = mPositions[i].z * scale_factor;

			writer->writeInt8(x_s8);
			writer->writeInt8(y_s8);

			if (cmp_cnt == ComponentCount::POS_XYZ) {
				writer->writeInt8(z_s8);
			}
		}
			break;
		case ComponentType::UNSIGNED_16: {
			uint16_t x_u16 = mPositions[i].x * scale_factor;
			uint16_t y_u16 = mPositions[i].y * scale_factor;
			uint16_t z_u16 = mPositions[i].z * scale_factor;

			writer->writeUInt16(x_u16);
			writer->writeUInt16(y_u16);

			if (cmp_cnt == ComponentCount::POS_XYZ) {
				writer->writeUInt16(z_u16);
			}
		}
			break;
		case ComponentType::SIGNED_16: {
			int16_t x_s16 = mPositions[i].x * scale_factor;
			int16_t y_s16 = mPositions[i].y * scale_factor;
			int16_t z_s16 = mPositions[i].z * scale_factor;

			writer->writeInt16(x_s16);
			writer->writeInt16(y_s16);

			if (cmp_cnt == ComponentCount::POS_XYZ) {
				writer->writeInt16(z_s16);
			}
		}
			break;
		case ComponentType::FLOAT_32: {
			writer->writeFloat(mPositions[i].x);
			writer->writeFloat(mPositions[i].y);

			if (cmp_cnt == ComponentCount::POS_XYZ) {
				writer->writeFloat(mPositions[i].z);
			}
		}
			break;
		}
	}

	StreamUtil::PadFileStream(writer, 32);
	writer->seek(next_header_offset);
}

void VVertexData::WriteNormals(bStream::CFileStream * writer, long vertex_data_start, nlohmann::json settings) {
	ComponentCount cmp_cnt = EnumUtil::StringToComponentCount(settings["ComponentCount"]);
	ComponentType cmp_type = EnumUtil::StringToComponentType(settings["ComponentType"]);
	int fixed_point = settings["FixedPointExponent"];

	float scale_factor = static_cast<float>(1 << fixed_point);

	WriteAttributeHeader(writer, AttributeID::NORMAL, cmp_cnt, cmp_type, fixed_point, mNormals.size(), vertex_data_start);

	long next_header_offset = writer->tell();
	writer->seek(writer->getSize());

	for (int i = 0; i < mNormals.size(); i++) {
		switch (cmp_type) {
		case ComponentType::UNSIGNED_8: {
			uint8_t x_u8 = mNormals[i].x * scale_factor;
			uint8_t y_u8 = mNormals[i].y * scale_factor;
			uint8_t z_u8 = mNormals[i].z * scale_factor;

			writer->writeUInt8(x_u8);
			writer->writeUInt8(y_u8);

			if (cmp_cnt == ComponentCount::NRM_XYZ) {
				writer->writeUInt8(z_u8);
			}
		}
			break;
		case ComponentType::SIGNED_8: {
			int8_t x_s8 = mNormals[i].x * scale_factor;
			int8_t y_s8 = mNormals[i].y * scale_factor;
			int8_t z_s8 = mNormals[i].z * scale_factor;

			writer->writeInt8(x_s8);
			writer->writeInt8(y_s8);

			if (cmp_cnt == ComponentCount::NRM_XYZ) {
				writer->writeInt8(z_s8);
			}
		}
			break;
		case ComponentType::UNSIGNED_16: {
			uint16_t x_u16 = mNormals[i].x * scale_factor;
			uint16_t y_u16 = mNormals[i].y * scale_factor;
			uint16_t z_u16 = mNormals[i].z * scale_factor;

			writer->writeUInt16(x_u16);
			writer->writeUInt16(y_u16);

			if (cmp_cnt == ComponentCount::NRM_XYZ) {
				writer->writeUInt16(z_u16);
			}
		}
			break;
		case ComponentType::SIGNED_16: {
			int16_t x_s16 = mNormals[i].x * scale_factor;
			int16_t y_s16 = mNormals[i].y * scale_factor;
			int16_t z_s16 = mNormals[i].z * scale_factor;

			writer->writeInt16(x_s16);
			writer->writeInt16(y_s16);

			if (cmp_cnt == ComponentCount::NRM_XYZ) {
				writer->writeInt16(z_s16);
			}
		}
			break;
		case ComponentType::FLOAT_32: {
			writer->writeFloat(mNormals[i].x);
			writer->writeFloat(mNormals[i].y);

			if (cmp_cnt == ComponentCount::NRM_XYZ) {
				writer->writeFloat(mNormals[i].z);
			}
		}
			break;
		}
	}

	StreamUtil::PadFileStream(writer, 32);
	writer->seek(next_header_offset);
}

void VVertexData::WriteColors(bStream::CFileStream * writer, int index, long vertex_data_start, nlohmann::json settings) {
	ComponentCount cmp_cnt = EnumUtil::StringToComponentCount(settings["ComponentCount"]);
	ComponentType cmp_type = EnumUtil::StringToComponentType(settings["ComponentType"]);

	WriteAttributeHeader(writer, static_cast<AttributeID>(11 + index), cmp_cnt, cmp_type, 0, mColors[index].size(), vertex_data_start);

	long next_header_offset = writer->tell();
	writer->seek(writer->getSize());

	for (int i = 0; i < mColors[index].size(); i++) {
		switch (cmp_type) {
		case ComponentType::RGB_565: {
			uint8_t r_5 = mColors[index][i].r * 31.0f;
			uint8_t g_6 = mColors[index][i].g * 63.0f;
			uint8_t b_5 = mColors[index][i].b * 31.0f;

			uint16_t rgb_565 = (r_5 << 11) || (g_6 << 5) || (b_5);
		}
			break;
		case ComponentType::RGB_8: {
			writer->writeUInt8(mColors[index][i].r * 255.0f);
			writer->writeUInt8(mColors[index][i].g * 255.0f);
			writer->writeUInt8(mColors[index][i].b * 255.0f);
		}
			break;
		case ComponentType::RGBX_8: {
			writer->writeUInt8(mColors[index][i].r * 255.0f);
			writer->writeUInt8(mColors[index][i].g * 255.0f);
			writer->writeUInt8(mColors[index][i].b * 255.0f);
			writer->writeUInt8(0);
		}
			break;
		case ComponentType::RGBA_4: {
			uint8_t r_4 = mColors[index][i].r * 15.0f;
			uint8_t g_4 = mColors[index][i].g * 15.0f;
			uint8_t b_4 = mColors[index][i].b * 15.0f;
			uint8_t a_4 = mColors[index][i].a * 15.0f;

			uint8_t rg_4 = (r_4 << 4) || (g_4);
			uint8_t ba_4 = (b_4 << 4) || (a_4);

			writer->writeUInt8(rg_4);
			writer->writeUInt8(ba_4);
		}
			break;
		case ComponentType::RGBA_6: {
			uint8_t r_6 = mColors[index][i].r * 63.0f;
			uint8_t g_6 = mColors[index][i].g * 63.0f;
			uint8_t b_6 = mColors[index][i].b * 63.0f;
			uint8_t a_6 = mColors[index][i].a * 63.0f;

			uint32_t rgba_6 = (r_6 << 26) || (b_6 << 20) || (g_6 << 14) || (a_6 << 8);

			writer->writeUInt32(rgba_6);
		}
			break;
		case ComponentType::RGBA_8: {
			writer->writeUInt8(mColors[index][i].r * 255.0f);
			writer->writeUInt8(mColors[index][i].g * 255.0f);
			writer->writeUInt8(mColors[index][i].b * 255.0f);
			writer->writeUInt8(mColors[index][i].a * 255.0f);
		}
			break;
		}
	}

	StreamUtil::PadFileStream(writer, 32);
	writer->seek(next_header_offset);
}

void VVertexData::WriteUVs(bStream::CFileStream * writer, int index, long vertex_data_start, nlohmann::json settings) {
	ComponentCount cmp_cnt = EnumUtil::StringToComponentCount(settings["ComponentCount"]);
	ComponentType cmp_type = EnumUtil::StringToComponentType(settings["ComponentType"]);
	int fixed_point = settings["FixedPointExponent"];

	float scale_factor = static_cast<float>(1 << fixed_point);

	WriteAttributeHeader(writer, static_cast<AttributeID>(13 + index), cmp_cnt, cmp_type, fixed_point,
		mUVs[index].size(), vertex_data_start);

	long next_header_offset = writer->tell();
	writer->seek(writer->getSize());

	for (int i = 0; i < mColors[index].size(); i++) {
		switch (cmp_type) {
		case ComponentType::UNSIGNED_8: {
			uint8_t x_u8 = mNormals[i].x * scale_factor;
			uint8_t y_u8 = mNormals[i].y * scale_factor;

			writer->writeUInt8(x_u8);

			if (cmp_cnt == ComponentCount::TEX_ST) {
				writer->writeUInt8(y_u8);
			}
		}
			break;
		case ComponentType::SIGNED_8: {
			int8_t x_s8 = mNormals[i].x * scale_factor;
			int8_t y_s8 = mNormals[i].y * scale_factor;

			writer->writeInt8(x_s8);

			if (cmp_cnt == ComponentCount::TEX_ST) {
				writer->writeInt8(y_s8);
			}
		}
			break;
		case ComponentType::UNSIGNED_16: {
			uint16_t x_u16 = mNormals[i].x * scale_factor;
			uint16_t y_u16 = mNormals[i].y * scale_factor;

			writer->writeUInt16(x_u16);

			if (cmp_cnt == ComponentCount::TEX_ST) {
				writer->writeUInt16(y_u16);
			}
		}
			break;
		case ComponentType::SIGNED_16: {
			int16_t x_s16 = mNormals[i].x * scale_factor;
			int16_t y_s16 = mNormals[i].y * scale_factor;

			writer->writeInt16(x_s16);

			if (cmp_cnt == ComponentCount::TEX_ST) {
				writer->writeInt16(y_s16);
			}
		}
			break;
		case ComponentType::FLOAT_32: {
			writer->writeFloat(mNormals[i].x);

			if (cmp_cnt == ComponentCount::TEX_ST) {
				writer->writeFloat(mNormals[i].y);
			}
		}
			break;
		}
	}

	StreamUtil::PadFileStream(writer, 32);
	writer->seek(next_header_offset);
}