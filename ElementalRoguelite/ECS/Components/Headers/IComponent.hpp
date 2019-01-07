//
//  IComponent.hpp
//  ElementalRoguelite
//
//  Created by Dylan Burden on 2018-09-30.
//  Copyright © 2018 ElementalRoguelike. All rights reserved.
//

#ifndef IComponent_hpp
#define IComponent_hpp

#include <string>

typedef unsigned int EntityID;
typedef unsigned int ComponentID;

static inline ComponentID nextId()
{
    static ComponentID nextId = 0;
    return nextId++;
}

class IComponent
{
public:
    virtual ComponentID id() = 0;
    virtual void toString() = 0;
};

template< class Derived >
class Component : public IComponent
{
    // The next component id to be assigned
    static ComponentID m_id;
    
    // The id number of the entity that owns this component
    const EntityID m_owner;
    
    // The type of the component
    const std::string m_type;
    
    virtual void toString() override = 0;
    
protected:
    //Constructor
    Component( const EntityID ownerId, const std::string& type ) :
        m_owner( ownerId ),
        m_type( type ) {}
    
public:
    //Constructor for blank component
    Component() :
        m_owner( 1000000 ),
        m_type( "blank" ) {}
    
    // Getters
    ComponentID id() override{ return m_id; }
    const std::string& type() { return m_type; }
    const EntityID owner() { return m_owner; }
};

template<typename Derived>
ComponentID Component<Derived>::m_id = nextId();

#endif /* IComponent_hpp */
