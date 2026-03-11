// include the basic windows header files and the Direct3D header file
#include "IvyyyEngine.h"
#include "IvyyySceneHandler.h"
#include <IvyyyScreen.h>
#include <IvyyyWindow.h>
#include "math.h"

using namespace Ivyyy;

// the entry point for any Windows program
int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	Ivyyy::Window::SetFullscreen(true);
	Ivyyy::Screen::SetResolution(Ivyyy::Resolution{ 1920, 1080 });
	Ivyyy::Renderer::SetMode(Renderer::Mode::DX11);

	return Ivyyy::IvyyyEngine::Start(hInstance, nCmdShow);
}