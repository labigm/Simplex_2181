#include "ControllerConfiguration.h"
ControllerInput::ControllerInput(ControllerInput const& other) {};
ControllerInput& ControllerInput::operator=(ControllerInput const& input) { return *this; };
ControllerInput::ControllerInput(unsigned int nVendorID, unsigned int nProductID)
{
	uModel = SimplexController_NONE;
	
	for (unsigned int i = 0; i < 15; ++i)
	{
		button[i] = false;
		mapButton[i] = i;
	}
	for (unsigned int i = 0; i < 8; ++i)
	{
		axis[i] = 0.0f;
		mapAxis[i] = i;
	}
	/*
	The following is used for mapping different controllers, Key A gets mapped
	to whatever the joystick reports as key 0 and so forth. This is specially
	useful whenever you want to be thinking about keys and not numerical
	identifiers in code like: button[SimplexKey_A];
	*/

	switch (nVendorID)
	{
	case MICROSOFT: //Microsoft
			   //XBOX ONE PRO || XBOX ONE || 360
		if (nProductID == 739 || nProductID == 746 || nProductID == 654)
		{
			//this is read: What does report as R? V does (or V reports as R)
			mapAxis[SimplexAxis_V] = sf::Joystick::Axis::R;

			mapAxis[SimplexAxis_L] = sf::Joystick::Axis::Z;
			mapAxis[SimplexAxis_R] = sf::Joystick::Axis::Z;

			/*
			mapButton[SimplexKey_A] = SimplexKey_A;
			mapButton[SimplexKey_B] = SimplexKey_B;
			mapButton[SimplexKey_X] = SimplexKey_X;
			mapButton[SimplexKey_Y] = SimplexKey_Y;

			mapButton[SimplexKey_L1] = SimplexKey_L1;
			mapButton[SimplexKey_R1] = SimplexKey_R1;
			mapButton[SimplexKey_Select] = SimplexKey_L2;
			mapButton[SimplexKey_Start] = SimplexKey_R2;
			mapButton[SimplexKey_L3] = SimplexKey_L3;
			mapButton[SimplexKey_R3] = SimplexKey_R3;
			*/
			mapButton[SimplexKey_L2] = SimplexKey_Select;
			mapButton[SimplexKey_R2] = SimplexKey_Start;

			//Does nothing on this pad
			mapButton[SimplexKey_Pad] = SimplexKey_Pad;//<----
			mapButton[SimplexKey_G0] = SimplexKey_G1;//<----
			mapButton[SimplexKey_G1] = SimplexKey_G1;//<----
		}

		if (nProductID == 739 || nProductID == 746)
		{
			uModel = SimplexController_XBONE;
		}
		else if (nProductID == 654)
		{
			uModel = SimplexController_360;
		}

		break;		

	case SONY: //Sony
		//PS4
		if (nProductID == 2976)
		{
			uModel = SimplexController_DualShock4;

			mapAxis[SimplexAxis_U] = sf::Joystick::Axis::Z;
			mapAxis[SimplexAxis_V] = sf::Joystick::Axis::R;

			mapAxis[SimplexAxis_L] = sf::Joystick::Axis::V;
			mapAxis[SimplexAxis_R] = sf::Joystick::Axis::U;

			mapButton[SimplexKey_B] = SimplexKey_A;
			mapButton[SimplexKey_X] = SimplexKey_B;
			mapButton[SimplexKey_A] = SimplexKey_X;
			mapButton[SimplexKey_Y] = SimplexKey_Y;

			mapButton[SimplexKey_L1] = SimplexKey_L1;
			mapButton[SimplexKey_R1] = SimplexKey_R1;
			mapButton[SimplexKey_L2] = SimplexKey_L2;
			mapButton[SimplexKey_R2] = SimplexKey_R2;
			mapButton[SimplexKey_Select] = SimplexKey_L3;
			mapButton[SimplexKey_Start] = SimplexKey_R3;
			
			mapButton[SimplexKey_L3] = SimplexKey_Select;
			mapButton[SimplexKey_R3] = SimplexKey_Start;
			
			mapButton[SimplexKey_G0] = SimplexKey_Pad;
			mapButton[SimplexKey_Pad] = SimplexKey_G0;

			//Does nothing on this pad
			mapButton[SimplexKey_G1] = SimplexKey_G1;//<----
		}
		break;
	case NINTENDO: //Nintendo
		//Switch Pro Controller
		if (nProductID == 8201)
		{
			uModel = SimplexController_SwitchPro;

			mapAxis[SimplexAxis_L] = SimplexAxis_U;

			mapButton[SimplexKey_A] = SimplexKey_A;
			mapButton[SimplexKey_B] = SimplexKey_B;
			mapButton[SimplexKey_X] = SimplexKey_X;
			mapButton[SimplexKey_Y] = SimplexKey_Y;

			mapButton[SimplexKey_L1] = SimplexKey_L1;
			mapButton[SimplexKey_R1] = SimplexKey_R1;
			mapButton[SimplexKey_L2] = SimplexKey_L2;
			mapButton[SimplexKey_R2] = SimplexKey_R2;
			mapButton[SimplexKey_Select] = SimplexKey_L3;
			mapButton[SimplexKey_Start] = SimplexKey_R3;

			mapButton[SimplexKey_L3] = SimplexKey_Select;
			mapButton[SimplexKey_R3] = SimplexKey_Start;
			
			mapButton[SimplexKey_Pad] = SimplexKey_Pad;
			mapButton[SimplexKey_G0] = SimplexKey_G0;

			//Does nothing on this pad
			mapButton[SimplexKey_G1] = SimplexKey_G1;//<----
		}
		break;
	case V8BITDO: //8 Bitdo
		//NES30 PRO
		if (nProductID == 36865)
		{
			uModel = SimplexController_NES30PRO;

			mapButton[SimplexKey_B] = SimplexKey_A;
			mapButton[SimplexKey_A] = SimplexKey_B;
			mapButton[SimplexKey_L1] = SimplexKey_X;
			mapButton[SimplexKey_Y] = SimplexKey_Y;

			mapButton[SimplexKey_L2] = SimplexKey_L1;
			mapButton[SimplexKey_R2] = SimplexKey_R1;

			mapButton[SimplexKey_L3] = SimplexKey_L2;
			mapButton[SimplexKey_R3] = SimplexKey_R2;

			mapButton[SimplexKey_G0] = SimplexKey_L3;
			mapButton[SimplexKey_G1] = SimplexKey_R3;

			mapButton[SimplexKey_Select] = SimplexKey_Select;
			mapButton[SimplexKey_Start] = SimplexKey_Start;
			
			//Does nothing on this pad
			mapButton[SimplexKey_X] = SimplexKey_Pad;//<----
			mapButton[SimplexKey_R1] = SimplexKey_Pad;//<-----
			mapButton[SimplexKey_Pad] = SimplexKey_Pad;//<-----
		}
		break;
	case VGENERIC: //USB Generic
		//USB NES
		if (nProductID == 17)
		{
			uModel = SimplexController_USBNES;

			mapAxis[SimplexAxis_X] = SimplexAxis_POVX;
			mapAxis[SimplexAxis_Y] = SimplexAxis_POVY;
			//-----------------------------------------
			mapButton[SimplexKey_X] = SimplexKey_A;
			mapButton[SimplexKey_B] = SimplexKey_B;

			mapButton[SimplexKey_L3] = SimplexKey_Select;
			mapButton[SimplexKey_R3] = SimplexKey_Start;

			//Does nothing on this pad
			mapButton[SimplexKey_A] = SimplexKey_Pad;//<----
			mapButton[SimplexKey_Y] = SimplexKey_Pad;//<----

			mapButton[SimplexKey_L1] = SimplexKey_Pad;//<----
			mapButton[SimplexKey_R1] = SimplexKey_Pad;//<----

			mapButton[SimplexKey_L2] = SimplexKey_Pad;//<----
			mapButton[SimplexKey_R2] = SimplexKey_Pad;//<----

			mapButton[SimplexKey_Select] = SimplexKey_Pad;//<----
			mapButton[SimplexKey_Start] = SimplexKey_Pad;//<----
						
			mapButton[SimplexKey_Pad] = SimplexKey_Pad;//<----
			mapButton[SimplexKey_G0] = SimplexKey_Pad;//<-----
			mapButton[SimplexKey_G1] = SimplexKey_Pad;//<-----			
		}
		break;
	default:
		break;
	}

}