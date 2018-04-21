#include "scene.h"



scene::scene()
{
}


scene::~scene()
{

	SDL_DestroyRenderer(renderer);
	renderer = NULL;

	SDL_DestroyWindow(window);
	window = NULL;

}


void scene::init() {

	window = SDL_CreateWindow("Project", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}

void scene::render() {

	for (box* b : bigBoxes) {

		if (b != NULL) {
			for (box* smallb : b->smallBoxes) {
				if (smallb != NULL)
					smallb->Draw(renderer);
			}
		}

		b->Draw(renderer);

	}

}

void scene::update() {

	while (loop) {

		handleEvent();

	

		if (sceneChange) {


			for (collision* col : collisions)
				delete col;

			collisions.clear();

			for (box* b : bigBoxes) {

				for (box* smallb : b->smallBoxes) {
					smallb->collided = false;
				}

				b->collided = false;
			}

			CollisionDetection();

			system("cls");

			for (collision* col : collisions) {
				col->output();
			}
		}

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);
		render();
		SDL_RenderPresent(renderer);

		sceneChange = false;

	}

}

bool scene::TestCollision(box* _b1, box* _b2) {

	if (((_b1->GetX() + _b1->GetWidth() >= _b2->GetX() && _b1->GetX() <= _b2->GetX()) || (_b1->GetX() <= _b2->GetX() + _b2->GetWidth() && _b1->GetX() + _b1->GetWidth() >= _b2->GetX() + _b2->GetWidth())) && ((_b1->GetY() + _b1->GetHeight() >= _b2->GetY() && _b1->GetY() <= _b2->GetY()) || (_b1->GetY() <= _b2->GetY() + _b2->GetHeight() && _b1->GetY() + _b1->GetHeight() >= _b2->GetY() + _b2->GetHeight()))) {
		return true;
	}

	else
		return false;
}

void scene::CollisionDetection() {
	for (list<box*>::iterator iterator = bigBoxes.begin(), end = bigBoxes.end(); iterator != end; ++iterator) {

		box* _b = *iterator;

		list<box*>::iterator iterator2 = iterator;
		iterator2++;
		

		for (iterator2; iterator2 != end; ++iterator2) {
			box* _b2 = *iterator2;
			if (_b != _b2) {
				if (TestCollision(_b, _b2)) {

					_b->collided = true;
					_b2->collided = true;

					collision* newCollision = new collision(_b, _b2);
					collisions.push_front(newCollision);

					for (box* _smallb : _b->smallBoxes) {
						
						for (box* _smallb2 : _b2->smallBoxes) {

							if (TestCollision(_smallb, _smallb2)) {

								_smallb->collided = true;
								_smallb2->collided = true;

								collision* newCollision2 = new collision(_smallb, _smallb2);
								collisions.push_front(newCollision2);

							}

							
						}

					}
				}

				
			}
		}


	}
}

