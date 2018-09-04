#include "model/geometry/vgeometry.h"

VGeometry::VGeometry(aiMesh** meshes, int count, VVertexData * vtx_data)
{
	for (int i = 0; i < count; i++)
	{
		VMesh * mesh = new VMesh(meshes[i], vtx_data);
		mesh_data.append(mesh);
	}
}

VGeometry::~VGeometry()
{

}

void VGeometry::Write(bStream::CFileStream* writer)
{
	long chunk_start = writer->getSize();

	writer->writeInt32(id);
	writer->writeInt32(0);
	writer->writeInt32(mesh_data.size());
	writer->writeInt32(0);

	for (int i = 0; i < mesh_data.size(); i++)
	{
		mesh_data[i]->Write(writer);
	}

	for (int i = 0; i < mesh_data.size(); i++)
	{
		long prim_offset = writer->getSize() - chunk_start;
		int num_prims = mesh_data[i]->WritePrimitives(writer);

		writer->seek(chunk_start + 16 + (i * 16) + 8);
		writer->writeInt32(num_prims);
		writer->writeInt32(prim_offset);
		writer->seek(writer->getSize());

		StreamUtil::PadFileStream(writer, 32);
	}

	long name_table_offset = writer->getSize() - chunk_start;

	// Write string table
	writer->seek(chunk_start + 12);
	writer->writeInt32(name_table_offset);
	writer->seek(writer->getSize());

	for (int i = 0; i < mesh_data.size(); i++)
	{
		writer->seek(chunk_start + 16 + (i * 16) + 4);
		writer->writeInt32((writer->getSize() - chunk_start) - name_table_offset);
		writer->seek(writer->getSize());

		mesh_data[i]->WriteName(writer);
	}

	StreamUtil::PadFileStream(writer, 32);

	// Chunk size
	writer->seek(chunk_start + 4);
	writer->writeInt32(writer->getSize() - chunk_start);

	writer->seek(writer->getSize());
}