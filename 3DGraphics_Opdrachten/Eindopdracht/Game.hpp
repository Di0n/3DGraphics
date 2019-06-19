#ifndef GAME_HPP
#define GAME_HPP
#include "Globals.hpp"
namespace Game
{
	// Needs to be publicly available for modules etc.
	extern bool keys[256];
	// Gets called when the engine is ready to load in content / initialize.
	void loadContent();
	// Gets called every frame for game logic.
	void update(float deltaTime);
	// Gets called on every draw.
	void draw();
	// Gets called when a key gets pressed.
	void onKey(Key key);
	// Gets called when a key is released.
	void onKeyUp(Key key);
	// Gets called when the mouse moves.
	void onMouseMove(int x, int y);
	// Gets called when the screen resizes.
	void onResize(int w, int h);
	// Gets called when app is closing.
	void onClose();
}
#endif