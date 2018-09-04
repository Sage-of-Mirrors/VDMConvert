#include "model/geometry/vmesh.h"

VMesh::VMesh(aiMesh* mesh, VVertexData * vtx_data)
{
	name = mesh->mName.data;
	num_faces = mesh->mNumFaces;

	SetAttributes(mesh);
	FindBounds(mesh->mVertices, mesh->mNumVertices);

	for (int i = 0; i < num_faces; i++) {
		for (int j = 0; j < 3; j++) {
			int face_index = mesh->mFaces[i].mIndices[j];

			size_t pos_index = 0;

			if (vtx_data->GetPositions()->contains(mesh->mVertices[face_index], &pos_index)) {
				indices.append(pos_index);
			}

			if (mesh->HasNormals()) {
				size_t nrm_index = 0;

				if (vtx_data->GetNormals()->contains(mesh->mNormals[face_index], &nrm_index)) {
					indices.append(nrm_index);
				}
			}

			for (int color = 0; color < 2; color++) {
				if (mesh->HasVertexColors(color)) {
					size_t clr_index = 0;

					if (vtx_data->GetColors(color)->contains(mesh->mColors[color][face_index], &clr_index)) {
						indices.append(clr_index);
					}
				}
			}

			for (int uv = 0; uv < 8; uv++) {
				if (mesh->HasTextureCoords(uv)) {
					size_t uv_index = 0;
					aiVector2D uv2d = aiVector2D(mesh->mTextureCoords[uv][face_index].x, mesh->mTextureCoords[uv][face_index].y);

					if (vtx_data->GetUVs(uv)->contains(uv2d, &uv_index)) {
						indices.append(uv_index);
					}
				}
			}
		}
	}
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

void VMesh::FindBounds(aiVector3D * positions, int count)
{
	min_bounds = aiVector3D(FLT_MAX, FLT_MAX, FLT_MAX);
	max_bounds = aiVector3D(FLT_MIN, FLT_MIN, FLT_MIN);

	for (int i = 0; i < count; i++)
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
	writer->writeInt32(0);
	writer->writeInt32(0);

	writer->writeFloat(min_bounds.x);
	writer->writeFloat(min_bounds.y);
	writer->writeFloat(min_bounds.z);

	writer->writeFloat(max_bounds.x);
	writer->writeFloat(max_bounds.y);
	writer->writeFloat(max_bounds.z);
}

int VMesh::WritePrimitives(bStream::CFileStream * writer)
{
	int num_primitives_written = 1;

	writer->writeInt8(0x90);
	writer->writeUInt16(num_faces);

	for (int i = 0; i < indices.size(); i++)
	{
		writer->writeUInt16(indices[i]);
	}

	return num_primitives_written;
}

void VMesh::WriteName(bStream::CFileStream * writer)
{
	writer->writeString(name);
	writer->writeInt8(0);
}