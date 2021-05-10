#include "App.h"

App::App() : offsetX(0), offsetY(0), scale(1), labirynt(), startPoint(), endPoint(), labCoordsLastClick({ 0, 0 })
{
	sAppName = "Labirynt / JPiA2 L10 / Dawid Dragula";
}

App::~App()
{

}

App::Point::Point() : position({ 0, 0 }), visible(false)
{
}

bool App::OnUserCreate()
{
	offsetX = 3;
	offsetY = 3;
	scale = 5;

	labirynt.LoadFromFile("labirynt1.txt");


	return true;
}

bool App::OnUserUpdate(float fElapsedTime)
{
	DrawLabirynt();
	HandleInput();
	DrawPoints();



	return true;
}

void App::DrawLabirynt()
{
	for (int i = 0; i < labirynt.GetWidth(); i++)
	{
		for (int j = 0; j < labirynt.GetHeight(); j++)
		{
			olc::Pixel px;
			switch (labirynt.GetData(i, j))
			{
			case '0':
				px = olc::Pixel(255, 255, 255);
				break;
			default:
				px = olc::Pixel(0, 0, 0);
			}

			for (int k = 0; k < scale; k++)
			{
				for (int l = 0; l < scale; l++)
				{
					Draw(i * scale + k + offsetX, j * scale + l + offsetY, px);
				}
			}
		}
	}
}

void App::DrawPoints()
{
	if (startPoint.visible)
	{
		for (int k = 0; k < scale; k++)
		{
			for (int l = 0; l < scale; l++)
			{
				Draw(startPoint.position.x * scale + k + offsetX, startPoint.position.y * scale + l + offsetY, olc::Pixel(0, 255, 0));
			}
		}
	}

	if (endPoint.visible)
	{
		for (int k = 0; k < scale; k++)
		{
			for (int l = 0; l < scale; l++)
			{
				Draw(endPoint.position.x * scale + k + offsetX, endPoint.position.y * scale + l + offsetY, olc::Pixel(255, 0, 0));
			}
		}
	}
}

void App::HandleInput()
{
	if (GetMouse(0).bHeld)
	{
		labCoordsLastClick = { (GetMouseX() - offsetX) / scale, (GetMouseY() - offsetY) / scale };
		if (labirynt.GetData(labCoordsLastClick.x, labCoordsLastClick.y) == '1')
		{
			startPoint.position = labCoordsLastClick;
			startPoint.visible = true;
		}
	}

	if (GetMouse(1).bHeld)
	{
		labCoordsLastClick = { (GetMouseX() - offsetX) / scale, (GetMouseY() - offsetY) / scale };
		if (labirynt.GetData(labCoordsLastClick.x, labCoordsLastClick.y) == '1')
		{
			endPoint.position = labCoordsLastClick;
			endPoint.visible = true;
		}
	}
}
