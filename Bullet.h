#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Bullet
{
private:
	// Where is the bullet?
	Vector2f m_Position;

	// What does each bullet look like?
	RectangleShape m_BulletShape;

	// Is this bullet currently flying?
	bool m_InFlight = false;

	// How fast does a bullet travel?
	float m_BulletSpeed = 1000;

	// What fraction of 1 pixel does the bullet travel horizontally and vertically each frame?
	// These valuse will be derived from m_BulletSpeed
	float m_BulletDistanceX;
	float m_BulletDistanceY;
	// Some boundaries so the bullet doesn't fly forever
	float m_MaxX;
	float m_MinX;
	float m_MaxY;
	float m_MinY;

	// Public function prototpes go here
public:
	// The constructor
	Bullet();

	// Stop the bullet
	void stop();

	// Returns the value of m_InFlight
	bool isInFlight();

	// Launch a new bullet
	void shoot(float startX, float startY, float xTarget, float yTarget);

	// Tell the calling code where the bullet is in the world
	FloatRect getPosition();

	// Return the actural shape (for drawing)
	RectangleShape getShape();

	// Update the bullet each frame
	void update(float elapsedTime);

};