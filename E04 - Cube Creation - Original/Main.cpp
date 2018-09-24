// Include standard headers
#include "Main.h"

int main(void)
{
	Application* pApp = new Application();
	pApp->Init("Mesh Class", RES_C_1280x720_16x9_HD, false, false);
	pApp->Run();
	SafeDelete(pApp);
	return 0;
}