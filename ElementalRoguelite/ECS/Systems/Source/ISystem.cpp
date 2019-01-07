//
//  ISystem.cpp
//  ElementalRoguelite
//
//  Created by Dylan Burden on 2018-09-30.
//  Copyright © 2018 ElementalRoguelike. All rights reserved.
//

#include "ISystem.hpp"

std::shared_ptr<EntityManager> ISystem::m_entityManager = nullptr;

ISystem::ISystem() {}

void ISystem::setEntityManager( std::shared_ptr<EntityManager> entityManager )
{
    m_entityManager = entityManager;
}
