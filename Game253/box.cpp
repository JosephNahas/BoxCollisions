#include "box.h"




box::box(int _x, int _y, float _w, float _h)
{

	x = _x;
	y = _y;
	width = _w;
	height = _h;


}


int box::GetX() {
	return x;
}

int box::GetY() {
	return y;
}


float box::GetWidth() {
	return width;
}

float box::GetHeight() {
	return height;
}


void box::SetX(int _x) {
	x = _x;
}


void box::SetY(int _y) {
	y = _y;
}


void box::Draw(SDL_Renderer* rend) {
	_box = { x , y, (int)width, (int)height };

	if (collided)
		SDL_SetRenderDrawColor(rend, 255, 0, 0, 255);

	else
		SDL_SetRenderDrawColor(rend, 0, 255, 0, 255);
	SDL_RenderDrawRect(rend, &_box);
}