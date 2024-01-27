#include "Pipe.h"

Pipe::Pipe(sf::Texture* PipeTexture, const sf::Vector2f PlayArea)
	:m_PlayArea(PlayArea), m_gapStartPosition(0.0f)
{
	// Load textures
	m_TopPipeSprite.setTexture(*PipeTexture);
	m_BottomPipeSprite.setTexture(*PipeTexture);
	
	// Flip top sprite
	m_BottomPipeSprite.setScale(PIPE_SCALE_VALUE, PIPE_SCALE_VALUE);
	m_TopPipeSprite.setScale(PIPE_SCALE_VALUE, -PIPE_SCALE_VALUE);
	
	m_gapStartPosition = m_calculateGapStartPositionY();
}

Pipe::~Pipe()
{}


/*
* ==========================================
* 
* Renders the pipe
* Parameter:
*	-> sf::RenderTarget& (target surface)
* 
* Return: void
* 
* ==========================================
*/
void Pipe::renderPipes(sf::RenderTarget& target)
{
	target.draw(m_BottomPipeSprite);
	target.draw(m_TopPipeSprite);
}


/*
* ========================================
* 
* Moves Bottom and top sprite
* Parameter:
*	-> const sf::Vector2f value (speed)
* 
* Return: void
* 
* ========================================
*/
void Pipe::movePipes(const sf::Vector2f value)
{
	m_BottomPipeSprite.move(value);
	m_TopPipeSprite.move(value);
}


/*
* ==================================
*
* Sets the pipes' X positions
* Parameter:
*	-> const float (new position)
*
* Return: void
*
* ==================================
*/
void Pipe::setPositionsX(const float value)
{
	m_BottomPipeSprite.setPosition(value, m_BottomPipeSprite.getPosition().y);
	m_TopPipeSprite.setPosition(value, m_TopPipeSprite.getPosition().y);
}


/*
* ===================================================
* 
* Calculates a random position in the play area
* This point will be the starting point of the gap
* Only the TOP Y coordinate is calculated
* 
* Return: float
* 
* ===================================================
*/
float Pipe::m_calculateGapStartPositionY()
{
	float available_space = m_PlayArea.y - PIPE_GAP;
	return static_cast<float>(rand() % static_cast<int>(available_space - m_PlayArea.x)) + m_PlayArea.x;
}
