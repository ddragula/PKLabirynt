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
	scale = 3;

	labirynt.LoadFromFile("labirynt1.txt");

	return true;
}

bool App::OnUserUpdate(float fElapsedTime)
{
	Clear(olc::Pixel(0, 0, 0));
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
			bool walls;
			olc::Pixel px;
			switch (labirynt.GetData(i, j))
			{
			case '0':
				px = olc::Pixel(255, 255, 255);
				walls = true;
				break;
			case '+':
				px = olc::Pixel(255, 255, 0);
				walls = false;
				break;
			case '-':
				px = olc::Pixel(50, 50, 50);
				walls = false;
				break;
			default:
				px = olc::Pixel(0, 0, 0);
				walls = true;
			}

			for (int k = 0; k < scale; k++)
			{
				for (int l = 0; l < scale; l++)
				{
					if (!walls)
					{
						if (k == scale / 2 && l == scale / 2)
						{
							Draw(i * scale + k + offsetX, j * scale + l + offsetY, px);
						}
					}
					else
					{
						Draw(i * scale + k + offsetX, j * scale + l + offsetY, px);
					}
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
		if (labirynt.GetData(labCoordsLastClick.x, labCoordsLastClick.y) != '0')
		{
			startPoint.position = labCoordsLastClick;
			startPoint.visible = true;
			if (endPoint.visible == true)
			{
				labirynt.SetStartAndFinish(startPoint.position, endPoint.position);
			}
		}
	}

	if (GetMouse(1).bHeld)
	{
		labCoordsLastClick = { (GetMouseX() - offsetX) / scale, (GetMouseY() - offsetY) / scale };
		if (labirynt.GetData(labCoordsLastClick.x, labCoordsLastClick.y) != '0')
		{
			endPoint.position = labCoordsLastClick;
			endPoint.visible = true;
			if (startPoint.visible == true)
			{
				labirynt.SetStartAndFinish(startPoint.position, endPoint.position);
			}
		}
	}
}
