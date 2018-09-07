#pragma once
#include <assimp/scene.h>
#include "../../util/bstream.h"
#include "../../util/array.h"

struct SceneNodeIndexHolder {
	uint16_t SkinningIndex;
	uint16_t MaterialIndex;
	uint16_t MeshIndex;

	friend bool operator==(const SceneNodeIndexHolder & lhs, const SceneNodeIndexHolder & rhs);
};

class SceneNode {
private:
	aiVector3D mTranslation;
	aiVector3D mScale;
	aiVector3D mRotation;

	SceneNode * mParent;
	CArrayT<SceneNode *> mChildren;

	CArrayT<SceneNodeIndexHolder *> mSceneNodeIndices;

	std::string mName;
public:
	SceneNode();
	SceneNode(aiNode * source, SceneNode * parent, CArrayT<SceneNode *> * flat_list);

	friend bool operator==(const SceneNode & lhs, const SceneNode & rhs);

	void Write(bStream::CFileStream * writer, CArrayT<SceneNode *> flat_scenegraph, CArrayT<SceneNodeIndexHolder> index_holders);
};