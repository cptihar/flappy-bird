#ifndef PIPE_MANAGER_H
#define PIPE_MANAGER_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "Pipe.h"

#define PATH_TO_PIPE_TEXTURE  "res/PipeTexture.png"
#define MAX_PIPES	      3
#define PIPE_SPEED	      1.0f

class PipeManager
{
	public:
		PipeManager(const sf::Vector2f PlayArea, const sf::Vector2u WindowSize, const float gLevel);
		~PipeManager();

		void renderPipes(sf::RenderTarget& target);
		void updatePipes(const sf::Sprite& player, bool& fucked);

		// Getter, setter
		const bool  playerDead() { return m_playerDead; }
		void	    setPlayerDead(const bool value) { m_playerDead = value; }
		
		// Point getter
		const uint32_t getPoints() { return m_points; }

	private:
		// Variables
		std::vector<Pipe>    m_PipeVector;
		const sf::Vector2f   m_PlayArea;
		sf::Texture*	     m_PipeTexture; // Destuctor should delete it
		const sf::Vector2u   m_WindowSize;
		const float	     m_groundLevel;
		bool		     m_playerDead;
		uint32_t	     m_points;

	private:
		// Functions
		void m_initPipeVector();
		void m_setupPipeForPush(Pipe& pipe);
};
#endif // !PIPE_MANAGER_H
