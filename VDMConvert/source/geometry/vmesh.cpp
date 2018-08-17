#include "../../include/model/geometry/vmesh.h"

VMesh::VMesh(aiMesh* mesh)
{
	name = mesh->mName.data;

	SetAttributes(mesh);
}

void VMesh::SetAttributes(aiMesh * mesh)
{
	attributes = 0;
	attributes |= (1 << 9);

	if (mesh->HasNormals())
	{
		attributes |= (1 << 10);
	}

	if (mesh->HasVertexColors(0))
	{
		attributes |= (1 << 11);
	}

	if (mesh->HasVertexColors(1))
	{
		attributes |= (1 << 12);
	}

	for (int i = 0; i < 8; i++)
	{
		if (mesh->HasTextureCoords(i))
		{
			attributes |= (1 << 13 + i);
		}
	}
}

void VMesh::Write(bStream::CFileStream * writer)
{
	writer->writeUInt32(attributes);
}

void VMesh::WriteName(bStream::CFileStream * writer)
{
	writer->writeString(name);
	writer->writeInt8(0);
}