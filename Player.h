#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Player
{
private:
	const float START_SPEED = 200;
	const float START_HEALTH = 100;
	//where is the player
	Vector2f m_Position;

	Sprite m_Sprite;

	// !! WATCH THIS SPACE!!//
	Texture m_Texture;

	//Screen Resolution
	Vector2f m_Resolution;

	//what size is the current arena?
	IntRect m_Arena;

	//how big is each tile of the arena?
	int m_TileSize;

	//Which direction is the player moving in
	bool m_UpPressed;
	bool m_DownPressed;
	bool m_LeftPressed;
	bool m_RightPressed;

	int m_Health;

	int m_MaxHealth;

	//when was the player hit last
	Time m_LastHit;

	// Speed in pixels per second
	float m_Speed;

	//public functions come next
public:
	Player();
	void spawn(IntRect arena, Vector2f resolution, int tileSize);

	//Call this at the end of every game
	void resetPlayerStats();

	//Handle the player getting hit by a zombie
	bool hit(Time timeHit);

	//How long ago was the player last hit
	Time getLastHitTime();

	//Where is the player
	FloatRect getPosition();

	//Where is the center of the player
	Vector2f getCenter();

	//Which angle is the player facing?
	float getRotation();

	// Send a copy of the sprite to main
	Sprite getSprite();

	//functions to move the player
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();

	//stop the player moving in a specifiv direction
	void stopLeft();
	void stopRight();
	void stopUp();
	void stopDown();

	//we will call this function once every frame
	void update(float elapsedTime, Vector2i mousePosition);

	//Give player a speed boost
	void upgradeSpeed();

	//Give the player some health
	void upgradeHealth();

	//increase the maximum amound of health the player can have
	void increaseHealthLevel(int amount);

	//How much health does the player have
	int getHealth();
	
		
};