//
//  Events.hpp
//  ElementalRoguelite
//
//  Created by Dylan Burden on 2018-10-16.
//  Copyright © 2018 ElementalRoguelike. All rights reserved.
//

#ifndef Events_hpp
#define Events_hpp

#include <vector>
#include <memory>
#include <algorithm>
#include <iostream>

#include "EventEnum.hpp"

// Declaration

class ISubscriber;

static inline std::vector< std::shared_ptr<ISubscriber> > initSubscribers() { return {}; }

class IEvent
{
protected:
    // Constructor
    IEvent( const Event_Type_Enum type );
    
    // Unique typename
    const Event_Type_Enum m_type;
    
public:
    // Get the list of subscribers
    virtual std::vector< std::shared_ptr<ISubscriber> > getSubscribers() const = 0;
};

template< class Derived >
class Event : public IEvent
{
    // Unique list of subscribers to an event type
    static std::vector< std::shared_ptr<ISubscriber> > m_subscribers;
    
protected:
    // Constructor
    Event( const Event_Type_Enum type );
    
public:
    // Attach a subscriber to this event type
    static void attach( std::shared_ptr<ISubscriber> subscriber );
    // Detach a subscriber from this event type
    static void detach( std::shared_ptr<ISubscriber> subscriber );
    // Get the list of subscribers
    virtual std::vector< std::shared_ptr<ISubscriber> > getSubscribers() const override;
    // Get the typename
    const Event_Type_Enum type() const;
};

class Publisher
{
    // Publish an event
    template< typename EventType >
    void publish( EventType& event );
    
public:
    // Constructor
    Publisher();
    
    // Attach a Subscriber to an Event
    template< typename EventType >
    void subscribe( std::shared_ptr<ISubscriber> sub ) const;
    
    // Detach a Subscriber from an Event
    template< typename EventType >
    void unsubscribe( std::shared_ptr<ISubscriber> sub ) const;
    
    // Raise an event of a certain type
    template< typename eventType, typename... Arguments >
    void raiseEvent( Arguments&&... args );
};

class ISubscriber
{
protected:
    // Constructor
    ISubscriber();
    
    // A pointer to the publisher to receive events from
    static std::shared_ptr< Publisher > m_publisher;
    
public:
    // Initialize the publisher
    static void setPublisher( std::shared_ptr<Publisher> publisher );
    
    // Handle an event
    virtual void handleEvent( const Event_Type_Enum type, IEvent& event ) = 0;
};

// Implementation

// Event Methods

template< class Derived >
std::vector< std::shared_ptr<ISubscriber> > Event<Derived>::m_subscribers = initSubscribers();

template< class Derived >
Event<Derived>::Event( const Event_Type_Enum type ) : IEvent( type ) {}

template< class Derived >
void Event<Derived>::attach( std::shared_ptr<ISubscriber> subscriber )
{
    if( std::find(m_subscribers.begin(), m_subscribers.end(), subscriber ) == m_subscribers.end() )
    {
        m_subscribers.push_back( subscriber );
    }
}

template< class Derived >
void Event<Derived>::detach( std::shared_ptr<ISubscriber> subscriber )
{
    m_subscribers.erase( std::remove( m_subscribers.begin(), m_subscribers.end(), subscriber), m_subscribers.end() );
}

template< class Derived >
std::vector< std::shared_ptr< ISubscriber > > Event<Derived>::getSubscribers() const
{
    return m_subscribers;
}

template< class Derived >
const Event_Type_Enum Event<Derived>::type() const
{
    return m_type;
}

// Publisher Methods
template< typename EventType >
void Publisher::publish( EventType &event )
{
    std::cout << "Publishing " << event.type() << " event\n";
    for( const auto& subscriber : event.getSubscribers() )
    {
        subscriber->handleEvent( event.type(), event );
    }
}

template< typename EventType >
void Publisher::subscribe( std::shared_ptr<ISubscriber> sub ) const
{
    EventType::attach( sub );
}

template< typename EventType >
void Publisher::unsubscribe( std::shared_ptr<ISubscriber> sub ) const
{
    EventType::detach( sub );
}

template< typename EventType, typename... Arguments >
void Publisher::raiseEvent( Arguments&&... args )
{
    EventType e = EventType( std::forward<Arguments>(args)... );
    std::cout << "Raising " << e.type() << " event\n";
    publish<EventType>( e );
}

#endif /* Events_hpp */
