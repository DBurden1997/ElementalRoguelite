//
//  main.cpp
//  ElementalRoguelite
//
//  Created by Dylan Burden on 2018-09-23.
//  Copyright © 2018 ElementalRoguelike. All rights reserved.
//
//  The main function simply starts the game, and does nothing else
//

#include <iostream>
#include "Game.hpp"
#include <chrono>
#include "EntityManager.hpp"
#include "Vec2D.hpp"
#include "TransformComponent.hpp"
#include "GraphicComponent.hpp"

int main(int argc, const char * argv[])
{
    auto start = std::chrono::high_resolution_clock::now();
   
    Game game;
    game.run();
    
    auto end = std::chrono::high_resolution_clock::now();
    
    std::cout << "Process took : "
    << std::chrono::duration_cast<std::chrono::milliseconds>( end - start ).count() << "ms\n";
    
    return 0;
}
