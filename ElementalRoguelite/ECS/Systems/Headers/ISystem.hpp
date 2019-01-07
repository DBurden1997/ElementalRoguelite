//
//  ISystem.hpp
//  ElementalRoguelite
//
//  Created by Dylan Burden on 2018-09-30.
//  Copyright © 2018 ElementalRoguelike. All rights reserved.
//

#ifndef ISystem_hpp
#define ISystem_hpp

#include <memory>
#include "EntityManager.hpp"
#include "Events.hpp"

class ISystem : public ISubscriber
{
protected:
    // Constructor
    ISystem();
    
    // A pointer to an entity manager
    static std::shared_ptr<EntityManager> m_entityManager;
    
public:
    // Initialize the entity manager
    static void setEntityManager( std::shared_ptr< EntityManager > entityManager );
    
    // Perform the system operations
    virtual void update() = 0;
    
    // Handle events
    virtual void handleEvent( const Event_Type_Enum type, IEvent& event ) override = 0;
};

#endif /* ISystem_hpp */
