#include "Window.h"

Window::Window()
	:m_Event(sf::Event()),
	 m_running(true),
	 m_spacePressed(false),
	 m_Player(sf::Vector2u(WN_WIDTH, WN_HEIGHT)),
	 m_Background(sf::Vector2u(WN_HEIGHT, WN_HEIGHT)),
	 m_PipeManager(PipeManager(m_Player.getPlayArea(), sf::Vector2u(WN_WIDTH, WN_HEIGHT), m_Player.getGroundLevel())),
	 m_Points(WN_HEIGHT)
{

	// Initialize window
	m_Window.create(sf::VideoMode(WN_WIDTH, WN_HEIGHT),
					"BirdGame",
					sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);

	m_Window.setFramerateLimit(FPS);
}

Window::~Window()
{}

void Window::MainLoop(void)
{
	while (m_running) {
		m_update();
		m_render();
	}
}

/*
* ======================================
* 
* Updates the window and game objects
* Call happense every frame
* 
* Return: void
* 
* ======================================
*/
inline void Window::m_update()
{
	m_spacePressed = false;
	// Event handling
	while (m_Window.pollEvent(m_Event)) {

		switch (m_Event.type) {

			case sf::Event::Closed:
				m_running = false;
				break;
			
			case sf::Event::KeyPressed:
				if (m_Event.key.code == sf::Keyboard::Space)
					m_spacePressed = true;
				break;

			default:
				break;
		}
	}

	// Background
	m_Background.updateBackgrounds();

	// Player
	m_Player.updatePlayer(m_spacePressed, m_PipeManager.playerDead());

	// Pipe manager
	m_PipeManager.updatePipes(m_Player.getPlayer(), m_Player.getPlayerState());

	// Points
	m_Points.updatePointText(m_PipeManager.getPoints());
}


/*
* ===============================
* 
* Renders the game objects
* Call happense every frame
*
* Return: void
* 
* ===============================
*/
inline void Window::m_render()
{
	// Clear the screen
	m_Window.clear();

	m_Background.renderBackgrounds(m_Window);
	m_Player.renderPlayer(m_Window);

	if (!m_PipeManager.playerDead() && !m_Player.getPlayerState())
		m_PipeManager.renderPipes(m_Window);

	m_Points.renderPoints(m_Window);
	// Display
	m_Window.display();
}
