//
//  CollisionSystem.hpp
//  ElementalRoguelite
//
//  Created by Dylan Burden on 2018-10-29.
//  Copyright © 2018 ElementalRoguelike. All rights reserved.
//

#ifndef CollisionSystem_hpp
#define CollisionSystem_hpp

#include "ISystem.hpp"
#include "CollisionComponent.hpp"
#include "MapManager.hpp"
#include <vector>
#include <memory>

class CollisionSystem : public ISystem
{
    //Pointer to the MapManager
    std::weak_ptr<MapManager> m_mapManager;
    
    //List of collision components
    static std::vector< EntityID > m_collisionEntities;
    
    //Check collision of background and other entities
    void checkBackgroundCollisions( EntityID id );
    void checkEntityCollisions( EntityID id );
public:
    //Constructor
    CollisionSystem( std::shared_ptr<MapManager> mapManager );
    
    // Perform the system operations
    virtual void update() override;
    
    // Handle events
    virtual void handleEvent( const Event_Type_Enum type, IEvent& event ) override;
};

#endif /* CollisionSystem_hpp */
