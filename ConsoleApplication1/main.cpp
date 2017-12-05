
#include "Window.h"

int main(int argc, char* argv) {
	char* title = "NeroEngine window";
	std::shared_ptr<NeroEngine::Window> mainWindow = std::make_shared<NeroEngine::Window>(title,640,480,std::make_shared<NeroEngine::ColorRGB>(0,0,255));

	mainWindow->run();

	return 0;
}
