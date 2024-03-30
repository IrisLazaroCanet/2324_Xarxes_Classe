#include "Game.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::Init(Window& window)
{
	//Init grid & pieces
	grid = new Grid();

	//Draw board task
    Task drawBoard = [&]() {
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                sf::RectangleShape* square = new sf::RectangleShape(sf::Vector2f(600 / 8, 600 / 8));

                if ((i % 2 == 0 && j % 2 == 0) || (i % 2 == 1 && j % 2 == 1))
                    square->setFillColor(sf::Color::White);
                else
                    square->setFillColor(sf::Color::Blue);

                square->setPosition(i * 600 / 8, j * 600 / 8);

                window.AddDrawable(square);
            }
        }
    };

    //window.AddTask(drawBoard);
}
