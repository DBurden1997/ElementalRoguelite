//
//  RenderSystem.hpp
//  ElementalRoguelite
//
//  Created by Dylan Burden on 2018-09-30.
//  Copyright © 2018 ElementalRoguelike. All rights reserved.
//

#ifndef RenderSystem_hpp
#define RenderSystem_hpp

#include <memory>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include "ISystem.hpp"
#include "TextureManager.hpp"
#include "TransformComponent.hpp"
#include "GraphicComponent.hpp"

class RenderSystem : public ISystem
{
    // List of all renderable entities
    std::vector< EntityID > m_renderableEntities;
    
    // Pointer to a texture manager
    std::shared_ptr< TextureManager > m_textureManager;
    
    // Pointer to a SDL renderer
    std::shared_ptr< SDL_Renderer > m_renderer;
    
    // Render the background
    void renderBackground();
    
    // Render the entities
    void renderEntities();
    
public:
    // Constructors
    RenderSystem( std::shared_ptr< TextureManager > textureManager, std::shared_ptr< SDL_Renderer > renderer );
    
    // Render the game
    virtual void update() override;
    
    // Handle events
    virtual void handleEvent( const Event_Type_Enum type, IEvent& event ) override {};
};

#endif /* RenderSystem_hpp */
