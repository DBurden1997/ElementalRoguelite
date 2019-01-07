//
//  Vec2D.hpp
//  Elemental
//
//  Created by Dylan Burden on 2018-09-18.
//  Copyright © 2018 Elemental. All rights reserved.
//

#ifndef Vec2D_hpp
#define Vec2D_hpp

#include <type_traits>
#include <cmath>
#include <string>
#include <iostream>
#include "Enable.hpp"

template < typename T, detail::enableIf< std::is_arithmetic< T > >... >
class Vec2D
{
    //The two members of the vector
    T m_first, m_second;
    
public:
    //Constructor given two values
    Vec2D( T first, T second ) : m_first( first ), m_second( second ) {}
    
    //Constructor given two vectors( points )
    //Returns the vector from first to another
    Vec2D( const  Vec2D<T>& start, const Vec2D<T>& end )
    {
        m_first = end.m_first - start.m_first;
        m_second = end.m_second - start.m_second;
    }
    
    //Getter functions
    //Get first element
    T first() const
    {
        return m_first;
    }
    //Get second element
    T second() const
    {
        return m_second;
    }
    //Set the first element
    void setFirst( T val )
    {
        m_first = val;
    }
    //Set the second element
    void setSecond( T val )
    {
        m_second = val;
    }
    void setValues( T firstVal, T secondVal )
    {
        m_first = firstVal;
        m_second = secondVal;
    }
    
    //Get the length of the vector
    float getLength() const
    {
        return sqrtf( float( m_first * m_first ) + float( m_second * m_second ) );
    }
    
    //Get the angle of the vector
    float getAngleRad() const
    {
        return atan2f( float(m_first), float(m_second) );
    }
    
    //Operator overrides
    void operator=( const Vec2D< T >& rhs )
    {
        m_first = rhs.m_first;
        m_second = rhs.m_second;
    }
    
    //Override addition
    Vec2D< T > operator+( const Vec2D< T >& rhs ) const
    {
        return Vec2D( m_first + rhs.m_first, m_second + rhs.m_second );
    }
    
    Vec2D< T >& operator+=( const Vec2D< T >& rhs )
    {
        m_first += rhs.m_first;
        m_second += rhs.m_second;
        
        return *this;
    }
    
    //Override subtraction
    Vec2D< T > operator-( const Vec2D< T >& rhs ) const
    {
        return Vec2D( m_first - rhs.m_first, m_second - rhs.m_second );
    }
    
    Vec2D< T >& operator-=( const Vec2D< T >& rhs )
    {
        m_first -= rhs.m_first;
        m_second -= rhs.m_second;
        
        return *this;
    }
    
    //Override multiplication
    Vec2D< T > operator*( const int rhs ) const
    {
        return Vec2D( m_first * rhs, m_second * rhs );
    }
    Vec2D< T > operator*( const float rhs ) const
    {
        return Vec2D( m_first * rhs, m_second * rhs );
    }
    
    Vec2D< T >& operator*=( const int rhs )
    {
        m_first *= rhs;
        m_second *= rhs;
        
        return *this;
    }
    Vec2D< T >& operator*=( const float rhs )
    {
        m_first *= rhs;
        m_second *= rhs;
        
        return *this;
    }
    
    
    //Component-wise multiplication
    Vec2D< T > operator*( const Vec2D< T >& rhs ) const
    {
        return Vec2D( m_first * rhs.m_first, m_second * rhs.m_second );
    }
    
    Vec2D< T >& operator*=( const Vec2D< T >& rhs )
    {
        m_first *= rhs.m_first;
        m_second *= rhs.m_second;
        
        return *this;
    }
    
    //Override division
    Vec2D< T > operator/( const int rhs ) const
    {
        return Vec2D( m_first / rhs, m_second / rhs );
    }
    Vec2D< T > operator/( const float rhs ) const
    {
        return Vec2D( m_first / rhs, m_second / rhs );
    }
    
    Vec2D< T >& operator/=( const int rhs )
    {
        m_first /= rhs;
        m_second /= rhs;
        
        return *this;
    }
    Vec2D< T >& operator/=( const float rhs )
    {
        m_first /= rhs;
        m_second /= rhs;
        
        return *this;
    }
    //Override comparison 
    bool operator==( const Vec2D< T >& rhs ) const
    {
        return ( ( m_first == rhs.m_first ) && ( m_second == rhs.m_second ) );
    }
    bool operator!=( const Vec2D< T >& rhs ) const
    {
        return !( *this == rhs );
    }
    
    //Dot product
    T dot( const Vec2D< T >& other ) const
    {
        return ( m_first * other.m_first ) + ( m_second + other.m_second );
    }
    
    //Get angle between two vectors
    float getAngleBetween( const Vec2D< T > & other ) const
    {
        // angle = acos([A*B]/[|A||B|])
        return acos( float( dot( other ) / ( getLength() * other.getLength() ) ) );
    }
    
    //Normalize the vector, changing the contents
    void normalize()
    {
        float length = getLength();
        m_first /= length;
        m_second /= length;
    }
    
    //Return a new vector that is this vectors normal
     Vec2D< float > getNormal() const
    {
        float length = getLength();
        return Vec2D< float >( m_first / length, m_second / length );
    }
    
    //Print info about the vector
    friend std::ostream& operator<<( std::ostream& os, const Vec2D< T >& rhs )
    {
        os << "< " << rhs.m_first << ", " << rhs.m_second << " >\n";
        return os;
    }
};

#endif /* Vec2D_hpp */
