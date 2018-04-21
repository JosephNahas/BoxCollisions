#pragma once


#include <list>
#include "box.h"
#include "collision.h"


#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

using namespace std;

class scene
{

private:
	bool loop = true;
	bool sceneChange = false;
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	list<box*> bigBoxes;
	list<collision*> collisions;
	box* currentBigBox;
	box* currentSmallBox;
	box* currentBox;
	
	
	list<box*>::iterator bigIt;

	void handleEvent();
	void render();
	void CollisionDetection();
	bool TestCollision(box* _b1, box* _b2);


public:
	scene();
	~scene();
	void init();
	void update();
	
};

