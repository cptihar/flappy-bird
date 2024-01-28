#include "Player.h"

Player::Player(const sf::Vector2u WindowSize)
	:m_BirdTexture(std::make_unique<sf::Texture>()),
	 m_WindowSize(WindowSize),
	 m_birdSpeed(GRAVITY),
	 m_groundLevel(m_WindowSize.y - 87.0f),
	 m_fucked(false)
{
	m_initBirdSprite();
	m_setDefaultBirdPosition();
}

Player::~Player()
{
}


/*
* =================================================
* 
* Draws the player sprite to the window
* Called by: 
*    -> Window::Render
*	 -> Call happens every frame
* 
* Parameter:
*	-> sf::RenderTarget: Reference to the window
* 
* Return: void
* 
* =================================================
*/
void Player::renderPlayer(sf::RenderTarget& target)
{
	target.draw(m_BirdSprite);
}


/*
* =================================
* Updates the player's
*	-> Movement
*	-> Out of bounds
*	-> State (dead or alive)
*	
* Called by:
*	-> Window::Update
*	-> Call happens every frame
* 
* Return: void
*	
* =================================
*/
void Player::updatePlayer(const bool SpacePressed, const bool dead)
{
	// Check for out of bounds
	if (m_isOutOfBounds() || dead) { 
		m_birdSpeed = 0.0f;
		m_fucked = true;
		m_setDefaultBirdPosition();
	}

	else if (!dead && !m_fucked) {

		if (SpacePressed) m_birdSpeed += DEFAULT_JUMP_SPEED;

		m_birdSpeed += GRAVITY;
		m_BirdSprite.move(0.0f, m_birdSpeed);
	}
}

/*
* ==========================================================
* 
* Returns the area where the pipes can be spawned
* Has buffer added to it to prevent unfair pipe placement
* 
* Return:
*	sf::Vector2f
*		-> X coord: upper
*		-> Y coord: lower
* 
* ==========================================================
*/
sf::Vector2f Player::getPlayArea()
{
	return sf::Vector2f(2 * m_BirdSprite.getGlobalBounds().height, 
		            m_groundLevel - 3 * m_BirdSprite.getGlobalBounds().height);
}


/*
* ==========================
* 
* Loads bird texture
* Initializes the sprite
* Called only by:
*	-> Constructor
* 
* Return: void
* 
* ==========================
*/
void Player::m_initBirdSprite()
{
	m_BirdTexture->loadFromFile(PATH_TO_SPRITE);
	m_BirdSprite.setTexture(*m_BirdTexture);
	m_BirdSprite.setScale(2.0f, 2.0f);
}


/*
* ======================================
* 
* Sets the player's default position
* 
* Return: void
* 
* ======================================
*/
void Player::m_setDefaultBirdPosition()
{
	m_BirdSprite.setPosition(m_BirdSprite.getGlobalBounds().width / 2,
				 m_WindowSize.y / 2 - 2 * m_BirdSprite.getGlobalBounds().height);
}


/*
* ============================================
* 
* Checks whether the Player's Y coordinates
* 
* Return: bool
*	-> true: Player is out of bounds
*	-> false: Player is ok
* 
* ============================================
*/
inline bool Player::m_isOutOfBounds()
{
	return (m_BirdSprite.getPosition().y < 0 ||
		m_BirdSprite.getPosition().y > m_groundLevel - m_BirdSprite.getGlobalBounds().height);
}
