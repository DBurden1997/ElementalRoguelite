//
//  Texture.cpp
//  ElementalRoguelite
//
//  Created by Dylan Burden on 2018-09-25.
//  Copyright © 2018 ElementalRoguelike. All rights reserved.
//

#include "Texture.hpp"

#include <stdio.h>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include "Helper.hpp"

Texture::Texture( std::string name ) :m_name( name ) {}

Texture::~Texture()
{
    free();
}

bool Texture::loadFromFile( std::shared_ptr<SDL_Renderer> aRenderer, const std::string &path ) 
{
    //Free previous texture
    free();
    
    //The final texture
    std::shared_ptr<SDL_Texture> newTexture;
    
    //Load image at specified path
    std::shared_ptr<SDL_Surface> loadedSurface = sdl2::make_surface( path.c_str() );
    if( loadedSurface.get() == nullptr ) {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else {
        //Create texture from surface pixels
        newTexture = sdl2::make_texture( aRenderer, loadedSurface );
        if( newTexture == nullptr ) {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }
        else {
            //Get image dimensions
            m_width = loadedSurface->w;
            m_height = loadedSurface->h;
        }
    }
    
    //Return success
    m_texture = newTexture;
    return m_texture.get() != nullptr;
}

void Texture::free()
{
    //Free
    m_width = 0;
    m_height = 0;
}

void Texture::render( std::shared_ptr<SDL_Renderer> aRenderer, int x, int y, const SDL_Rect& clip ) const
{
    //Set rendering space and render to screen
    SDL_Rect renderQuad = { x, y, m_width, m_height };
    
    //Set clip rendering dimensions{
    renderQuad.w = clip.w;
    renderQuad.h = clip.h;
    
    //Render the texture
    SDL_RenderCopy( aRenderer.get(), m_texture.get(), &clip, &renderQuad );
}

int Texture::width() const
{
    return m_width;
}

int Texture::height()const
{
    return m_height;
}

std::string Texture::name() const
{
    return m_name;
}