void scene::handleEvent() {

	SDL_Event event;

	while (SDL_PollEvent(&event) != 0) {

		
		if (event.type == SDL_QUIT) {
			loop = false;
		}

		else if (event.type == SDL_KEYDOWN) {

			sceneChange = true;
			
			switch (event.key.keysym.sym) {

			case SDLK_b:
			{
				box* newBox = new box(0, 0, 100, 100);
				bigBoxes.push_front(newBox);
				bigIt = bigBoxes.begin();
				currentBigBox = *bigIt;
				currentBox = currentBigBox;
			}
				break;

			case SDLK_s:
			{
				if (currentBigBox != NULL) {

					box* newSmallBox = new box(currentBigBox->GetX(), currentBigBox->GetY(), 10, 10);
					currentBigBox->smallBoxes.push_front(newSmallBox);
					currentBigBox->smallIt = currentBigBox->smallBoxes.begin();
					currentSmallBox = *currentBigBox->smallIt;
					currentBox = currentSmallBox;

				}
			}
				break; 

			case SDLK_a:
			{
				if (currentBigBox != NULL) {

					bigIt++;

					if (bigIt != bigBoxes.end())
					{
						currentBigBox = *bigIt;
						currentBox = currentBigBox;
						

						if (!currentBigBox->smallBoxes.empty()) {
							currentBigBox->smallIt = currentBigBox->smallBoxes.begin();
							currentSmallBox = *currentBigBox->smallIt;
						}
					}
				
					else {
						bigIt = bigBoxes.begin();
						currentBigBox = *bigIt;
						currentBox = currentBigBox;
						

						if (!currentBigBox->smallBoxes.empty()) {
							currentBigBox->smallIt = currentBigBox->smallBoxes.begin();
							currentSmallBox = *currentBigBox->smallIt;
						}

					}

					


				}
			}
				break;

			case SDLK_d:
			{
				if (currentSmallBox != NULL) {

					currentBigBox->smallIt++;

					if (currentBigBox->smallIt != currentBigBox->smallBoxes.end())
					{
						currentSmallBox = *currentBigBox->smallIt;
						currentBox = currentSmallBox;
					}

					else {
						currentBigBox->smallIt = currentBigBox->smallBoxes.begin();
						currentSmallBox = *currentBigBox->smallIt;
						currentBox = currentSmallBox;
					}

				}
			}
				break;

			case SDLK_UP:
			{
				if (currentBox != NULL) {

					currentBox->SetY(currentBox->GetY() - 2);

					if (currentBox->GetY() < 0)
						currentBox->SetY(0);

					if (currentBox == currentBigBox) {

						for (box* smallBox : currentBigBox->smallBoxes) {

							if (smallBox != NULL)
								smallBox->SetY(smallBox->GetY() - 2);

							if (smallBox->GetY() < 0)
								smallBox->SetY(0);
						}

					}

					if (currentBox == currentSmallBox) {

						if (currentSmallBox->GetY() < currentBigBox->GetY())
							currentSmallBox->SetY(currentBigBox->GetY());

					}


				}

			}
				break;

			case SDLK_DOWN:
			{
				if (currentBox != NULL) {

					currentBox->SetY(currentBox->GetY() + 2);

					if (currentBox->GetY() + currentBox->GetHeight() > SCREEN_HEIGHT)
						currentBox->SetY(SCREEN_HEIGHT - currentBox->GetHeight());

					if (currentBox == currentBigBox) {

						for (box* smallBox : currentBigBox->smallBoxes) {

							if (smallBox != NULL)
								smallBox->SetY(smallBox->GetY() + 2);

							if (smallBox->GetY() + smallBox->GetHeight() > SCREEN_HEIGHT)
								smallBox->SetY(SCREEN_HEIGHT - smallBox->GetHeight());
						}

					}

					if (currentBox == currentSmallBox) {

						if (currentSmallBox->GetY() + currentSmallBox->GetHeight() > currentBigBox->GetY() + currentBigBox->GetHeight())
							currentSmallBox->SetY(currentBigBox->GetY() + currentBigBox->GetHeight() - currentSmallBox->GetHeight());

					}

				}

			}
				break;

			case SDLK_LEFT:
			{
				if (currentBox != NULL) {

					currentBox->SetX(currentBox->GetX() - 2);

					if (currentBox->GetX() < 0)
						currentBox->SetX(0);

					if (currentBox == currentBigBox) {

						for (box* smallBox : currentBigBox->smallBoxes) {

							if (smallBox != NULL)
								smallBox->SetX(smallBox->GetX() - 2);

							if (smallBox->GetX() < 0)
								smallBox->SetX(0);
						}

					}

					if (currentBox == currentSmallBox) {

						if (currentSmallBox->GetX() < currentBigBox->GetX())
							currentSmallBox->SetX(currentBigBox->GetX());

					}

				}

			}
				break;

			case SDLK_RIGHT:
			{
				if (currentBox != NULL) {

					currentBox->SetX(currentBox->GetX() + 2);

					if (currentBox->GetX() + currentBox->GetWidth() > SCREEN_WIDTH)
						currentBox->SetX(SCREEN_WIDTH - currentBox->GetWidth());

					if (currentBox == currentBigBox) {

						for (box* smallBox : currentBigBox->smallBoxes) {

							if (smallBox != NULL)
								smallBox->SetX(smallBox->GetX() + 2);

							if (smallBox->GetX() + smallBox->GetWidth() > SCREEN_WIDTH)
								smallBox->SetX(SCREEN_WIDTH - smallBox->GetWidth());
						}

					}

					if (currentBox == currentSmallBox) {

						if (currentSmallBox->GetX() + currentSmallBox->GetWidth() > currentBigBox->GetX() + currentBigBox->GetWidth())
							currentSmallBox->SetX(currentBigBox->GetX() + currentBigBox->GetWidth() - currentSmallBox->GetWidth());

					}

				}

			}
				break;


			case SDLK_BACKSPACE:
			{
				if (currentBox != NULL) {

					if (currentBox == currentSmallBox) {

						currentBigBox->smallIt = currentBigBox->smallBoxes.erase(currentBigBox->smallIt);

						if (currentBigBox->smallIt != currentBigBox->smallBoxes.end()) {
							currentSmallBox = *currentBigBox->smallIt;
							currentBox = currentSmallBox;
						}
						else
						{

							if (!currentBigBox->smallBoxes.empty()) {

								currentBigBox->smallIt = currentBigBox->smallBoxes.begin();
								currentSmallBox = *currentBigBox->smallIt;
								currentBox = currentSmallBox;
							}

							else {
								currentBox = currentBigBox;
							
							}
						}

					}

					else if (currentBox == currentBigBox) {


						currentBigBox->smallBoxes.clear();

						bigIt = bigBoxes.erase(bigIt);


						if (bigIt != bigBoxes.end()) {

							currentBigBox = *bigIt;
							currentBox = currentBigBox;
						}

						else {

							if (!bigBoxes.empty()) {
								bigIt = bigBoxes.begin();
								currentBigBox = *bigIt;
								currentBox = currentBigBox;
							}
								

							else {
								currentBigBox = NULL;
								currentBox = NULL;
							}
						}
						
					}
				}

			}
		
				break;

			case SDLK_ESCAPE:
				loop = false;
				break;

			default:
				break;
			}
		}

	}
}
