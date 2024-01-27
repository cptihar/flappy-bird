#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SFML/Graphics.hpp>

#include <vector>
#include <memory>

#define  PATH_TO_BACKGROUND_IMAGE  "res/BackgroundImage.png"
#define  BACKGROUND_AMOUNT         2
#define	 BACKGROUND_SPEED		   1.0f

class Background
{
	public:
		Background(const sf::Vector2u WindowSize);
		~Background();

		void renderBackgrounds(sf::RenderTarget& target);
		void updateBackgrounds();

	private:
		// Variables
		std::vector<sf::Sprite>		  m_BackgroundVector;
		std::unique_ptr<sf::Texture>  m_BackgroundTexture;
		const sf::Vector2u			  m_WindowSize;

	private:
		// Functions
		void m_initBackgroundVector();
};
#endif // !BACKGROUND_H