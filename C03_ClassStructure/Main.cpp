#include "Main.h"

int main(void)
{
	AppClass* pApp = new AppClass();
	pApp->Run();
	if (pApp)
	{
		delete pApp;
		pApp = nullptr;
	}
	return 0;
}