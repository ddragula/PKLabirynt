#define OLC_PGE_APPLICATION
#include "App.h"

int main()
{
	App labiryntApp;
	if (labiryntApp.Construct(100, 100, 8, 8))
	{
		labiryntApp.Start();
	}

	return 0;
}