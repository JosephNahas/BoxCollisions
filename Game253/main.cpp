#include "scene.h"

int main(int argc, char ** argv)
{
	SDL_Init(SDL_INIT_VIDEO);

	scene* newScene = new scene();

	newScene->init();
	newScene->update();

	delete newScene;

	SDL_Quit();

	return 0;
}