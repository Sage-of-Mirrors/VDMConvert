#pragma once

#include "scenenode.h"
#include "../../util/array.h"
#include "../../util/bstream.h"

class VScenegraph {
private:
	const int id = 1448297294;

	SceneNode * mRootNode;
	CArrayT<SceneNode *> mNodes;
public:
	VScenegraph();
	VScenegraph(aiNode * scene_root);

	void Write(bStream::CFileStream * writer);
};