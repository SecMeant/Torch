#include "complexTypes.hpp"

TextButton::TextButton
(const sf::Font &font, sf::Color defC, sf::Color hc)
{
	this->text.setFont(font);
	this->setColors(defC, hc);
}

bool TextButton::clicked(const sf::Event &ev)
{
	auto mousex = ev.mouseButton.x;
	auto mousey = ev.mouseButton.y;

	if(ev.type == sf::Event::MouseButtonReleased)
	{
		return this->text.getGlobalBounds().contains(mousex, mousey);
	}
	return false;
}

void TextButton::handleHoverEvent(const sf::Event &ev)
{
	auto mousex = ev.mouseMove.x;
	auto mousey = ev.mouseMove.y;

	if(ev.type == sf::Event::MouseMoved)
	{
		if(this->text.getGlobalBounds().contains(mousex, mousey))
		{
			this->mouseEnter();
			return;
		}
		this->mouseLeave();
	}
}
