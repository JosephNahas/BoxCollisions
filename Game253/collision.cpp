#include "collision.h"
#include <stdlib.h>


collision::collision(box* b1, box* b2)
{

	box1 = b1;
	box2 = b2;

}


void collision::output() {


	
	cout << "collision between box: " << box1->GetX() << " " << box1->GetY() << " and box: " << box2->GetX() << " " << box2->GetY() << endl;


}


