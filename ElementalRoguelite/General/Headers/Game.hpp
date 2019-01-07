//
//  Game.hpp
//  ElementalRoguelite
//
//  Created by Dylan Burden on 2018-09-24.
//  Copyright © 2018 ElementalRoguelike. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <memory>
#include "Helper.hpp"
#include "TextureManager.hpp"
#include "MapManager.hpp"
#include "EntityManager.hpp"
#include "RenderSystem.hpp"
#include "MovementSystem.hpp"
#include "InputSystem.hpp"
#include "CollisionSystem.hpp"
#include "InputHandler.hpp"
#include "Events.hpp"

class Game
{
    //Start SDL subsystems
    bool initialize();
    
    //Run the game loop
    void gameLoop();
    
    //Handle input
    bool handleEvents( SDL_Event e );
    
    //Perform logic
    void performLogic();
    
    //Render the scene
    void renderScene();
    
    //Shut down SDL subsytems
    void shutDown();
    
    //The game window and renderer
    std::shared_ptr<SDL_Window> m_window;
    std::shared_ptr<SDL_Renderer> m_renderer;
    
    //Set up managers
    std::shared_ptr<TextureManager> m_textureManager;
    std::shared_ptr<MapManager> m_mapManager;
    std::shared_ptr<EntityManager> m_entityManager;
    std::shared_ptr<InputHandler> m_inputHandler;
    
    // List of game systems
    std::shared_ptr< RenderSystem > m_renderSystem;
    std::shared_ptr< MovementSystem > m_movementSystem;
    std::shared_ptr< InputSystem > m_inputSystem;
    std::shared_ptr< CollisionSystem > m_collisionSystem;
    std::shared_ptr< Publisher > m_publisher;
    
public:
    //Constructor
    Game();
    
    //Run the game
    void run();
};

#endif /* Game_hpp */
