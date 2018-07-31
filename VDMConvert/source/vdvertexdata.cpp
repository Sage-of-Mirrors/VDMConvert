#include "../include/vdvertexdata.h"

VDVertexData::VDVertexData(aiMesh** meshes, int count) {
	Attributes.append(new VDVertexAttributeT<aiVector3D>(AttributeID::POSITION, 4));

	for (int i = 0; i < count; i++)
	{
		const aiMesh* mesh = meshes[i];
		auto positions = static_cast<VDVertexAttributeT<aiVector3D>*>(Attributes[0]);
		positions->AddData(mesh->mVertices, mesh->mNumVertices);
		
		if (mesh->HasNormals())
		{
			auto normals = static_cast<VDVertexAttributeT<aiVector3D>*>(GetAttribute(AttributeID::NORMAL));

			if (normals == nullptr)
			{
				normals = new VDVertexAttributeT<aiVector3D>(AttributeID::NORMAL, 4);
				Attributes.append(normals);
			}

			normals->AddData(mesh->mNormals, mesh->mNumVertices);
		}

		if (mesh->HasVertexColors(0))
		{
			auto vtxColors0 = static_cast<VDVertexAttributeT<aiColor4D>*>(GetAttribute(AttributeID::COLOR_0));

			if (vtxColors0 == nullptr)
			{
				vtxColors0 = new VDVertexAttributeT<aiColor4D>(AttributeID::COLOR_0, 5);
				Attributes.append(vtxColors0);
			}

			vtxColors0->AddData(mesh->mColors[0], mesh->mNumVertices);
		}

		if (mesh->HasVertexColors(1))
		{
			auto vtxColors1 = static_cast<VDVertexAttributeT<aiColor4D>*>(GetAttribute(AttributeID::COLOR_1));

			if (vtxColors1 == nullptr)
			{
				vtxColors1 = new VDVertexAttributeT<aiColor4D>(AttributeID::COLOR_1, 5);
				Attributes.append(vtxColors1);
			}

			vtxColors1->AddData(mesh->mColors[1], mesh->mNumVertices);
		}

		for (int j = 0; j < 8; j++)
		{
			if (mesh->HasTextureCoords(j))
			{
				auto texCoords = static_cast<VDVertexAttributeT<aiVector3D>*>(GetAttribute((AttributeID)((int)AttributeID::TEX_0 + j)));

				if (texCoords == nullptr)
				{
					texCoords = new VDVertexAttributeT<aiVector3D>((AttributeID)((int)AttributeID::TEX_0 + j), 4);
					Attributes.append(texCoords);
				}

				texCoords->AddData(mesh->mTextureCoords[j], mesh->mNumUVComponents[j]);
			}
		}
	}
}

VDVertexData::~VDVertexData() {

}

VDVertexAttributeBase* VDVertexData::GetAttribute(AttributeID attribId) {
	for (int i = 0; i < Attributes.size(); i++)
	{
		if (Attributes[i]->GetAttributeId() == attribId)
			return Attributes[i];
	}

	return nullptr;
}

void VDVertexData::Write() {

}