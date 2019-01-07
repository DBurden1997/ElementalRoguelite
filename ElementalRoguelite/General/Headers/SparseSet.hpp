//
//  SparseSet.hpp
//  ElementalRoguelite
//
//  Created by Dylan Burden on 2018-09-27.
//  Copyright © 2018 ElementalRoguelike. All rights reserved.
//

#ifndef SparseSet_hpp
#define SparseSet_hpp

#include <memory>

class SparseSet
{
    //The dense array
    std::unique_ptr<unsigned int[]> m_dense;
    
    //The sparse array
    std::unique_ptr<unsigned int[]> m_sparse;
    
    //The number of elements currently in the set
    unsigned int m_end = 0;
    
    //The size of the sets
    const size_t m_size;
    
public:
    //Constructor
    SparseSet( size_t arraySize );
    
    //Add an element to the set
    bool insert( const unsigned int k );
    
    //Check if an element is in the set
    const bool lookUp( const unsigned int k ) const;
    
    // Get the position of a certain element
    const unsigned int getPos( const unsigned int k );
    
    //Iterate through the elements of the set
    void listItems() const;
    
    //Clear the set
    void clear();
    
    //Remove an element from the set
    void remove( const unsigned int k );
};

#endif /* SparseSet_hpp */
