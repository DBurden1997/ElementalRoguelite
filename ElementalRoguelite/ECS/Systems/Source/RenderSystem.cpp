//
//  RenderSystem.cpp
//  ElementalRoguelite
//
//  Created by Dylan Burden on 2018-09-30.
//  Copyright © 2018 ElementalRoguelike. All rights reserved.
//

#include "RenderSystem.hpp"
#include <iostream>

RenderSystem::RenderSystem( std::shared_ptr< TextureManager > textureManager, std::shared_ptr< SDL_Renderer > renderer ) :
    m_textureManager( textureManager ),
    m_renderer( renderer ){}

void RenderSystem::renderEntities()
{
    m_renderableEntities = m_entityManager->getEntitiesWithComponents( { "transform", "graphic" } );
    
    for( EntityID id : m_renderableEntities )
    {
        // Get the transform and graphic components
        std::shared_ptr< TransformComponent > transform = std::dynamic_pointer_cast< TransformComponent >( m_entityManager->getComponent( id, "transform" ) );
        std::shared_ptr< GraphicComponent > graphic = std::dynamic_pointer_cast< GraphicComponent >( m_entityManager->getComponent( id, "graphic" ) );
        
        
        
        // Render it
        m_textureManager->getTexture( graphic->m_spriteSheet )->render( m_renderer, transform->m_position.first(), transform->m_position.second(), graphic->m_spriteClip );
    }
}

void RenderSystem::update()
{
    renderEntities();
}
