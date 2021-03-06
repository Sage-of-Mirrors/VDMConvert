#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "model/vmodel.h"

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
	VModel* model = new VModel("D:\\Game_Shapes\\cube_test.dae");
	model->WriteVDM("D:\\Github\\VDMConvert\\test.vdm");

    return 0;
}

