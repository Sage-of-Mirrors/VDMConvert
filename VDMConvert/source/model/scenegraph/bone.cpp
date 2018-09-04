#include "../../../include/model/scenegraph/bone.h"

Bone::Bone() {
	mParent = nullptr;

	mTranslation = aiVector3D(0.0f, 0.0f, 0.0f);
	mScale = aiVector3D(1.0f, 1.0f, 1.0f);
	mRotation = aiVector3D(0.0f, 0.0f, 0.0f);
}

Bone::Bone(aiNode * source, Bone * parent) {
	mParent = parent;

	source->mTransformation.Decompose(mScale, mRotation, mTranslation);
}