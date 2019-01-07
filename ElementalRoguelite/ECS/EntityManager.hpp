//
//  EntityManager.hpp
//  ElementalRoguelite
//
//  Created by Dylan Burden on 2018-09-27.
//  Copyright © 2018 ElementalRoguelike. All rights reserved.
//

#ifndef EntityManager_hpp
#define EntityManager_hpp

#include <vector>
#include <map>
#include <memory>
#include "SparseSet.hpp"
#include "ComponentManager.hpp"

typedef unsigned int EntityID;
typedef unsigned int ComponentID;

class EntityManager
{
    // A component manager to manage components
    std::unique_ptr< ComponentManager > m_componentMananger;
    
    // The ID to be assigned to the next entity
    static EntityID m_nextEntityId;
    
    // A map of entity ids to sparse sets containing the components they contain
    std::map< EntityID, std::unique_ptr< SparseSet > > m_entityComponents;
    
    // A list of the active entity ids
    std::vector< EntityID > m_activeIds;
    
    // A list of entities to clear at end of frame
    std::vector< EntityID > m_deadEntities;
    
    // A list of ids not currently in use
    std::vector< EntityID > m_inactiveIds;
    
public:
    // Constructor
    EntityManager();
    
    // Create a new entity and return its id
    const EntityID createEntity();
    
    // Delete an entity
    void deadEntity( const EntityID id );
    
    // Clear all dead entities
    void clearDeadEntities();
    
    // Add a component
    template< typename T, typename... Arguments  >
    std::shared_ptr<T> addComponent( const EntityID entityId, Arguments&&... args );
    
    // Check if an entity has a certain combination of components
    bool hasComponents( const EntityID entityId, const std::vector< std::string >& types );
    
    // Get a list of components with the given component types
    const std::vector< EntityID > getEntitiesWithComponents( const std::vector< std::string >& types );
    
    // Get component
    std::shared_ptr< IComponent > getComponent( const EntityID id, const std::string& type );
    
    // Remove a component
    void removeComponent( const EntityID entityId, const std::string& type );
    
    //List all entities
    void toString();
};

template< typename T, typename... Arguments >
std::shared_ptr<T> EntityManager::addComponent( const EntityID entityId, Arguments&&... args )
{
    std::shared_ptr<T> newComponent = m_componentMananger->addComponent< T >( entityId, std::forward<Arguments> (args)... );
    m_entityComponents[ entityId ]->insert( newComponent->id() );
    return newComponent;
}

#endif /* EntityManager_hpp */
