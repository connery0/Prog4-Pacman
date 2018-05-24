#include "MiniginPCH.h"
#pragma comment(lib,"xinput.lib")
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

// ReSharper disable once CppUnusedIncludeDirective
#include <vld.h>
#include "SDL.h"
#include "Core/Minigin.h"

#pragma warning( push )  
#pragma warning( disable : 4100 )  
int main(int argc, char* argv[]) {
#pragma warning( pop )
	srand(static_cast<unsigned int>(time(0)));//Initialize RNG

	dae::Minigin engine;
	engine.Run();
    return 0;
}

