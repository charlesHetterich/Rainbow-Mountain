#include "stdafx.h"
#include "Data.h"

CData::CData()
{
}


CData::~CData()
{
}

//std::string CData::load(std::string fileName)
int CData::load(std::string fileName)
{
	std::ifstream infile;
	infile.open(fileName);
	if (infile.fail())
	{
		std::cerr << "error opening file\n";
		//exit(1);
	}

	int output;

	infile >> output;

	infile.close();

	return output;
}
void CData::save(std::string fileName, int input)
{
	std::ofstream outfile;
	outfile.open(fileName);
	if (outfile.fail())
	{
		std::cerr << "error opening file\n";
		//exit(1);
	}

	outfile << input;

	outfile.close();
}
