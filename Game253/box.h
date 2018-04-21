#pragma once

#include <SDL.h>
#include <list>

using namespace std;

class box
{

private:
	int x;
	int y;
	float width;
	float height;

	SDL_Rect _box;
	



public:


	box(int _x, int _y, float _w, float _h);
	bool collided;

	int GetX();
	int GetY();
	float GetWidth();
	float GetHeight();
	void SetX(int _x);
	void SetY(int _y);
	void Draw(SDL_Renderer* rend);

	list<box*> smallBoxes;
	list<box*>::iterator smallIt;

};

