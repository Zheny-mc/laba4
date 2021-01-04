#include <iostream>
#include "solution.h"

int main()
{
    Solution game;
    
    game.install_prohibition_places();
    game.install_obvious_lanterns_around_black_cells();

    return 0;
}