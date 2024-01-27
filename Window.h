#ifndef WINDOW_H
#define WINDOW_H

#include <SFML/Graphics.hpp>

#include "Player.h"
#include "Background.h"
#include "PipeManager.h"
#include "Points.h"

#define FPS		    60
#define WN_WIDTH   300
#define WN_HEIGHT  400

class Window
{
	public:
		Window();
		~Window();
		
		void MainLoop(void);

	private:
		// private variables, objects
		sf::RenderWindow  m_Window;
		sf::Event		  m_Event;
		bool			  m_running;
		bool			  m_spacePressed;

		Player			  m_Player;
		Background		  m_Background;
		PipeManager	      m_PipeManager;
		xd::Points		  m_Points;

	private:
		// Private functions
		inline void m_update();
		inline void m_render();
};
#endif // !WINDOW_H