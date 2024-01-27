#ifndef PIPE_H
#define PIPE_H

#include <SFML/Graphics.hpp>

#define PIPE_SCALE_VALUE  2.0f
#define PIPE_GAP	  50.0f

class Pipe
{
	public:
		Pipe() = default;
		Pipe(sf::Texture* PipeTexture, const sf::Vector2f PlayArea);
		~Pipe();

		void  renderPipes(sf::RenderTarget& target);
		void  movePipes(const sf::Vector2f value);
		void  setPositionsX(const float value);

		// Geters
		sf::Sprite&   getBottomSprite() { return m_BottomPipeSprite; }
		sf::Sprite&   getTopSprite() { return m_TopPipeSprite; }
		sf::Vector2f  getBothPositions() { return m_TopPipeSprite.getPosition(); }
		const float   getGapStartPosition() { return m_gapStartPosition; }

	private:
		// Variables
		sf::Sprite    m_TopPipeSprite;
		sf::Sprite    m_BottomPipeSprite;
		sf::Vector2f  m_PlayArea;
		float	      m_gapStartPosition;

	private:
		// Functions
		float  m_calculateGapStartPositionY();
};
#endif // !PIPE_H
