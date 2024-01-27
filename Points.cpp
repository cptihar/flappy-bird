#include "Points.h"

xd::Points::Points(int wnHeight)
{
	// Loading font
	m_Font.loadFromFile(PATH_TO_FONT);

	// Setting up the font
	m_Text.setFont(m_Font);
	m_Text.setFillColor(sf::Color::Red);
	m_Text.setCharacterSize(CHARACTER_SIZE);

	// Setting font position
	m_Text.setPosition(0.0f, float(wnHeight - CHARACTER_SIZE));
}

xd::Points::~Points()
{
}

void xd::Points::updatePointText(uint32_t points)
{
	std::stringstream stream;
	stream << points;
	m_Text.setString(stream.str());
}

void xd::Points::renderPoints(sf::RenderTarget& target)
{
	target.draw(m_Text);
}
