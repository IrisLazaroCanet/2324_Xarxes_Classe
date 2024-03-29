#include "Button.h"

Button::Button(float x, float y, std::string texturePath)
{
	//Carregar textura
	if (!texture.loadFromFile(texturePath))
	{
		//Handle error
		return;
	}

	//Si volem, podem comprovar que la textura sigui prou gran.

	//Posicionar bot�
	//setPostion ve heredada de Transformable. SFML est� preparada per fer jocs i t� el sistema de Transform
	this->setPosition(x, y);
	this->setTexture(texture);
	isHovered = false;
}

bool Button::CheckBounds(unsigned int x, unsigned int y)
{
	return this->getGlobalBounds().contains(x, y);
}
