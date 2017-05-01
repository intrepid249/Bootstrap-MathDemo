#include "MathDemoApp.h"
#include "settings.h"
#include <Windows.h>
#include <time.h>

int main() {
	srand((unsigned int)time(NULL));

	auto app = new MathDemoApp();
	app->run(APPTITLE, SCREENWIDTH, SCREENHEIGHT, FULLSCREEN);
	delete app;

	return 0;
}