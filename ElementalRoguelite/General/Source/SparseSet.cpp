//
//  SparseSet.cpp
//  ElementalRoguelite
//
//  Created by Dylan Burden on 2018-09-27.
//  Copyright © 2018 ElementalRoguelike. All rights reserved.
//

#include "SparseSet.hpp"
#include <iostream>
#include <algorithm>

SparseSet::SparseSet( size_t arraySize ):
    m_dense( new unsigned int[ arraySize ] ),
    m_sparse( new unsigned int[ arraySize ] ),
    m_end( 0 ),
    m_size( arraySize )
{
    std::fill_n( m_dense.get(), m_size, m_size + 1 );
    std::fill_n( m_sparse.get(), m_size, m_size + 1 );
}

bool SparseSet::insert( const unsigned int k )
{
    // The value inserted must be less than the size of the arrays
    if( k < m_size )
    {
        // The value is not already in the set
        if( !lookUp( k ) )
        {
            // Insert the element
            m_dense[ m_end ] = k;
            m_sparse[ k ] = m_end;
            ++m_end;
            return true;
        }
    }
    return false;
}

const bool SparseSet::lookUp( const unsigned int k ) const
{
    // The value must be less than the size of the arrayss
    if( k < m_size )
    {
        //Check if the element is in the set
        return ( ( m_dense[ m_sparse[ k ] ] == k ) && ( m_sparse[ k ] < m_end ) );
    }
    return false;
}

const unsigned int SparseSet::getPos( const unsigned int k )
{
    if( lookUp( k ))
    {
        return m_sparse[ k ];
    }
    return -1;
}

void SparseSet::listItems() const
{
    std::cout << "Dense: ";
    for( int i = 0; i < m_size; ++i )
    {
         std::cout << m_dense[i] << " ";
    }
    std::cout << "\nSparse: ";
    for( int i = 0; i < m_size; ++i )
    {
        std::cout << m_sparse[i] << " ";
    }
    std::cout << "\nEnd is: " << m_end <<"\n\n\n";
}

void SparseSet::clear()
{
    m_end = 0;
}

void SparseSet::remove( const unsigned int k )
{
    // The values must be less than the size of the arrays
    if( k < m_size )
    {
        // If the element is in the array
        if( lookUp( k ) )
        {
            // Remove the element
            m_dense[ m_sparse[ k ] ] = m_dense[ m_end - 1 ];
            m_sparse[ m_dense[ m_end - 1 ] ] = m_sparse[ k ];
            --m_end;
        }
    }
}
