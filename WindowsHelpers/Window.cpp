#include "Window.h"

Window::Window(unsigned int width, unsigned int height, std::string title)
{
	_window.create(sf::VideoMode(width, height), title);

	//TODO: Afegir al constructor tot el que calgui. 
}

void Window::AddButton(Button* bt)
{
	_mutex.lock();

	_buttons.push_back(bt);

	//Posicions a la lista com a Z-Buffer. Haur� d'anar canviant: si pintem el taulell i despr�s movem un bot�,
	//haurem d'ajustar el bot� perqu� estigui a dalt de tot (bringToFront). 
	//Caldr� gestionar aquest bringToFront. 
	//Recomanaci�: que la posici� dels botons tingui una posici� relativa: pujar el bot� a la llista _buttons i a _objectsToDraw
	//Haurem de rec�rrer la llista de dreta (final) a esquerra (inici) per pintar correctament els objectes en ordre
	_objectsToDraw.push_back(bt);

	_mutex.unlock();
}

void Window::AddDrawable(sf::Drawable* drawable)
{
	_mutex.lock();
	_objectsToDraw.push_front(drawable);
	_mutex.unlock();
}

void Window::AddTempDrawable(sf::Drawable* tempDrawable)
{
	_mutex.lock();
	_tempObjectsToDraw.push_front(tempDrawable);
	_mutex.unlock();
}

void Window::ClearTempDrawables()
{
	_mutex.lock();
	_tempObjectsToDraw.clear();
	_mutex.unlock();
}

void Window::RunWindowsLoop()
{
	//TODO: Fer aquesta funci� thread safe

	//Com si fos l'update de unity.
	//Hem de gestionar si volem que es pintin diverses coses en diferents moments:
	//Lista de lambdas per l'update, llista de lambdas pel fixed update, llista de lambdas per el start...
	//Tanmateix, per la pr�ctica no cal complicar-se
	while (_window.isOpen())
	{
		_window.clear(sf::Color::Black);

		for (sf::Drawable* drawable : _objectsToDraw)
		{
			//Idealment, aquest if no hauria d'estar: haur�em d'estar segurs que els objectes que entren aqu� no es borren
			//Per� com que estem treballant amb punters, �s millor prevenir
			if (drawable != nullptr)
			{
				//T�cnicament no est� pintant per pantalla.
				//Est� pintant al Z-Buffer de deb�, l'intern.
				_window.draw(*drawable);
			}
		}

		for (sf::Drawable* tempDrawable : _tempObjectsToDraw)
		{
			if (tempDrawable != nullptr)
			{
				_window.draw(*tempDrawable);
			}
		}

		//Pintar, ara s�, la pantalla
		_window.display();

		sf::Event event;
		while (_window.pollEvent(event))
		{
			//TODO: Fer de manera m�s elegant
			//TODO: Crear funcions enlloc de ficar-ho dins dels cases del switch
			//TODO: Afegir la resta de event types que ens caldran
			switch (event.type)
			{
				case sf::Event::Closed:
				{
					_window.close();
					break;
				}
				case sf::Event::MouseButtonPressed:
				{
					if (event.mouseButton.button == sf::Mouse::Left)
					{
						//Com que estem fent un joc en 2D, probablement no mourem el m�n
						//Per si de cas, passem el pixel de la posici� del ratol� a world coords
						sf::Vector2i clickPixelPos = { event.mouseButton.x, event.mouseButton.y };
						sf::Vector2f worldPos = _window.mapPixelToCoords(clickPixelPos);

						//Com hem dit anteriorment, cal iterar la llista a l'inrev�s
						for (auto it = _buttons.rbegin(); it != _buttons.rend(); it++)
						{
							Button* bt = *it;
							if (bt->CheckBounds(worldPos.x, worldPos.y))
							{
								_lastClickedDownButton = bt;
								break;
							}
						}
					}
					break;
				}
				case sf::Event::MouseButtonReleased:
				{
					if (event.mouseButton.button == sf::Mouse::Left)
					{
						//Com que estem fent un joc en 2D, probablement no mourem el m�n
						//Per si de cas, passem el pixel de la posici� del ratol� a world coords
						sf::Vector2i clickPixelPos = { event.mouseButton.x, event.mouseButton.y };
						sf::Vector2f worldPos = _window.mapPixelToCoords(clickPixelPos);

						if (_lastClickedDownButton != nullptr && _lastClickedDownButton->CheckBounds(worldPos.x, worldPos.y))
						{
							_lastClickedDownButton->onClick();
						}
						else
						{
							//TODO: Cancel click or drag or others
						}
					}
					break;
				}
				case sf::Event::MouseMoved:
				{
					sf::Vector2i clickPixelPos = { event.mouseMove.x, event.mouseMove.y };
					sf::Vector2f worldPos = _window.mapPixelToCoords(clickPixelPos);

					for (auto it = _buttons.rbegin(); it != _buttons.rend(); it++)
					{
						Button* bt = *it;
						if (bt->CheckBounds(worldPos.x, worldPos.y) && !bt->IsHovered())
						{
							bt->onHoverEnter();
							bt->ChangeHovered();
							break;
						}
						else if (!bt->CheckBounds(worldPos.x, worldPos.y) && bt->IsHovered())
						{
							bt->onHoverExit();
							bt->ChangeHovered();
							break;
						}
					}
					break;
				}
				case sf::Event::MouseWheelScrolled:
				{
					//TODO: Handle MouseWheelScrolled
					break;
				}
			}
		}

		//Execute all tasks
		_taskMutex.lock();
		size_t size = _tasks.size();
		for (int i = 0; i < size; i++)
		{
			_tasks[i]();
		}
		//Com que s�n tasques d'un sol �s, cal netejar la llista despr�s del for (ja s'han executat les tasques)
		_tasks.clear();
		_taskMutex.unlock();
	}
}

void Window::AddTask(Task task)
{
	_taskMutex.lock();
	_tasks.push_back(task);
	_taskMutex.unlock();
}

