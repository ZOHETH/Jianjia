#include "Application.h"

bool g_ApplicationRunning = true;

int main(int argc, char** argv)
{
	while (g_ApplicationRunning)
	{
		jjf::Application* app = jjf::CreateApplication(argc, argv);
		app->Run();
		delete app;
	}

	return 0;
}