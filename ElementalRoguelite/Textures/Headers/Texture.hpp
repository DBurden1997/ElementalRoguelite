//
//  Texture.hpp
//  ElementalRoguelite
//
//  Created by Dylan Burden on 2018-09-25.
//  Copyright © 2018 ElementalRoguelike. All rights reserved.
//

#ifndef Texture_hpp
#define Texture_hpp

#include <string>
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

class Texture
{
    //The actual SDL texture
    std::shared_ptr<SDL_Texture> m_texture;
    
    //The name of the texture
    std::string m_name;
    
    //The texture dimensions
    int m_width, m_height;
    
public:
    //Constructor
    Texture( std::string name );
    
    //Destructor
    ~Texture();
    
    //Load image from specified path
    bool loadFromFile( std::shared_ptr<SDL_Renderer> aRenderer, const std::string& path );
    
    //Deallocate texture
    void free();
    
    //Render texture at given point
    void render( std::shared_ptr<SDL_Renderer> aRenderer, int x, int y, const SDL_Rect& clip ) const;
    
    //Getters const
    int width() const;
    int height() const;
    std::string name() const;
    
};

#endif /* Texture_hpp */
