#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "include/GX_Enums.h"
#include "include/vdvertexattribute.h"

void ShowHelpMessage()
{
	std::cout << "VDMConvert written by Sage-of-Mirrors/Gamma (@SageOfMirrors)\n";
	std::cout << "Converts models to the VDM format using assimp.\n";
	std::cout << "Works on single models and directories, with an option for directory recursion.\n";
	std::cout << "\n";
	std::cout << "Example usage:\n";
	std::cout << "VDMConvert.exe -f/--file <file path>\n";
	std::cout << "VDMConvert.exe -d/--directory <directory path> [-r/--recurse]\n";
	std::cout << "\n";
	std::cout << "Arguments:\n";
	std::cout << "-f/--file\t\tfile path\t\tSpecifies the path of a file to convert to VDM\n";
	std::cout << "-d/--directory\t\tdirectory path\t\tSpecifies the path of a directory containing files to convert to VDM\n";
	std::cout << "-r/--recurse\t\t\t\t\tSpecifies that the converter should recurse through subdirectories\n";
}

int main()
{
	const struct aiScene* scene = NULL;
	scene = aiImportFile("D:\\Game_Shapes\\cube.obj", 0);

	VDVertexAttributeT<aiVector3D> * test = new VDVertexAttributeT<aiVector3D>(AttributeID::POSITION, 4);
	for (int i = 0; i < scene->mNumMeshes; i++)
	{
		test->AddData(scene->mMeshes[i]->mVertices, scene->mMeshes[i]->mNumVertices);
	}

	CArrayT<aiVector3D> * testArray = test->GetData();

	for (int i = 0; i < testArray->size(); i++)
	{
		std::cout << "(" << testArray->at(i).x << ", " << testArray->at(i).y << ", " << testArray->at(i).z << ")\n";
	}

	delete test;
	aiReleaseImport(scene);

    return 0;
}

