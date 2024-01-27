#ifndef POINTS_H
#define POINTS_H

#include <SFML/Graphics.hpp>

#include <sstream>

#define PATH_TO_FONT	"res/GameFont.ttf"
#define CHARACTER_SIZE  50

namespace xd {
	class Points
	{
		public:
			Points(int wnHeight);
			~Points();

			void updatePointText(uint32_t points);
			void renderPoints(sf::RenderTarget& target);

		private:
			// Variables
			sf::Font		   m_Font;
			sf::Text		   m_Text;
	};
}
#endif // !POINTS_H