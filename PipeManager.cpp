#include "PipeManager.h"

PipeManager::PipeManager(const sf::Vector2f PlayArea, const sf::Vector2u WindowSize, const float gLevel)
	:m_PlayArea(PlayArea),
	 m_PipeTexture(new sf::Texture()),
	 m_WindowSize(WindowSize),
	 m_groundLevel(gLevel),
	 m_playerDead(true)
{
	// Load texture
	m_PipeTexture->loadFromFile(PATH_TO_PIPE_TEXTURE);

	// Initialize vector
	m_PipeVector.reserve(MAX_PIPES);
	m_initPipeVector();
}

PipeManager::~PipeManager()
{
	delete m_PipeTexture; // !!!!!
	m_PipeTexture = nullptr;
}


/*
* ====================================
* 
* Renders the pipes in m_PipeVector
* Called by:
*	-> Window::MainLoop
* 
* Return: void
* ====================================
*/
void PipeManager::renderPipes(sf::RenderTarget& target)
{
	for (auto& p : m_PipeVector)
		p.renderPipes(target);
}

/*
* ===============================================
* 
* Updates the pipes inside m_PipeVector
* Checks :
*	-> Player is dead or not, respawns
*	-> Whether the first pipe is out of bounds
*   -> For player collision
*	-> Spawns new pipes
*	-> Moves pipes
*	-> Handles points
* 
* Called by:
*	-> Window::MainLoop
* 
* Return: void
* 
* ===============================================
*/
void PipeManager::updatePipes(const sf::Sprite& player, bool& fucked)
{
	// Player is dead, respawn check
	if (m_playerDead && sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		m_playerDead = false;
		fucked = false;
	}

	// Player is alive
	else if (!m_playerDead) {
		for (auto& p : m_PipeVector) {
			p.movePipes({ -PIPE_SPEED, 0.0f });

			// Check for intersection
			if (p.getTopSprite().getGlobalBounds().intersects(player.getGlobalBounds()) ||
				p.getBottomSprite().getGlobalBounds().intersects(player.getGlobalBounds()) ||
				fucked ) {

				m_playerDead = true;
				m_PipeVector.clear();
				m_initPipeVector();
				m_points = 0; // Reset point
			}
		}

		// Check whether Pipe is out of bounds
		sf::Sprite s = m_PipeVector.front().getTopSprite(); // Cache 1 sprite

		// Check position
		if (s.getPosition().x < -s.getGlobalBounds().width) {

			// Setup, create new Pipe
			Pipe p = Pipe(m_PipeTexture, m_PlayArea);
			m_setupPipeForPush(p);
			p.setPositionsX(m_WindowSize.x + 2 * s.getGlobalBounds().width);

			// Remove first element, push new to the back
			m_PipeVector.erase(m_PipeVector.begin());
			m_PipeVector.push_back(p);

			// Add point
			++m_points;
		}
	}
}


/*
* ================================
* 
* Fills the pipe vector
* Makes calculations regarding:
*	-> Pipe positioning
* 
* Called by:
*	-> Constructor
* 
* Return: void
* 
* ================================
*/
void PipeManager::m_initPipeVector()
{
	for (uint8_t i = 0; i < MAX_PIPES; ++i) {
		Pipe e = Pipe(m_PipeTexture, m_PlayArea);

		m_setupPipeForPush(e);
		e.setPositionsX(m_WindowSize.x + 3 * e.getBottomSprite().getGlobalBounds().width * i);
		m_PipeVector.emplace_back(e);
	}
}


/*
* ================================
* 
* Sets up Pipe object for use
* Makes calculations regarding:
*	-> Pipe positions
*	-> Size
*	-> Gap placement
* 
* Return: void
* 
* ================================
*/
void PipeManager::m_setupPipeForPush(Pipe& pipe)
{
	// Store data
	float gapStart = pipe.getGapStartPosition();
	sf::Sprite& top = pipe.getTopSprite();
	sf::Sprite& bottom = pipe.getBottomSprite();

	// Setup bottom sprite
	bottom.setPosition(100.0f, gapStart + 2.0f * PIPE_GAP);
	int b_VisibleTexture = static_cast<int>((m_groundLevel - bottom.getPosition().y) / PIPE_SCALE_VALUE);
	bottom.setTextureRect(sf::IntRect(0, 0, bottom.getTexture()->getSize().x, b_VisibleTexture));

	// Setup top sprite
	int t_VisibleTexture = static_cast<int>(gapStart + m_PlayArea.x);
	top.setPosition(100.0f, gapStart);
	top.setTextureRect(sf::IntRect(0, 0, top.getTexture()->getSize().x, t_VisibleTexture));
}