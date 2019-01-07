//
//  EntityManager.cpp
//  ElementalRoguelite
//
//  Created by Dylan Burden on 2018-09-27.
//  Copyright © 2018 ElementalRoguelike. All rights reserved.
//

#include "EntityManager.hpp"
#include <iostream>
#include <algorithm>
EntityID EntityManager::m_nextEntityId = 0;



EntityManager::EntityManager() :
    m_componentMananger( new ComponentManager() ),
    m_activeIds( {} ),
    m_deadEntities( {} ) {}

const unsigned int EntityManager::createEntity()
{
    // Get the id and increase the next id
    EntityID id;
    if( m_inactiveIds.empty() )     id = m_nextEntityId++;
    else
    {
        id = m_inactiveIds.back();
        m_inactiveIds.pop_back();
    }
    
    m_entityComponents.insert( std::make_pair( id, std::make_unique< SparseSet >( 50 ) ) );
    m_activeIds.push_back( id );
    return id;
}

void EntityManager::deadEntity( const unsigned int id )
{
    m_deadEntities.push_back( id );
    m_activeIds.erase( std::remove( m_activeIds.begin(), m_activeIds.end(), id ), m_activeIds.end() );
}

void EntityManager::clearDeadEntities()
{
    std::map< unsigned int, std::unique_ptr< SparseSet > >::iterator it;
    for( auto id : m_deadEntities )
    {
        it = m_entityComponents.find( id );
        m_entityComponents.erase( it );
        m_componentMananger->removeAllComponents( id );
        m_inactiveIds.push_back( id );
    }
    m_deadEntities.clear();
}



bool EntityManager::hasComponents( const EntityID entityId, const std::vector< std::string >& types )
{
    ComponentID id;
    for( auto i : types )
    {
        id = m_componentMananger->getId( i );
        if( id == 123456 )
        {
            return false;
        }
        else
        {
            if( !m_entityComponents[ entityId ]->lookUp( id ) )
            {
                return false;
            }
        }
    }
    
    return true;
}

const std::vector< EntityID > EntityManager::getEntitiesWithComponents( const std::vector< std::string >& types )
{
    std::vector< EntityID > returnVec;
    
    for( EntityID id : m_activeIds )
    {
        if( hasComponents( id, types ) )
        {
            returnVec.push_back( id );
        }
    }
    
    return returnVec;
}

std::shared_ptr< IComponent > EntityManager::getComponent( const EntityID id, const std::string& type )
{
    return m_componentMananger->getComponent( id, type );
}

void EntityManager::removeComponent( const EntityID entityId, const std::string& type )
{
    ComponentID id = m_componentMananger->getId( type );
    if( id != 123456 )
    {
        m_entityComponents[ entityId ]->remove( id );
        m_componentMananger->removeComponent( entityId, type );
    }
}

void EntityManager::toString()
{
    std::cout << "\n\nActive: ";
    for( auto i : m_activeIds )
    {
        std::cout << i << " ";
    }
    std::cout << "\n\nDead: ";
    for( auto i : m_deadEntities )
    {
        std::cout << i << " ";
    }
    std::cout << "\n\n";
    for( auto i = m_entityComponents.begin(); i != m_entityComponents.end(); ++i )
    {
        std::cout << (*i).first << ":\n";
        (*i).second->listItems();
    }
    
    m_componentMananger->toString();
}


