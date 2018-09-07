#include "../../../include/model/scenegraph/scenenode.h"

SceneNode::SceneNode() {
	mParent = nullptr;
	mName = "default_node_name";

	mTranslation = aiVector3D(0.0f, 0.0f, 0.0f);
	mScale = aiVector3D(1.0f, 1.0f, 1.0f);
	mRotation = aiVector3D(0.0f, 0.0f, 0.0f);
}

SceneNode::SceneNode(aiNode * source, SceneNode * parent, CArrayT<SceneNode *> * flat_list) {
	flat_list->append(this);

	mParent = parent;
	mName = source->mName.data;

	source->mTransformation.Decompose(mScale, mRotation, mTranslation);

	for (int i = 0; i < source->mNumChildren; i++) {
		mChildren.append(new SceneNode(source->mChildren[i], this, flat_list));
	}
}

void SceneNode::Write(bStream::CFileStream * writer, CArrayT<SceneNode *> flat_scenegraph, CArrayT<SceneNodeIndexHolder> index_holders) {
	// Transform
	writer->writeFloat(mTranslation.x);
	writer->writeFloat(mTranslation.y);
	writer->writeFloat(mTranslation.z);

	writer->writeFloat(mRotation.x);
	writer->writeFloat(mRotation.y);
	writer->writeFloat(mRotation.z);

	writer->writeFloat(mScale.x);
	writer->writeFloat(mScale.y);
	writer->writeFloat(mScale.z);

	// Placeholder for name offset
	writer->writeInt32(0);
	
	// Parent index
	if (mParent == nullptr) {
		writer->writeInt16(-1);
	}
	else {
		size_t parent_index = 0;
		flat_scenegraph.contains(mParent, &parent_index);
		writer->writeInt16(parent_index);
	}

	// Placeholder for next sibling index
	writer->writeInt16(-1);

	// Children count and first child index
	int num_children = mChildren.size();
	writer->writeInt16(num_children);

	if (num_children == 0) {
		writer->writeInt16(-1);
	}
	else {
		size_t first_child_index = 0;
		flat_scenegraph.contains(mChildren[0], & first_child_index);
		writer->writeInt16(first_child_index);
	}

	// Index holders count and first index
	writer->writeInt16(mSceneNodeIndices.size());
	
	size_t first_holder_index = 0;
	//index_holders.contains(*mSceneNodeIndices[0], &first_holder_index);
	writer->writeInt16(first_holder_index);

	// Children
	for (int i = 0; i < num_children; i++) {
		// Record the current offset, write a child, and then record the offset after that.
		long child_offset = writer->getSize();
		mChildren[i]->Write(writer, flat_scenegraph, index_holders);
		long next_offset = writer->getSize();

		// Go to the "next sibling" field and write the next index value.
		// (or -1 if 
		writer->seek(child_offset + 0x2A);
		
		if (i + 1 == num_children) {
			writer->writeInt16(-1);
		}
		else {
			size_t next_child_index = 0;
			flat_scenegraph.contains(mChildren[i + 1], &next_child_index);
			writer->writeInt16(next_child_index);

			writer->writeInt16(i + 1);
		}

		writer->seek(next_offset);
	}
}

bool operator==(const SceneNodeIndexHolder & lhs, const SceneNodeIndexHolder & rhs) {
	return lhs.MaterialIndex == rhs.MaterialIndex && lhs.MeshIndex == rhs.MeshIndex && lhs.SkinningIndex == rhs.SkinningIndex;
}

bool operator==(const SceneNode & lhs, const SceneNode & rhs) {
	return lhs.mName == rhs.mName && lhs.mTranslation == rhs.mTranslation && lhs.mRotation == rhs.mRotation
		&& lhs.mScale == rhs.mScale;
}