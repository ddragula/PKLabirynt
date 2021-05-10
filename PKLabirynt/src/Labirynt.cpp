#include "Labirynt.h"

Labirynt::Labirynt() : data(nullptr), dimension({ 0, 0 })
{
}

Labirynt::~Labirynt()
{
	for (int i = 0; i < dimension.x; i++)
	{
		delete[] data[i];
	}
	delete[] data;
}


void Labirynt::LoadFromFile(const std::string &filename)
{
	std::ifstream ifile;
	ifile.open(filename.c_str());
	if (!ifile.good())
	{
		throw std::exception(std::string("Cannot read data from file \"" + filename + "\"").c_str());
		return;
	}

	{
		auto verifyResult = VerifyFileSyntax(ifile);
		if (!verifyResult.first) {
			throw std::exception(std::string("Invalid syntax of file \"" + filename + "\"").c_str());
			return;
		}

		dimension = verifyResult.second;
	}

	FetchDataFromFile(ifile, data);
}

char** Labirynt::GetData() const
{
	return data;
}

Vector<uint> Labirynt::GetDimension() const
{
	return dimension;
}

std::pair<bool, Vector<uint>> Labirynt::VerifyFileSyntax(const std::ifstream& ifile)
{
	bool valid = true;
	uint width = 0;
	uint height = 0;



	return std::pair<bool, Vector<uint>>(true, { width, height });
}

void Labirynt::FetchDataFromFile(const std::ifstream& ifile, char**& refData)
{

}
