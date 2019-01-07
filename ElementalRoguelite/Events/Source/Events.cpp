//
//  Events.cpp
//  ElementalRoguelite
//
//  Created by Dylan Burden on 2018-10-25.
//  Copyright © 2018 ElementalRoguelike. All rights reserved.
//

#include "Events.hpp"

// IEvent constructor
IEvent::IEvent( const Event_Type_Enum type) : m_type( type ){}

// Static publisher for all subscribers
std::shared_ptr<Publisher> ISubscriber::m_publisher = nullptr;

// Publisher constructor
Publisher::Publisher() {}

// Subscriber Methods
ISubscriber::ISubscriber() {}

void ISubscriber::setPublisher( std::shared_ptr<Publisher> publisher )
{
    m_publisher = publisher;
}
