#include "..\include\model\vdmodel.h"

VDModel::VDModel(const std::string file_path)
{
	const struct aiScene* scene = aiImportFile(file_path.data(), 0);

	vertData = new VDVertexData(scene->mMeshes, scene->mNumMeshes);

	aiReleaseImport(scene);
}

VDModel::~VDModel()
{
	delete vertData;
}

void VDModel::WriteVDM(const std::string file_path)
{
	bStream::CFileStream* writer = new bStream::CFileStream(file_path, bStream::Big, bStream::Out);

	writer->writeUInt32(id); // The FourCC of the model file, 'VDMD'
	writer->writeInt32(0); // Placeholder for file size
	writer->writeInt32(1); // Number of chunks, currently 1 (vertex data)
	writer->writeInt32(-1); // Padding, it will be -1 for now

	vertData->Write(writer);

	writer->seek(4);
	writer->writeInt32(writer->getSize()); // Write file size

	writer->getStream().flush();
	delete writer;
}