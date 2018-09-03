#include "model/geometry/vmesh.h"

VMesh::VMesh(aiMesh* mesh, VVertexData * vtx_data)
{
	name = mesh->mName.data;
	num_faces = mesh->mNumFaces;

	SetAttributes(mesh);
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
	writer->writeInt32(0);

	writer->writeFloat(min_bounds.x);
	writer->writeFloat(min_bounds.y);
	writer->writeFloat(min_bounds.z);

	writer->writeFloat(max_bounds.x);
	writer->writeFloat(max_bounds.y);
	writer->writeFloat(max_bounds.z);
}

void VMesh::WritePrimitives(bStream::CFileStream * writer)
{
	writer->writeInt8(0x90);
	writer->writeUInt16(num_faces);

	for (int i = 0; i < indices.size(); i++)
	{
		writer->writeUInt16(indices[i]);
	}
}

void VMesh::WriteName(bStream::CFileStream * writer)
{
	writer->writeString(name);
	writer->writeInt8(0);
}