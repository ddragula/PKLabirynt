#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include "util.h"

class Labirynt
{
private:
	char** data;
	uint width;
	uint height;
public:
	Labirynt();
	~Labirynt();
	void LoadFromFile(const std::string& filename);
	char GetData(uint x, uint y) const;
	uint GetWidth() const;
	uint GetHeight() const;
private:
	std::pair<bool, Vector<uint>> VerifyFileSyntax(std::ifstream& ifile);
	void FetchDataFromFile(std::ifstream& ifile, char**& refData);
};