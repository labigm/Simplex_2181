/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2017/05
----------------------------------------------*/
#ifndef __CONTROLLERCONFIG_H_
#define __CONTROLLERCONFIG_H_

#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"
#include "SFML\OpenGL.hpp"

enum ControllerKey_
{
	SimplexKey_A,		//0
	SimplexKey_B,		//1
	SimplexKey_X,		//2
	SimplexKey_Y,		//3
	SimplexKey_L1,		//4
	SimplexKey_R1,		//5
	SimplexKey_L2,		//6
	SimplexKey_R2,		//7
	SimplexKey_L3,		//8
	SimplexKey_R3,		//9
	SimplexKey_Select,	//10
	SimplexKey_Start,	//11
	SimplexKey_Pad,		//12
	SimplexKey_G0,		//13
	SimplexKey_G1,		//14
};
enum ControllerAxis_
{
	SimplexAxis_X,		//0
	SimplexAxis_Y,		//1
	SimplexAxis_U,		//2
	SimplexAxis_V,		//3
	SimplexAxis_L,		//4
	SimplexAxis_R,		//5
	SimplexAxis_POVX,	//6
	SimplexAxis_POVY,	//7
};
enum ControllerModel_
{
	/*
	Notes:
	-Controllers not natively supported by Windows:
	DualShock3 and older, Wiimote, WiiU Pro
	-For Controllers not natively supported by Windows:
	If you connect the controller, Windows might
	install drivers for it and display your controller
	in the "Devices and Printers" window. This does not
	mean that Windows knows how to use it though. Check
	the controller properties, if it does not register
	there, it will not register here unless other
	libraries are used. 
	-There are packages like ScToolKit that will make
	not natively supported controllers work under
	Windows, but they will register as if a 360
	controller was plugged in.
	-This is a list of proven controllers, special
	configurations might be needed and some are 
	provided in the .cpp
	*/
	SimplexController_NONE,
	SimplexController_XBONE,
	SimplexController_360,
	SimplexController_DualShock4,
	SimplexController_SwitchPro,
	SimplexController_NES30PRO,
	SimplexController_USBNES,
	SimplexController_OTHER,
};

enum Vendor_
{
	SONY = 1356,
	MICROSOFT = 1118,
	NINTENDO = 1406,
	V8BITDO = 11720,
	VGENERIC = 121,
};
struct ControllerInput
{
	unsigned int uModel = 1000;

	bool button[15];
	int mapButton[15];
	int mapAxis[8];
	float axis[8];
	
	ControllerInput(unsigned int nVendorID = 0, unsigned int nProductID = 0);

private:
	ControllerInput(ControllerInput const& other);
	ControllerInput& operator=(ControllerInput const& input);

};

#endif // __CONTROLLERCONFIG_H_

/*
USAGE:
ARGUMENTS: ---
OUTPUT: ---
*/