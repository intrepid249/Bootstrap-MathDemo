#include "MathDemoApp.h"
#include "settings.h"

int main() {
	auto app = new MathDemoApp();
	app->run(APPTITLE, SCREENWIDTH, SCREENHEIGHT, FULLSCREEN);
	delete app;

	return 0;
}