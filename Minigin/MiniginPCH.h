#pragma once

#include "Core/targetver.h"

#include <stdio.h>
#include <iostream> // std::cout
#include <sstream> // stringstream
#include <tchar.h>
#include <memory> // smart pointers
#include <vector>


#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "Core/Log.h" // Various logging functions


template<class T>
inline void SafeDelete(T &pObjectToDelete)
{
	if (pObjectToDelete)
	{
		delete(pObjectToDelete);
		pObjectToDelete = nullptr;
	}
}

#include "ObjComp/BaseObject.h"
#include "ObjComp/BaseComponent.h"
#include "ObjComp/Transform.h"
