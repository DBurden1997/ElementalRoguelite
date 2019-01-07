//
//  EventList.hpp
//  ElementalRoguelite
//
//  Created by Dylan Burden on 2018-10-24.
//  Copyright © 2018 ElementalRoguelike. All rights reserved.
//

#ifndef EventList_hpp
#define EventList_hpp

#include "Events.hpp"
#include "Vec2D.hpp"

/////   INPUT EVENTS   /////

template< class Derived >
class ControlEvent : public Event< ControlEvent<Derived> >
{
    // The id of the player who gave a control
    const unsigned int m_controllerId;
    
public:
    // Constructor
    ControlEvent( Event_Type_Enum controlType, const unsigned int controllerId );
    
    // Get the controller id
    const unsigned int controllerId() const;
};

template< class Derived >
ControlEvent<Derived>::ControlEvent( Event_Type_Enum controlType, const unsigned int controllerId ) :
    Event<ControlEvent<Derived> >( controlType ),
    m_controllerId( controllerId ) {}

class MoveUpEvent : public ControlEvent< MoveUpEvent >
{
public:
    // Constructor
    MoveUpEvent( const unsigned int controllerId  ) : ControlEvent( EVENT_MOVE_UP, controllerId ) {}
};

class HaltUpEvent : public ControlEvent< HaltUpEvent >
{
public:
    // Constructor
    HaltUpEvent( const unsigned int controllerId  ) : ControlEvent( EVENT_HALT_UP, controllerId ) {}
};

class MoveDownEvent : public ControlEvent< MoveDownEvent >
{
public:
    // Constructor
    MoveDownEvent( const unsigned int controllerId  ) : ControlEvent( EVENT_MOVE_DOWN, controllerId ) {}
};

class HaltDownEvent : public ControlEvent< HaltDownEvent >
{
public:
    // Constructor
    HaltDownEvent( const unsigned int controllerId  ) : ControlEvent( EVENT_HALT_DOWN, controllerId ) {}
};

class MoveLeftEvent : public ControlEvent< MoveLeftEvent >
{
public:
    // Constructor
    MoveLeftEvent( const unsigned int controllerId  ) : ControlEvent( EVENT_MOVE_LEFT, controllerId ) {}
};

class HaltLeftEvent : public ControlEvent< HaltLeftEvent >
{
public:
    // Constructor
    HaltLeftEvent( const unsigned int controllerId  ) : ControlEvent( EVENT_HALT_LEFT, controllerId ) {}
};

class MoveRightEvent : public ControlEvent< MoveRightEvent >
{
public:
    // Constructor
    MoveRightEvent( const unsigned int controllerId  ) : ControlEvent( EVENT_MOVE_RIGHT, controllerId ) {}
};

class HaltRightEvent : public ControlEvent< HaltRightEvent >
{
public:
    // Constructor
    HaltRightEvent( const unsigned int controllerId  ) : ControlEvent( EVENT_HALT_RIGHT, controllerId ) {}
};

/////   OTHER   /////

class MovementEvent : public Event< MovementEvent >
{
public:
    unsigned int m_entId;
    bool m_axis;
    int m_dir;
    
    // Constructor
    MovementEvent( unsigned int entId, bool axis, int dir ) : Event( EVENT_MOVEMENT ), m_entId( entId ), m_axis( axis ), m_dir( dir ){}
    
};

#endif /* EventList_hpp */
