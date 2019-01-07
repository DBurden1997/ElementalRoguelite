//
//  MapReader.cpp
//  ElementalRoguelite
//
//  Created by Dylan Burden on 2018-09-25.
//  Copyright © 2018 ElementalRoguelike. All rights reserved.
//

#include "MapReader.hpp"

#include <string>
#include <vector>
#include <fstream>
#include <sstream>

MapReader::MapReader() {};

std::vector< std::vector< std::vector< int > > > MapReader::readMapFile( const std::string &fileName ) const
{
    //The vector to be returned
    std::vector< std::vector< std::vector< int > > > mapData = {};
    
    //Variabel to hold current line
    std::string line = "";
    //Open the file and read from it
    std::ifstream mapFile( fileName );
    if( mapFile.is_open() ) {
        getline( mapFile, line );
        //Create a string stream to read from lines
        std::istringstream lineParser( line );
        char c;
        lineParser.get( c );
        if( c != '[' )
        {
            printf( "Improper lvl file format!\n Expected '[' character!\n" );
            return {};
        }
        else {
            //Flag for finished reading
            bool finished = false;
            //While the file is not empty and we are not finisihed
            while( getline( mapFile, line ) && !finished ) {
                //Clear the string stream and get read the next line
                lineParser.clear();
                lineParser.str( line );
                lineParser.get( c );
                //If we get a closing square bracket the file is over
                if( c == ']' ) {
                    finished = true;
                }
                //Otherwise pass the line to the row reader function
                else {
                    std::vector< std::vector < int > > levelRow = readMapRow( line );
                    if( levelRow.empty() ) {    //If the returned function is empty there has been an error
                        return {};
                    }
                    //Otherwise add the row to the mapData
                    else {
                        mapData.push_back( levelRow );
                        mapData.size();
                    }
                }
            }
        }
    }
    else {
        printf( "Unable to open file %s\n", fileName.c_str() );
    }
    //Return the data
    return mapData;
}

std::vector< std::vector< int > > MapReader::readMapRow( const std::string& line ) const
{
    //Vector holding row informaion
    std::vector< std::vector< int > > rowData = {};
    
    std::istringstream lineParser( line );
    char c;
    lineParser.get( c );
    if( c != '{' ) {
        printf( "Improper lvl format!\nExpected '{'!\n" );
        return {};
    }
    else {
        lineParser.get( c );
        bool finished = false;
        //While there is more to read and we are not finished
        while( lineParser.rdbuf()->in_avail() != 0 && !finished ) {
            if( c != '(' ) {
                printf( "Improper lvl format!\nExpected '('!\n" );
                return {};
            }
            else {
                //Get a string containing tile info to pass to tile parser
                std::string tileInfo = "";
                for( lineParser.get( c ); c != ')'; lineParser.get( c ) ) {
                    tileInfo += c;
                }
                //Read tile data and handle result
                std::vector< int > tile = readMapTile( tileInfo );
                if( tile.empty() ) {
                    return {};
                }
                else {
                    rowData.push_back( tile );
                }
                //Check for required characters and continue if ok
                lineParser.get( c );
                if( c == '}' ) {
                    finished = true;
                }
                else if( c != ',' ) {
                    printf( "Improper lvl format!\nExpected ','!\n");
                }
                else {
                    lineParser.get( c );
                }
            }
        }
    }
    //Return row data
    return rowData;
}

std::vector< int > MapReader::readMapTile( const std::string &tile ) const
{
    //Vector holding tile info to return
    std::vector< int > tileData = {};
    //Create a string stream
    std::istringstream tileParser( tile );
    char c;
    //Data to return
    int type;
    int collidable;
    //Read the first integer into type
    tileParser >> type;
    //Check for the required comma
    tileParser.get( c );
    if( c != ',' ) {
        printf( "Expected ','!\n" );
        return {};
    }
    //Read the next integer into collidabel
    tileParser >> collidable;
    
    //Add the data to the vector and return it
    tileData.push_back( type );
    tileData.push_back( collidable );
    return tileData;
}
