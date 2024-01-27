#include "Background.h"

Background::Background(const sf::Vector2u WindowSize)
	:m_WindowSize(WindowSize),
	 m_BackgroundTexture(std::make_unique<sf::Texture>())
{
	m_initBackgroundVector();
}

Background::~Background()
{
}


/*
* ==============================================
* 
* Renders the background vector to the screen
* Called by:
*    -> Window::Render
*	 -> Call happens every frame
* 
* Return: void
* 
* ==============================================
*/
void Background::renderBackgrounds(sf::RenderTarget& target)
{
	for (const auto& b : m_BackgroundVector) 
		target.draw(b);
}


/*
* ==============================================
* 
* Updates the background vector and sprites
* Adds "infinite" animation to the background
* Called by:
*	-> Window::MainLoop
*	-> Call happens every frame
* 
* Return: void
* 
* ==============================================
*/
void Background::updateBackgrounds()
{
	// Move backgrounds
	for (auto& b : m_BackgroundVector) {
		b.move(-BACKGROUND_SPEED, 0.0f);
	}

	sf::Sprite FrontSprite = m_BackgroundVector.front(); // Cache the element at the beginning

	// Check whether the first element should be repositioned (is out of bounds)
	if (FrontSprite.getPosition().x < -FrontSprite.getGlobalBounds().width) {
		float newpositionX = m_BackgroundVector.back().getPosition().x + FrontSprite.getGlobalBounds().width;

		FrontSprite.setPosition(newpositionX, 0.0f);

		// Send front to the back
		m_BackgroundVector.push_back(FrontSprite);
		m_BackgroundVector.erase(m_BackgroundVector.begin());
	}
}


/*
* =========================================
* 
* Initializes the background vector
* Sets the position of the sprites
* Initilizes the size of the background
* 
* Called by:
*	-> Constructor
* 
* Return: void
* 
* =========================================
*/
void Background::m_initBackgroundVector()
{
	m_BackgroundTexture->loadFromFile(PATH_TO_BACKGROUND_IMAGE);

	sf::Sprite bgSprite;
	bgSprite.setTexture(*m_BackgroundTexture);

	// Calculate ratio
	float scaleX = m_WindowSize.x / bgSprite.getGlobalBounds().width;
	float scaleY = m_WindowSize.y / bgSprite.getGlobalBounds().height;

	// Set scale
	bgSprite.scale(scaleX, scaleY);

	// Load vector
	for (uint8_t i = 0; i < BACKGROUND_AMOUNT; ++i) {

		bgSprite.setPosition(static_cast<float>(bgSprite.getGlobalBounds().width * i),
						     0.0f);
		m_BackgroundVector.push_back(bgSprite);
	}
}