#include "Labirynt.h"

Labirynt::Labirynt() : data(nullptr), width(0), height(0), moveCounter(0), sc({ 0, 0 }), finish({ 0, 0 })
{
}

Labirynt::~Labirynt()
{
	for (int i = 0; i < width; i++)
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
		std::cout << "[ERROR] Cannot read data from a file \"" << filename << "\"" << std::endl;
		return;
	}

	{
		auto verifyResult = VerifyFileSyntax(ifile);
		if (!verifyResult.first) {
			std::cout << "[ERROR] Invalid syntax of a file \"" << filename << "\"" << std::endl;
			return;
		}

		width = verifyResult.second.x;
		height = verifyResult.second.y;
	}

	data = new char*[width];
	for (int i = 0; i < width; i++) {
		data[i] = new char[height];
	}

	FetchDataFromFile(ifile, data);
}

char Labirynt::GetData(uint x, uint y) const
{
	if (x > width - 1 || y > height - 1) {
		return '0';
	}

	return data[x][y];
}

uint Labirynt::GetWidth() const
{
	return width;
}

uint Labirynt::GetHeight() const
{
	return height;
}

bool Labirynt::SetStartAndFinish(const Vector<uint>& start, const Vector<uint>& finish)
{
	ClearPath();
	this->finish = finish;
	bool result = SeekStep(start.x, start.y);
	std::cout << "[RESULT] The path " << (result ? "was" : "was not") << " found. Steps: " << moveCounter << std::endl;
	return result;
}

bool Labirynt::SeekStep(uint x, uint y)
{
	moveCounter++;
	data[x][y] = '+';

	if (x == finish.x && y == finish.y) return true;

	if (GetData(x + 1, y) == '1')
	{
		if (SeekStep(x + 1, y)) return true;
	}

	if (GetData(x, y + 1) == '1')
	{
		if (SeekStep(x, y + 1)) return true;
	}

	if (GetData(x - 1, y) == '1')
	{
		if (SeekStep(x - 1, y)) return true;
	}

	if (GetData(x, y - 1) == '1')
	{
		if (SeekStep(x, y - 1)) return true;
	}

	data[x][y] = '-';
	return false;
}

void Labirynt::ClearPath()
{
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			if (data[i][j] == '+' || data[i][j] == '-')
			{
				data[i][j] = '1';
			}
		}
	}

	moveCounter = 0;
}

std::pair<bool, Vector<uint>> Labirynt::VerifyFileSyntax(std::ifstream& ifile)
{
	bool valid = true;
	uint width = 0;
	uint height = 0;

	ifile.seekg(0, std::ios::beg);
	while (!ifile.eof() && valid)
	{
		std::string line;
		ifile >> line;
		uint lineSize = line.size();
		if (lineSize > 0)
		{
			if (width == 0 || width == lineSize)
			{
				height++;
			}
			else
			{
				valid = false;
			}

			width = lineSize;
		}
	}

	return std::pair<bool, Vector<uint>>(valid, { width, height });
}

void Labirynt::FetchDataFromFile(std::ifstream& ifile, char**& refData)
{
	ifile.seekg(0, std::ios::beg);
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			ifile >> refData[i][j];
		}
	}
}
