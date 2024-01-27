#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <memory>

#define GRAVITY				  0.5f
#define DEFAULT_JUMP_SPEED  -12.0f
#define PATH_TO_SPRITE		"res/BirdImage.png"

class Player
{
	public:
		Player(const sf::Vector2u WindowSize);
		~Player();

		void			   renderPlayer(sf::RenderTarget& target);
		void			   updatePlayer(const bool SpacePressed, const bool dead);
		const sf::Sprite&  getPlayerSprite() { return m_BirdSprite; }
		const float		   getGroundLevel() { return m_groundLevel; }
		bool&		       getPlayerState() { return m_fucked; }
		sf::Vector2f       getPlayArea();
		
		
		constexpr sf::Sprite& getPlayer() { return m_BirdSprite; }

	private:
		// Variables
		std::unique_ptr<sf::Texture>  m_BirdTexture;
		sf::Sprite				      m_BirdSprite;
		const sf::Vector2u			  m_WindowSize;
		float						  m_birdSpeed;
		const float					  m_groundLevel;
		bool						  m_fucked;

	private:
		// Functions
		void		 m_initBirdSprite();
		void		 m_setDefaultBirdPosition();
		inline bool  m_isOutOfBounds();
};
#endif // !PLAYER_H