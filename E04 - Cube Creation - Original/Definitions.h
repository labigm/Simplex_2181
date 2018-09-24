/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2017/06
----------------------------------------------*/
#ifndef __DEFINITIONS_H_
#define __DEFINITIONS_H_

//#include <vld.h>

//#define USEBASICX
#ifdef USEBASICX
#include "BasicX\BasicX.h"
using namespace BasicX;
#else
#include "Simplex\Simplex.h"
using namespace Simplex;
#endif // USEBASICX

#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"
#include "SFML\OpenGL.hpp"

#endif //__DEFINITIONS_H_

/*
USAGE:
ARGUMENTS: ---
OUTPUT: ---
*/