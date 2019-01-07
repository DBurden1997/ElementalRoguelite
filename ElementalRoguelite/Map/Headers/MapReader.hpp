//
//  MapReader.hpp
//  ElementalRoguelite
//
//  Created by Dylan Burden on 2018-09-25.
//  Copyright © 2018 ElementalRoguelike. All rights reserved.
//

#ifndef MapReader_hpp
#define MapReader_hpp

#include <string>
#include <vector>

class MapReader
{
    //Read a row/line of map data
    std::vector< std::vector< int > > readMapRow( const std::string& line) const;
    
    //Read informtaion about a single tile
    std::vector< int > readMapTile( const std::string& tile ) const;
    
public:
    //Constructor
    MapReader();
    
    //Reads a .lvl file and returns the map data in a vector
    std::vector< std::vector< std::vector< int > > > readMapFile( const std::string& fileName ) const;
};

#endif /* MapReader_hpp */
