#pragma once
#include <list>
#include <mutex>
#include "Button.h"

typedef std::function<void()> Task;

#define WINDOW_WIDTH = 800
#define WINDOW_HEIGHT = 800

class Window
{
	//TODO: Crear sistema de dispatcher

public:
	/// <summary>
	/// El constructor crea la finestra. No es pot tocar la finestra des d'un altre thread que no sigui el que la ha creat.
	/// </summary>
	/// <param name="width"></param>
	/// <param name="height"></param>
	/// <param name="title"></param>
	Window(unsigned int width = 800, unsigned int height = 600, std::string title = "Window");

	void AddButton(Button* bt);
	void AddDrawable(sf::Drawable* drawable);
	void AddTempDrawable(sf::Drawable* tempDrawable);
	void ClearTempDrawables();
	void RunWindowsLoop();

	//LAMBDA TASKS
	void AddTask(Task task);

private:
	//LAMBDA TASKS
	std::mutex _taskMutex;
	std::vector<Task> _tasks;

	//Posar un mutex global per tot el sistema de finestres funciona, per� no �s el m�s eficient:
	//mentre aquest mutex estigui bloquejat, no podrem fer res m�s
	//TODO: Crear m�s mutex
	std::mutex _mutex;
	sf::RenderWindow _window;

	Button* _lastClickedDownButton;
	std::list<Button*> _buttons;

	//T�cnicament, com que el bot� �s drawable, podr�em posar-lo aqu�.
	//Per� no seria eficient, ja que quan volgu�ssim comprovar si s'ha clicat un bot� haur�em d'iterar per tots els drawables
	std::list<sf::Drawable*> _objectsToDraw;

	std::list<sf::Drawable*> _tempObjectsToDraw;
};

