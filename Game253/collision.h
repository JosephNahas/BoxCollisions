#pragma once

#include "box.h"
#include <iostream>

class collision
{

private:
	box* box1;
	box* box2;



public:
	collision(box* b1, box* b2);
	void output();
};

