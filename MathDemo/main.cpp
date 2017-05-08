#include "MathDemoApp.h"
#include "settings.h"
#include <Windows.h>
#include <time.h>


/////////////////////////////////////////////////////////////////
////	Created by:		Jack McCall
////	Description:	Demonstrates the use of the maths library
////					to calculate collision and matrix heirachies


int main() {
	srand((unsigned int)time(NULL));

	auto app = new MathDemoApp();
	app->run(APPTITLE, SCREENWIDTH, SCREENHEIGHT, FULLSCREEN);
	delete app;

	return 0;
}