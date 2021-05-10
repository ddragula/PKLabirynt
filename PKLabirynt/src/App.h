#pragma once
#include "olcPixelGameEngine.h"
#include "Labirynt.h"

class App : public olc::PixelGameEngine
{
private:
	struct Point
	{
		Vector<uint> position;
		bool visible;
		Point();
	};
public:
	App();
	~App();
public:
	bool OnUserCreate() override;
	bool OnUserUpdate(float fElapsedTime) override;
private:
	uint offsetX, offsetY, scale;
	Point startPoint;
	Point endPoint;
	Vector<uint> labCoordsLastClick;
	Labirynt labirynt;
private:
	void DrawLabirynt();
	void DrawPoints();
	void HandleInput();
};

