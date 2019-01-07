//
//  InputSystem.hpp
//  ElementalRoguelite
//
//  Created by Dylan Burden on 2018-10-25.
//  Copyright © 2018 ElementalRoguelike. All rights reserved.
//

#ifndef InputSystem_hpp
#define InputSystem_hpp

#include "ISystem.hpp"

enum Input_Type_Enum {
    INPUT_MOVE_UP,
    INPUT_MOVE_DOWN,
    INPUT_MOVE_LEFT,
    INPUT_MOVE_RIGHT,
    INPUT_MAX
};

class InputSystem : public ISystem
{
    // The list of player controlled entities
    std::vector< EntityID > m_playerEntities;
    
    // A vector to tell whether a certain input is active
    std::vector< bool > m_inputActive;
public:
    // Constructor
    InputSystem();
    
    // Update system
    void update() override;
    
    // Handle events
    virtual void handleEvent( const Event_Type_Enum type, IEvent& event ) override;
};


#endif /* InputSystem_hpp */
