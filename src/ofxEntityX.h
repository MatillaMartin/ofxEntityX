#pragma once

#include "entityx/entityx.h"
#include "entityx/deps/Dependencies.h"

using entityx::Component;
using entityx::ComponentAddedEvent;
using entityx::ComponentHandle;
using entityx::ComponentRemovedEvent;
using entityx::Entity;
using entityx::EntityX;
using entityx::EntityCreatedEvent;
using entityx::EntityDestroyedEvent;
using entityx::EntityManager;
using entityx::Event;
using entityx::EventManager;
using entityx::Receiver;
using entityx::System;
using entityx::SystemManager;
using entityx::TimeDelta;

class ofxEntityX : public EntityX
{};