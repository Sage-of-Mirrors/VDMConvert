#include "model/vmodel.h"

VModel::VModel(const std::string file_path)
{
	const struct aiScene* scene = aiImportFile(file_path.data(), 0);

	std::experimental::filesystem::path path = std::experimental::filesystem::path(file_path);

	std::experimental::filesystem::path dir = path.parent_path();
	std::experimental::filesystem::path file_name = path.filename().replace_extension("");
	std::experimental::filesystem::path json_path = path.parent_path().append(file_name.concat(".json"));

	std::experimental::filesystem::directory_iterator test = std::experimental::filesystem::directory_iterator(dir);

	for (auto& p : test) {
		if (p.path() == json_path) {
			std::ifstream strm(json_path.c_str());
		}
	}

	vertData = new VVertexData(scene->mMeshes, scene->mNumMeshes);
	geomData = new VGeometry(scene->mMeshes, scene->mNumMeshes, vertData);
	sceneData = new VScenegraph(scene->mRootNode);

	aiReleaseImport(scene);
}

VModel::~VModel()
{
	delete vertData;
	delete geomData;
	delete sceneData;
}

void VModel::WriteVDM(const std::string file_path)
{
	bStream::CFileStream* writer = new bStream::CFileStream(file_path, bStream::Big, bStream::Out);

	writer->writeUInt32(id); // The FourCC of the model file, 'VDMD'
	writer->writeInt32(0); // Placeholder for file size
	writer->writeInt32(1); // Number of chunks, currently 1 (vertex data)
	writer->writeInt32(-1); // Padding, it will be -1 for now

	vertData->Write(writer);
	geomData->Write(writer);
	sceneData->Write(writer);

	writer->seek(4);
	writer->writeInt32(writer->getSize()); // Write file size

	writer->getStream().flush();
	delete writer;
}