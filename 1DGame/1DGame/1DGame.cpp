//
// Software Engineering final practica
//
// Author: Andres Molina Lopez
//
// Description: The main goal of project is to create a simple game in 1D 
// in which you control a character 'X' that can move along a line '------'
// in both directions. During the game, enemies '*' will appear in the line 
// trying to reach this character. Your mission is to kill them before they 
// catch you because you only have 1 life and you lose it if an enemy touch 
// you. In order to kill them, you can shoot bullets '<' or '>' but only 5 
// in the same direction at the same time.
//
// Controllers: 
// - Move left -> h // Move right -> l
// - Shoot left -> j // Shoot right -> k
// 

#include "Managers/world.h"
#include "Managers/graphics.h"
#include <Windows.h>

int main()
{
	CGraphics::GetInstance().Init();
	CWorld::GetInstance().Init();
	
	while (!CWorld::GetInstance().GetExit())
	{
		CWorld::GetInstance().Update();
		CGraphics::GetInstance().Update();

		Sleep(50); // Force 20 fps
	}

	CWorld::GetInstance().Terminate();
	CGraphics::GetInstance().Terminate();

	return 0;
}
