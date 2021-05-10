#pragma once
#include "olcPixelGameEngine.h"

class App : public olc::PixelGameEngine
{
public:
	App();
public:
	bool OnUserCreate() override;
	bool OnUserUpdate(float fElapsedTime) override;
};

