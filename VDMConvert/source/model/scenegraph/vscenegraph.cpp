#include "../../../include/model/scenegraph/vscenegraph.h"

VScenegraph::VScenegraph(aiNode * scene_root) {
	aiNode * skeleton_root = nullptr;

	for (int i = 0; i < scene_root->mNumChildren; i++) {
		if (scene_root->mChildren[i]->mName == aiString("skeleton_root")) {
			skeleton_root = scene_root->mChildren[i];
		}
	}

	if (skeleton_root == nullptr) {
		// do something
		return;
	}

	mRootNode = new SceneNode(skeleton_root, nullptr, &mNodes);
}

void VScenegraph::Write(bStream::CFileStream * writer) {
	long chunk_start = writer->getSize();

	writer->writeUInt32(id);
	writer->writeInt32(0);
	writer->writeInt32(mNodes.size());
	for (int i = 0; i < 5; i++) {
		writer->writeInt32(0);
	}

	mRootNode->Write(writer, mNodes, NULL);

	// Chunk size
	writer->seek(chunk_start + 4);
	writer->writeInt32(writer->getSize() - chunk_start);

	writer->seek(writer->getSize());
}