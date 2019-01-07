
//
//  Helper.hpp
//  ElementalRoguelite
//
//  Created by Dylan Burden on 2018-09-24.
//  Copyright © 2018 ElementalRoguelike. All rights reserved.
//

#ifndef Helper_hpp
#define Helper_hpp

#include <stdio.h>
#include <system_error>
#include <memory>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

// Namesace allowing easy creation of unique and shared pointers for SDL types
namespace sdl2
{
    using window_ptr_t = std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>;
    using render_ptr_t = std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)>;
    using texture_ptr_t = std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)>;
    using surface_ptr_t = std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)>;
    
    //Template function for the creation of resources
    template< typename Creator, typename Destructor, typename... Arguments >
    auto make_resource( Creator c, Destructor d, Arguments&&... args )
    {
        //Create the resource with the given Creator function
        auto r = c( std::forward<Arguments>( args )... );
        
        //If the resource is not initialized throw an error
        if( !r )
        {
            throw std::system_error( errno, std::generic_category(), SDL_GetError() );
        }
        //Return a unique_ptr to the resource
        return std::unique_ptr<std::decay_t<decltype(*r)>, decltype(d)>(r, d);
    }
    
    //Helper function to create a window
    inline window_ptr_t make_window( const char* title, int x, int y, int w, int h, Uint32 flags )
    {
        return make_resource( SDL_CreateWindow, SDL_DestroyWindow, title, x, y, w, h, flags );
        
    }
    
    //Helper function to create a renderer
    inline render_ptr_t make_renderer( std::shared_ptr<SDL_Window> window, int index, Uint32 flags )
    {
        return make_resource( SDL_CreateRenderer, SDL_DestroyRenderer, window.get(), index, flags );
        
    }
    
    //Helper function to create a surface
    inline surface_ptr_t  make_surface( const char* path )
    {
        return make_resource( IMG_Load, SDL_FreeSurface, path );
    }
    
    //Helper function to create a texture
    inline texture_ptr_t make_texture( std::shared_ptr<SDL_Renderer> renderer, std::shared_ptr<SDL_Surface> surface )
    {
        return make_resource( SDL_CreateTextureFromSurface, SDL_DestroyTexture, renderer.get(), surface.get() );
    }
}

#endif /* Helper_hpp */
