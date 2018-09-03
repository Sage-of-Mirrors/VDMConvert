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

void VVertexData::Write(bStream::CFileStream * writer, nlohmann::json attribute_settings = default_vertex_settings) {
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
	ComponentCount cmp_cnt = StringToComponentCount(settings["ComponentCount"]);
	ComponentType cmp_type = StringToComponentType(settings["ComponentType"]);

	WriteAttributeHeader(writer, AttributeID::POSITION, cmp_cnt, cmp_type, settings["FixedPointExponent"],
		mPositions.size(), vertex_data_start);

	long next_header_offset = writer->tell();
	writer->seek(writer->getSize());

	for (int i = 0; i < mPositions.size(); i++) {
		writer->writeFloat(mPositions[i].x);
		writer->writeFloat(mPositions[i].y);
		writer->writeFloat(mPositions[i].z);
	}

	writer->seek(next_header_offset);
}

void VVertexData::WriteNormals(bStream::CFileStream * writer, long vertex_data_start, nlohmann::json settings) {
	writer->writeInt32(static_cast<int>(AttributeID::NORMAL));
	writer->writeInt8(4);
	writer->writeInt8(0);
	writer->writeInt8(0);
	writer->writeInt8(-1);
	writer->writeInt32(mNormals.size());
	writer->writeInt32(writer->getSize() - vertex_data_start);

	long next_header_offset = writer->tell();

	writer->seek(writer->getSize());

	for (int i = 0; i < mNormals.size(); i++) {
		writer->writeFloat(mNormals[i].x);
		writer->writeFloat(mNormals[i].y);
		writer->writeFloat(mNormals[i].z);
	}

	writer->seek(next_header_offset);
}

void VVertexData::WriteColors(bStream::CFileStream * writer, int index, long vertex_data_start, nlohmann::json settings) {
	writer->writeInt32(static_cast<int>(AttributeID::COLOR_0) + index);
	writer->writeInt8(5);
	writer->writeInt8(0);
	writer->writeInt8(0);
	writer->writeInt8(-1);
	writer->writeInt32(mColors[index].size());
	writer->writeInt32(writer->getSize() - vertex_data_start);

	long next_header_offset = writer->tell();

	writer->seek(writer->getSize());

	for (int i = 0; i < mColors[index].size(); i++) {
		writer->writeUInt8(mColors[index][i].r * 255.0f);
		writer->writeUInt8(mColors[index][i].g * 255.0f);
		writer->writeUInt8(mColors[index][i].b * 255.0f);
		writer->writeUInt8(mColors[index][i].a * 255.0f);
	}

	writer->seek(next_header_offset);
}

void VVertexData::WriteUVs(bStream::CFileStream * writer, int index, long vertex_data_start, nlohmann::json settings) {
	writer->writeInt32(static_cast<int>(AttributeID::TEX_0) + index);
	writer->writeInt8(4);
	writer->writeInt8(0);
	writer->writeInt8(0);
	writer->writeInt8(-1);
	writer->writeInt32(mUVs[index].size());
	writer->writeInt32(writer->getSize() - vertex_data_start);

	long next_header_offset = writer->tell();

	writer->seek(writer->getSize());

	for (int i = 0; i < mUVs[index].size(); i++) {
		writer->writeFloat(mUVs[index][i].x);
		writer->writeFloat(mUVs[index][i].y);
	}

	writer->seek(next_header_offset);
}