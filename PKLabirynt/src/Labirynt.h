#pragma once
#include <string>
#include "util.h"
#include <fstream>

class Labirynt
{
private:
	char** data;
	Vector<uint> dimension;
public:
	Labirynt();
	~Labirynt();
	void LoadFromFile(const std::string& filename);
	char** GetData() const;
	Vector<uint> GetDimension() const;
private:
	std::pair<bool, Vector<uint>> VerifyFileSyntax(const std::ifstream& ifile);
	void FetchDataFromFile(const std::ifstream& ifile, char**& refData);
};