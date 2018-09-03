#pragma once
#include <cassert>
#include <assimp/scene.h>
#include "../GX_Enums.h"
#include "../../util/enumutil.h"
#include "../../util/json.hpp"
#include "util/array.h"
#include "util/bstream.h"
#include "util/streamutil.h"

static const nlohmann::json default_vertex_settings = {
	{
		"Settings", {
			{
				{ "Attribute", "POSITION" },
                { "ComponentCount", "POS_XYZ" },
				{ "ComponentType", "FLOAT_32" },
				{ "FixedPointExponent", 0 }
			},
			{
				{ "Attribute", "NORMAL" },
				{ "ComponentCount", "NRM_XYZ" },
				{ "ComponentType", "SIGNED_16" },
				{ "FixedPointExponent", 14 }
			},
			{
				{ "Attribute", "COLOR_0" },
				{ "ComponentCount", "CLR_RGBA" },
				{ "ComponentType", "RGBA_8" },
				{ "FixedPointExponent", 0 }
			},
			{
				{ "Attribute", "COLOR_1" },
				{ "ComponentCount", "CLR_RGBA" },
				{ "ComponentType", "RGBA_8" },
				{ "FixedPointExponent", 0 }
			},
			{
				{ "Attribute", "TEX_0" },
				{ "ComponentCount", "TEX_ST" },
				{ "ComponentType", "SIGNED_16" },
				{ "FixedPointExponent", 8 }
			},
			{
				{ "Attribute", "TEX_1" },
				{ "ComponentCount", "TEX_ST" },
				{ "ComponentType", "SIGNED_16" },
				{ "FixedPointExponent", 8 }
			},
			{
				{ "Attribute", "TEX_2" },
				{ "ComponentCount", "TEX_ST" },
				{ "ComponentType", "SIGNED_16" },
				{ "FixedPointExponent", 8 }
			},
			{
				{ "Attribute", "TEX_3" },
				{ "ComponentCount", "TEX_ST" },
				{ "ComponentType", "SIGNED_16" },
				{ "FixedPointExponent", 8 }
			},
			{
				{ "Attribute", "TEX_4" },
				{ "ComponentCount", "TEX_ST" },
				{ "ComponentType", "SIGNED_16" },
				{ "FixedPointExponent", 8 }
			},
			{
				{ "Attribute", "TEX_5" },
				{ "ComponentCount", "TEX_ST" },
				{ "ComponentType", "SIGNED_16" },
				{ "FixedPointExponent", 8 }
			},
			{
				{ "Attribute", "TEX_6" },
				{ "ComponentCount", "TEX_ST" },
				{ "ComponentType", "SIGNED_16" },
				{ "FixedPointExponent", 8 }
			},
			{
				{ "Attribute", "TEX_7" },
				{ "ComponentCount", "TEX_ST" },
				{ "ComponentType", "SIGNED_16" },
				{ "FixedPointExponent", 8 }
			}
        }
	}
};

class VVertexData {
private:
	const int id = 1448498264;

	bool mActiveAttributes[21];
	CArrayT<aiVector3D> mPositions;
	CArrayT<aiVector3D> mNormals;
	CArrayT<aiColor4D>  mColors[2];
	CArrayT<aiVector2D> mUVs[8];

	void SetAttribute(AttributeID id);
	void ProcessMesh(aiMesh* mesh);

	void WriteAttributeHeader(bStream::CFileStream * writer, AttributeID id, ComponentCount cmp_cnt,
		ComponentType cmp_type, int fixed_point_exponent, int obj_count, int offset);
	void WritePositions(bStream::CFileStream * writer, long vertex_data_start, nlohmann::json settings);
	void WriteNormals(bStream::CFileStream * writer, long vertex_data_start, nlohmann::json settings);
	void WriteColors(bStream::CFileStream * writer, int index, long vertex_data_start, nlohmann::json settings);
	void WriteUVs(bStream::CFileStream * writer, int index, long vertex_data_start, nlohmann::json settings);
public:
	VVertexData(aiMesh** meshes, int count);
	~VVertexData();

	void Initialize();

	bool GetAttribute(AttributeID id);
	CArrayT<aiVector3D> * GetPositions();
	CArrayT<aiVector3D> * GetNormals();
	CArrayT<aiColor4D>  * GetColors(int index);
	CArrayT<aiVector2D> * GetUVs(int index);

	void Write(bStream::CFileStream* writer, nlohmann::json attribute_settings = default_vertex_settings);
};