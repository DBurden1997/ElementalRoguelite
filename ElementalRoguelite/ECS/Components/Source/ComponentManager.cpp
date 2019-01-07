//
//  ComponentManager.cpp
//  ElementalRoguelite
//
//  Created by Dylan Burden on 2018-09-29.
//  Copyright © 2018 ElementalRoguelike. All rights reserved.
//

#include "ComponentManager.hpp"
#include <iostream>

ComponentManager::ComponentManager() {}

std::shared_ptr<IComponent> ComponentManager::getComponent( const EntityID ownerId, const std::string& type )
{
    // If this type has an id type mapped
    if( m_typeIds.find( type ) != m_typeIds.end() )
    {
        // Get the id for this type
        ComponentID id = m_typeIds[ type ];
        // Get the position of the component for this owner
        int pos = m_componentOwners[ id ]->getPos( ownerId );
        // If the component was found
        if( pos != -1 )
        {
            return m_allComponents[ id ][ pos ];
        }
    }
    return nullptr;
}

void ComponentManager::removeComponent( const unsigned int ownerId, const std::string& type )
{
    // If this type has an id type mapped
    if( m_typeIds.find( type ) != m_typeIds.end() )
    {
        // Get the id for this type
        ComponentID id = m_typeIds[ type ];
        // Get the position of that entities component of this type
        int pos = m_componentOwners[ id ]->getPos( ownerId );
        if( pos != -1 )
        {
            // Swap this component to the back then remove it
            if( pos != m_allComponents[ id ].size() - 1 )
            {
                m_allComponents[ id ][ pos ] = std::move(m_allComponents[ id ].back());
            }
            m_allComponents[ id ].pop_back();
            // Remove the owner from the sparse set for this component type
            m_componentOwners[ id ]->remove( ownerId );
        }
    }
}

void ComponentManager::removeAllComponents( const EntityID ownerId )
{
    for( auto i = m_typeIds.begin(); i != m_typeIds.end(); ++i )
    {
        removeComponent( ownerId, (*i).first );
    }
}

ComponentID ComponentManager::getId( const std::string& type )
{
    if( m_typeIds.find( type ) != m_typeIds.end() )
    {
        return m_typeIds[ type ];
    }
    
    //Fail value
    return 123456;
}

void ComponentManager::toString()
{
    std::cout << "COMPONENT MANAGER STATUS\n\n";
    
    // Print the map of type to id
    for( auto i = m_typeIds.begin(); i != m_typeIds.end(); ++i )
    {
        std::cout << (*i).first << " id is "
         << (*i).second << "\n";
    }
    std::cout << "\n\n";
    for( auto i = m_componentOwners.begin(); i != m_componentOwners.end(); ++i )
    {
        std::cout << (*i).first << ":\n";
        (*i).second->listItems();
    }
    std::cout << "\n\n";
    for( auto i = m_allComponents.begin(); i != m_allComponents.end(); ++i )
    {
        std::cout << (*i).first << ":\n";
        for( const auto& j : (*i).second )
        {
            j->toString();
        }
    }
    
}



