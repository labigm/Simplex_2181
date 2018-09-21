/*--------------------------------------------------------------------------------------------------
This project was generated in 2018
--------------------------------------------------------------------------------------------------*/
#ifndef __MAIN_H_
#define __MAIN_H_

#include "AppClass.h"
/*
USAGE: will safely delete the input pointer and initialize it to nullptr, DOES NOT WORK WITH POINTER ARRAY
*/
#define SafeDelete(p){ if(p) { delete p; p = nullptr; } }

#endif //__MAIN_H_

/*
USAGE:
ARGUMENTS: ---
OUTPUT: ---
*/