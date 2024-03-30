#pragma once
#include "../WindowsHelpers/Window.h"
#include "Grid.h"

class Game {
public:
	Game();
	~Game();
	void Init(Window &window);

	Grid* grid;
};