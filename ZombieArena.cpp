// ZombieArena.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "ZombieArena.h"

using namespace sf;

int main()
{
	// The game will always be in one of four states
	enum class State
	{
		PAUSED, LEVELING_UP, GAME_OVER, PLAYING
	};
	//Start with the GAME_OVER state
	State state = State::GAME_OVER;

	//get the screen resolution and create an SFML window
	Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	RenderWindow window(VideoMode(resolution.x, resolution.y), "Zombie Arena", Style::Fullscreen);

	//create an SFML view for the main action
	View mainView(sf::FloatRect(0, 0, resolution.x, resolution.y));
	// here is our clock for timing everything
	Clock clock;

	// How long has the PLAYING state been active
	Time gameTimeTotal;
	// Where is the mouse in relation to world coordinates?
	Vector2f mouseWorldPosition;

	// Where is the mouse in relation to screen coordinates
	Vector2i mouseScreenPosition;

	// Create an instance of the Player class
	Player player;

	// the boundaries of the arena
	IntRect arena;

	//create the background
	VertexArray background;
	//load the texture for our background vertex array
	Texture textureBackground;
	textureBackground.loadFromFile("graphics/background_sheet.png");

	//The main game loop
	while (window.isOpen())
	{
		/*
		************
		Handle Input
		************
		*/

		//Handle events by polling
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::KeyPressed)
			{
				// Pause a game while playing
				if (event.key.code == Keyboard::Return && state == State::PLAYING)
				{
					state = State::PAUSED;
				}
				//Restart while paused
				else if (event.key.code == Keyboard::Return && state == State::PAUSED)
				{
					state = State::PLAYING;
					// reset the clock so there isn't a frame jump
					clock.restart();
				}
				//start a new game while in GAME_OVER state
				else if (event.key.code == Keyboard::Return && state == State::GAME_OVER)
				{
					state = State::LEVELING_UP;
				}
				if (state == State::PLAYING)
				{

				}
			}
		}// End Event polling

		//Handle the player quitting
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		//Handle WASD movement while player
		if (state == State::PLAYING)
		{
			//Handle the pressing and releaseing of the WASD keys
			if (Keyboard::isKeyPressed(Keyboard::W))
			{
				player.moveUp();
			}
			else
			{
				player.stopUp();
			}
			if (Keyboard::isKeyPressed(Keyboard::S))
			{
				player.moveDown();
			}
			else
			{
				player.stopDown();
			}
			if (Keyboard::isKeyPressed(Keyboard::D))
			{
				player.moveRight();
			}
			else
			{
				player.stopRight();
			}
			if (Keyboard::isKeyPressed(Keyboard::A))
			{
				player.moveLeft();
			}
			else
			{
				player.stopLeft();
			}
		}// End WASD movement

		// Handle the leveling up state
		if (state == State::LEVELING_UP)
		{
			//handle leveling up
			if (event.key.code == Keyboard::Num1)
			{
				state = State::PLAYING;
			}

			if (event.key.code == Keyboard::Num2)
			{
				state = State::PLAYING;
			}
			if (event.key.code == Keyboard::Num3)
			{
				state = State::PLAYING;
			}
			if (event.key.code == Keyboard::Num4)
			{
				state = State::PLAYING;
			}
			if (event.key.code == Keyboard::Num5)
			{
				state = State::PLAYING;
			}
			if (event.key.code == Keyboard::Num6)
			{
				state = State::PLAYING;
			}
			if (state == State::PLAYING)
			{
				//prepare the level
				// we will modify the next two lines later
				arena.width = 500;
				arena.height = 500;
				arena.left = 0;
				arena.top = 0;

				//Pass the vertex array reference to the createBackground function
				int tileSize = createBackground(background, arena);

				//spawn the player in the middle of the arena
				player.spawn(arena, resolution, tileSize);

				//reset the clock so there isn't a frame jump
				clock.restart();
			}

		}// End leveling up

		/*
		****************
		UPDATE THE FRAME
		****************
		*/
		if (state == State::PLAYING)
		{
			//Update the delta time
			Time dt = clock.restart();

			//Update the total game time
			gameTimeTotal += dt;

			//Make a decimal fraction of 1 from the delta time
			float dtAsSeconds = dt.asSeconds();

			//Where is the mouse pointer?
			mouseScreenPosition = Mouse::getPosition();

			//convert mouse position to world coordinates of mainView
			mouseWorldPosition = window.mapPixelToCoords(Mouse::getPosition(), mainView);

			//update the player
			player.update(dtAsSeconds, Mouse::getPosition());

			//make a note of the player's new position
			Vector2f playerPosition(player.getCenter());

			//make the view centre around the player
			mainView.setCenter(player.getCenter());
		}// End updating the scene

		/*
		**************
		Draw the Scene
		**************
		*/

		if (state == State::PLAYING)
		{
			window.clear();

			//set the mainView to be displayed in the window
			// draw everying related to mainView
			window.setView(mainView);

			//draw the background
			window.draw(background, &textureBackground);

			//draw the player
			window.draw(player.getSprite());
		}
		if (state == State::LEVELING_UP)
		{

		}
		if (state == State::PAUSED)
		{

		}
		if (state == State::GAME_OVER);
		{

		}
		window.display();

	}// End game loop

	//comments
	
	return 0;
}

