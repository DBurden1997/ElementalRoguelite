//
//  Game.cpp
//  ElementalRoguelite
//
//  Created by Dylan Burden on 2018-09-24.
//  Copyright © 2018 ElementalRoguelike. All rights reserved.
//

#include "Game.hpp"

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include "Helper.hpp"
#include "TextureManager.hpp"
#include "MapManager.hpp"
#include "InputHandler.hpp"
#include "Events.hpp"
#include "EventList.hpp"

#include "PlayerControlComponent.hpp"
///// PRIVATE /////

bool Game::initialize()
{
    //Success flag
    bool success = true;
    
    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) <0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n",  SDL_GetError() );
        success = false;
    }
    else
    {
        //Create the window
        m_window = sdl2::make_window( "Elemental Prototype", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                               1280, 720, SDL_WINDOW_SHOWN );
        
        if( m_window == nullptr )
        {
            printf( "Window could not be created! SDL Erroe: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            //Set texture filtering to linear
            if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "0" ) )
            {
                printf( "Warning: Nearest neighbour filtering not enabled!" );
            }
            //Create renderer for window
            m_renderer = sdl2 ::make_renderer( m_window, -1, SDL_RENDERER_ACCELERATED |SDL_RENDERER_PRESENTVSYNC );
            if( m_renderer == nullptr )
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            else
            {
                //Set logical size
                SDL_RenderSetLogicalSize( m_renderer.get(), 640, 360 );
                
                //Initialize render color
                SDL_SetRenderDrawColor( m_renderer.get(), 0x00, 0x00, 0x00, 0xff );
                
                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) && imgFlags ) )
                {
                    printf( "Could not initialize PNG loading! SDL_image Error: %s\n", IMG_GetError() );
                    success = false;
                }
            }
        }
    }
    
    //Return success flag
    return success;
}

void Game::gameLoop()
{
    //Quit flag
    bool quit = false;
    
    //Event to handle
    SDL_Event e;
    
    m_publisher = std::make_shared<Publisher>();
    m_inputHandler = std::make_shared<InputHandler>( m_publisher );
    
    //Create managers
    m_textureManager = std::make_shared<TextureManager>( m_renderer );
    m_mapManager = std::make_shared<MapManager>( 32, 32 );
    m_entityManager = std::make_shared< EntityManager >();
    
    ISystem::setEntityManager( m_entityManager );
    ISubscriber::setPublisher(m_publisher );
    
    // Create systems
    m_renderSystem = std::make_unique<RenderSystem>( m_textureManager, m_renderer );
    m_movementSystem = std::make_unique<MovementSystem>();
    m_publisher->subscribe<MovementEvent>( m_movementSystem );
    m_collisionSystem = std::make_unique<CollisionSystem>( m_mapManager );
    m_inputSystem = std::make_unique<InputSystem>();
    m_publisher->subscribe<MoveUpEvent>( m_inputSystem );
    m_publisher->subscribe<HaltUpEvent>( m_inputSystem );
    m_publisher->subscribe<MoveDownEvent>( m_inputSystem );
    m_publisher->subscribe<HaltDownEvent>( m_inputSystem );
    m_publisher->subscribe<MoveLeftEvent>( m_inputSystem );
    m_publisher->subscribe<HaltLeftEvent>( m_inputSystem );
    m_publisher->subscribe<MoveRightEvent>( m_inputSystem );
    m_publisher->subscribe<HaltRightEvent>( m_inputSystem );
    
    HaltUpEvent r(1);
    std::cout << r.getSubscribers().size();
    
    //Load assets
    m_mapManager->loadMap( "ProtoMap", *m_textureManager.get() );
    
    EntityID player = m_entityManager->createEntity();
    EntityID enemy = m_entityManager->createEntity();
    
    m_entityManager->addComponent< PlayerControlComponent >( player );
    m_entityManager->addComponent< TransformComponent >( player, 250, 260, 0, 0, 16, 16 );
    m_entityManager->addComponent< GraphicComponent >( player, "plantPlayerSword", 0, 0, 32, 32 );
    m_entityManager->addComponent< CollisionComponent >( player, "boundingBox", 18, 24, 7, 7 );
    
    m_entityManager->addComponent< TransformComponent >(enemy, 200, 130, 0, 0, 16, 16 );
    m_entityManager->addComponent< GraphicComponent >( enemy, "CharacterSpriteSheet", 32, 0, 32, 32 );
    m_entityManager->addComponent< CollisionComponent >( enemy, "boundingBox", 32, 32, 0, 0 );
    
    //While the game is running
    while( !quit )
    {
        //Handle inputs
        quit = handleEvents( e );
        //Perform logic
        performLogic();
        //Render the resulting scene
        renderScene();
    }
}

bool Game::handleEvents( SDL_Event e )
{
    //Quit flag
    bool wantsToExit = false;
    
    //Handle events on queue
    while( SDL_PollEvent( &e ) != 0 )
    {
        //If the user requests exit
        if( e.type == SDL_QUIT )
        {
            wantsToExit = true;;
        }
        m_inputHandler->getIntent( e );
    }
    
    return wantsToExit;
}

void Game::performLogic()
{
    m_inputSystem->update();
    m_movementSystem->update();
    m_collisionSystem->update();
}

void Game::renderScene()
{
    //Clear the screen
    SDL_SetRenderDrawColor( m_renderer.get(), 0x00, 0x00, 0x00, 0xff );
    SDL_RenderClear( m_renderer.get() );
    
    //Render the scene
    m_mapManager->renderMap( m_renderer );
    m_renderSystem->update();
    
    //Update the screen
    SDL_RenderPresent( m_renderer.get() );
}

void Game::shutDown()
{
    //Exit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}


///// PUBLIC /////
Game::Game(){}

void Game::run()
{
    //Initialize SDL
    if( initialize() )
    {
        if( m_window == nullptr ) std::cout << "Window null\n";
        if( m_renderer == nullptr ) std::cout << "Reneder null\n";
        //Run the game loop
        gameLoop();
    }
    
    //Clean up variables
    shutDown();
}
