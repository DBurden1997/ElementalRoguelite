//
//  ComponentManager.hpp
//  ElementalRoguelite
//
//  Created by Dylan Burden on 2018-09-29.
//  Copyright © 2018 ElementalRoguelike. All rights reserved.
//

#ifndef ComponentManager_hpp
#define ComponentManager_hpp

#include <map>
#include <vector>
#include <memory>
#include <string>
#include "SparseSet.hpp"
#include "IComponent.hpp"

typedef unsigned int EntityID;
typedef unsigned int ComponentID;

class ComponentManager
{
    // A map of component ids to sparse sets containing the position of a given entity's component of that type
    std::map< ComponentID, std::unique_ptr< SparseSet > > m_componentOwners;
    
    // A map of component ids to lists of those components
    std::map< ComponentID, std::vector< std::shared_ptr< IComponent >  > > m_allComponents;
    
    // A map of component type to id
    std::map< std::string, ComponentID > m_typeIds;
    
public:
    //Constructor
    ComponentManager();
    
    // Add a component with arguments args
    template< typename T, typename... Arguments >
    auto addComponent( const EntityID ownerId, Arguments&&... args );
    
    // Get component of given type for the given entity id
    std::shared_ptr<IComponent> getComponent( const EntityID ownerId, const std::string& type );
    
    // Remove given entity's given component type
    void removeComponent( const EntityID ownerId, const std::string& type );
    
    // Remove all of the given entity's components
    void removeAllComponents( const EntityID ownerId );
    
    // Get the ids of the given types
    ComponentID getId( const std::string& type );
    
    // Print shit
    void toString();
    
};

template< typename T, typename... Arguments >
auto ComponentManager::addComponent( const EntityID ownerId, Arguments &&... args )
{
    // Create the new component
    auto newComponent = std::make_shared<T>( ownerId ,std::forward<Arguments>(args)... );
    
    ComponentID id = newComponent->id();
    
    // If this type has not been mapped to its id do so
    if( m_typeIds.find( newComponent->type() ) == m_typeIds.end() )
    {
        m_typeIds[ newComponent->type() ] = id;
    }
    
    // If this component type has no sparse set yet create one
    if( m_componentOwners.find( id ) == m_componentOwners.end() )
    {
        m_componentOwners.insert( std::pair< ComponentID, std::unique_ptr< SparseSet > >( id, std::make_unique<SparseSet>( 1000 ) ) );
    }
    // Insert the owning entity
    bool exists = !m_componentOwners[ id ]->insert( ownerId );
    // If this component type has no list yet create one
    if( m_allComponents.find( id ) == m_allComponents.end() )
    {
        m_allComponents.insert( std::pair< ComponentID, std::vector< std::shared_ptr< IComponent > > >( id, {} ) );
    }
    if( !exists)
    {
        // ADd the new component to the list
        m_allComponents[ id ].push_back( newComponent );
    }
    
    return newComponent;
}

#endif /* ComponentManager_hpp */
