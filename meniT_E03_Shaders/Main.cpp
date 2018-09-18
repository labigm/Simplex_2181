#include "Main.h"

int main(void)
{
	AppClass* pApp = new AppClass("Shaders");
	pApp->Run();
	SafeDelete(pApp);
	return 0;
}