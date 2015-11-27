#include <SFML/Graphics.hpp>
#include <cmath>
#include "Framework.h"
#include <windows.h>
#include <time.h>

int main()
{
    srand(time(NULL));

    Init();

    Run();


    return EXIT_SUCCESS;
}

