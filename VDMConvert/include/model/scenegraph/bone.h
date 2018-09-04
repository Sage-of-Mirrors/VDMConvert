#pragma once
#include <assimp/scene.h>
#include "../../util/bstream.h"
#include "../../util/array.h"

class Bone {
private:
	aiVector3D mTranslation;
	aiVector3D mScale;
	aiVector3D mRotation;

	Bone * mParent;
	CArrayT<Bone> mChildren;
	std::string mName;
public:
	Bone();
	Bone(aiNode * source, Bone * parent);

	void Write(bStream::CFileStream * writer);
};