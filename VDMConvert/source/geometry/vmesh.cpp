#include "model/geometry/vmesh.h"

VMesh::VMesh(aiMesh* mesh, VVertexData * vtx_data)
{
	name = mesh->mName.data;

	SetAttributes(mesh);
	SetIndices(mesh, vtx_data);
}

void VMesh::SetAttributes(aiMesh * mesh)
{
	attributes = 0;
	attributes |= (1 << static_cast<int32_t>(AttributeID::POSITION));

	if (mesh->HasNormals())
	{
		attributes |= (1 << static_cast<int32_t>(AttributeID::NORMAL));
	}

	for (int i = 0; i < 2; i++)
	{
		if (mesh->HasVertexColors(i))
		{
			attributes |= (1 << static_cast<int32_t>(AttributeID::COLOR_0 + i));
		}
	}

	for (int i = 0; i < 8; i++)
	{
		if (mesh->HasTextureCoords(i))
		{
			attributes |= (1 << static_cast<int32_t>(AttributeID::TEX_0 + i));
		}
	}
}

void VMesh::SetIndices(aiMesh * mesh, VVertexData * vtx_data)
{
	CArrayT<aiVector3D> positions_for_bounds;

	CArrayT<aiVector3D> vtx_positions = static_cast<VVertexAttributeVector3 *>(vtx_data->GetAttribute(AttributeID::POSITION))->GetData();
	CArrayT<aiVector3D> vtx_normals;
	CArrayT<aiColor4D>  vtx_colors[2];
	CArrayT<aiVector2D> vtx_uvs[8];
	
	if (mesh->HasNormals())
	{
		vtx_normals = static_cast<VVertexAttributeVector3 *>(vtx_data->GetAttribute(AttributeID::NORMAL))->GetData();
	}
	
	for (int i = 0; i < 2; i++)
	{
		if (mesh->HasVertexColors(i))
		{
			vtx_colors[i] = static_cast<VVertexAttributeColor4 *>(vtx_data->GetAttribute(AttributeID::COLOR_0 + i))->GetData();
		}
	}
	
	for (int i = 0; i < 8; i++)
	{
		if (mesh->HasTextureCoords(i))
		{
			vtx_uvs[i] = static_cast<VVertexAttributeVector2 *>(vtx_data->GetAttribute(AttributeID::TEX_0 + i))->GetData();
		}
	}

	for (int i = 0; i < mesh->mNumFaces; i++)
	{
		uint16_t pos_index = mesh->mFaces[i].mIndices[0];
		aiVector3D pos = mesh->mVertices[pos_index];

		for (int i = 0; i < vtx_positions.size(); i++)
		{
			if (vtx_positions[i] == pos)
			{
				indices.append(i);
				positions_for_bounds.append(pos);
				break;
			}
		}
		
		if (mesh->HasNormals())
		{
			uint16_t nrm_index = mesh->mFaces[i].mIndices[1];
		}
	}

	FindBounds(positions_for_bounds);
}

void VMesh::FindBounds(CArrayT<aiVector3D> positions)
{
	min_bounds = aiVector3D(FLT_MAX, FLT_MAX, FLT_MAX);
	max_bounds = aiVector3D(FLT_MIN, FLT_MIN, FLT_MIN);

	for (int i = 0; i < positions.size(); i++)
	{
		aiVector3D cur_vec = positions[i];

		// Min check
		if (cur_vec.x < min_bounds.x)
		{
			min_bounds.x = cur_vec.x;
		}

		if (cur_vec.y < min_bounds.y)
		{
			min_bounds.y = cur_vec.y;
		}

		if (cur_vec.z < min_bounds.z)
		{
			min_bounds.z = cur_vec.z;
		}

		// Max check
		if (cur_vec.x > min_bounds.x)
		{
			max_bounds.x = cur_vec.x;
		}

		if (cur_vec.y > min_bounds.y)
		{
			max_bounds.y = cur_vec.y;
		}

		if (cur_vec.z > min_bounds.z)
		{
			max_bounds.z = cur_vec.z;
		}
	}
}

void VMesh::Write(bStream::CFileStream * writer)
{
	writer->writeUInt32(attributes);

	writer->writeFloat(min_bounds.x);
	writer->writeFloat(min_bounds.y);
	writer->writeFloat(min_bounds.z);

	writer->writeFloat(max_bounds.x);
	writer->writeFloat(max_bounds.y);
	writer->writeFloat(max_bounds.z);
}

void VMesh::WritePrimitives(bStream::CFileStream * writer)
{

}

void VMesh::WriteName(bStream::CFileStream * writer)
{
	writer->writeString(name);
	writer->writeInt8(0);
}