#include "MathDemoApp.h"
#include "settings.h"
#include <Windows.h>
#include <time.h>
#include <GLFW\glfw3.h>


/////////////////////////////////////////////////////////////////
////	Created by:		Jack McCall
////	Description:	Demonstrates the use of the maths library
////					to calculate collision and matrix heirachies


int main() {
	srand((unsigned int)time(NULL));

	// Initialise glfw to let us tweak some parameters
	glfwInit();
	// Disable window resize
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	auto app = new MathDemoApp();
	app->run(APPTITLE, SCREENWIDTH, SCREENHEIGHT, FULLSCREEN);
	delete app;

	return 0;
}