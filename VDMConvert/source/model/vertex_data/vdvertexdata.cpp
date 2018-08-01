#include "../include/model/vertex_data/vdvertexdata.h"

VDVertexData::VDVertexData(aiMesh** meshes, int count) {
	Attributes.append(new VDVertexAttributeVector3(AttributeID::POSITION, 4));

	for (int i = 0; i < count; i++)
	{
		const aiMesh* mesh = meshes[i];
		auto positions = static_cast<VDVertexAttributeT<aiVector3D>*>(Attributes[0]);
		positions->AddData(mesh->mVertices, mesh->mNumVertices);
		
		if (mesh->HasNormals())
		{
			auto normals = static_cast<VDVertexAttributeVector3*>(GetAttribute(AttributeID::NORMAL));

			if (normals == nullptr)
			{
				normals = new VDVertexAttributeVector3(AttributeID::NORMAL, 4);
				Attributes.append(normals);
			}

			normals->AddData(mesh->mNormals, mesh->mNumVertices);
		}

		if (mesh->HasVertexColors(0))
		{
			auto vtxColors0 = static_cast<VDVertexAttributeColor4*>(GetAttribute(AttributeID::COLOR_0));

			if (vtxColors0 == nullptr)
			{
				vtxColors0 = new VDVertexAttributeColor4(AttributeID::COLOR_0, 5);
				Attributes.append(vtxColors0);
			}

			vtxColors0->AddData(mesh->mColors[0], mesh->mNumVertices);
		}

		if (mesh->HasVertexColors(1))
		{
			auto vtxColors1 = static_cast<VDVertexAttributeColor4*>(GetAttribute(AttributeID::COLOR_1));

			if (vtxColors1 == nullptr)
			{
				vtxColors1 = new VDVertexAttributeColor4(AttributeID::COLOR_1, 5);
				Attributes.append(vtxColors1);
			}

			vtxColors1->AddData(mesh->mColors[1], mesh->mNumVertices);
		}

		for (int j = 0; j < 8; j++)
		{
			if (mesh->HasTextureCoords(j))
			{
				auto texCoords = static_cast<VDVertexAttributeVector2*>(GetAttribute((AttributeID)((int)AttributeID::TEX_0 + j)));

				if (texCoords == nullptr)
				{
					texCoords = new VDVertexAttributeVector2((AttributeID)((int)AttributeID::TEX_0 + j), 4);
					Attributes.append(texCoords);
				}

				std::vector<aiVector2D> converted_uvs;

				for (int i = 0; i < mesh->mNumUVComponents[j]; i++)
				{
					converted_uvs.push_back(aiVector2D(mesh->mTextureCoords[j][i].x, mesh->mTextureCoords[j][i].y));
				}

				texCoords->AddData(converted_uvs.data(), mesh->mNumUVComponents[j]);
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

void VDVertexData::Write(bStream::CFileStream* writer) {
	long curOffset = writer->tell();

	writer->writeUInt32(id);
	writer->writeInt32(0);
	writer->writeInt32(Attributes.size());
	writer->writeInt32(-1);

	for (int i = 0; i < Attributes.size(); i++)
	{
		Attributes[i]->Write(writer);
	}

	for (int i = 0; i < Attributes.size(); i++)
	{
		VDVertexAttributeBase* attr = Attributes[i];

		if (attr->GetAttributeId() == AttributeID::POSITION || attr->GetAttributeId() == AttributeID::NORMAL)
		{
			auto vec3dAttr = static_cast<VDVertexAttributeVector3*>(attr);
			vec3dAttr->WriteData(writer);
		}
		else if (attr->GetAttributeId() == AttributeID::COLOR_0 || attr->GetAttributeId() == AttributeID::COLOR_1)
		{
			auto vecColor4Attr = static_cast<VDVertexAttributeColor4*>(attr);
			vecColor4Attr->WriteData(writer);
		}
		else
		{
			auto vec2dAttr = static_cast<VDVertexAttributeVector2*>(attr);
			vec2dAttr->WriteData(writer);
		}
	}

	writer->seek(curOffset + 4);
	writer->writeInt32(writer->getSize() - curOffset);
	writer->seek(writer->getSize());
}