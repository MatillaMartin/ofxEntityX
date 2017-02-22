#pragma once

#include "ofxEntityX.h"
#include "Components.h"
#include "ofLog.h"
#include "ofAppRunner.h"
#include "ofGraphics.h"

struct MovementSystem : public System<MovementSystem> {
	// system updates corresponding Movement component for all entities
	void update(entityx::EntityManager &es, entityx::EventManager &events, TimeDelta dt) override {
		es.each<DirectionComponent, GravityComponent>([dt](Entity entity, DirectionComponent &direction, GravityComponent &gravity) {
			direction.y += 100 * dt;
		});

		es.each<PositionComponent, DirectionComponent>([dt](Entity entity, PositionComponent &position, DirectionComponent &direction) {
			position.x += direction.x * dt;
			position.y += direction.y * dt;
		});
	};

};

class CollisionSystem : public System<CollisionSystem> {
public:
	// system updates corresponding Collision component for all entities
	void update(entityx::EntityManager &es, entityx::EventManager &events, TimeDelta dt) override {
		if (!bCollide) return;

		ComponentHandle<PositionComponent> left_position, right_position;
		ComponentHandle<DirectionComponent> left_direction, right_direction;
		ComponentHandle<CircleComponent> left_circle, right_circle;
		for (Entity left_entity : es.entities_with_components(left_position, left_direction, left_circle)) {
			for (Entity right_entity : es.entities_with_components(right_position, right_direction, right_circle)) {
				if(left_entity != right_entity)
				{
					if (collide(left_position, left_circle, right_position, right_circle)) {
						// emmit collision event
						events.emit<CollisionComponent>(left_entity, right_entity);

						// react to collision
						ofPoint left(left_position->x, left_position->y);
						ofPoint right(right_position->x, right_position->y);
						ofVec2f left_dir(left_direction->x, left_direction->y);
						ofVec2f right_dir(right_direction->x, right_direction->y);
						ofVec2f normal = left - right;
						normal.normalize();

						ofVec2f left_dir_new = -2 * (left_dir.dot(normal)) * normal + left_dir;
						left_direction->x = left_dir_new.x;
						left_direction->y = left_dir_new.y;

						// the right entity will be modified when the iteration finds it on the left
						// this is NOT the best way to check collisions.. but it works.. head on collisions work, back collisions are weird.. but its just an example
					}
				}
			}
		}
	};

	// implement System logic
	bool collide(	ComponentHandle<PositionComponent> & leftPos, ComponentHandle<CircleComponent> & leftCircle, 
					ComponentHandle<PositionComponent> & rightPos, ComponentHandle<CircleComponent> & rightCircle)
	{
		float dist = ABS(leftPos->distance(*rightPos.get()));
		return (dist < leftCircle->radius + rightCircle->radius); // simple radius distance check
	}

	bool bCollide = false;
};

struct DebugSystem : public System<DebugSystem>, public Receiver<DebugSystem> {
	// subscribe to collision component events
	void configure(entityx::EventManager &event_manager) {
		event_manager.subscribe<CollisionComponent>(*this);
	}

	void update(entityx::EntityManager &entities, entityx::EventManager &events, TimeDelta dt) {}

	void receive(const CollisionComponent &collision) {
		//ofLogNotice("DebugSystem") << "entities collided: " << collision.left << " and " << collision.right << endl;
	}
};

struct BoundsSystem : public System<BoundsSystem>
{
public:
	// system updates corresponding Movement component for all entities
	void update(entityx::EntityManager &es, entityx::EventManager &events, TimeDelta dt) override {
		es.each<PositionComponent, DirectionComponent, CircleComponent>([dt, this](Entity entity, PositionComponent &position, DirectionComponent &direction, CircleComponent & circle) {
			if (!ofInRange(position.x + direction.x * dt + circle.radius*ofSign(direction.x), 0, m_width))
			{
				direction.x = -direction.x;
			}

			if (!ofInRange(position.y + direction.y * dt + circle.radius*ofSign(direction.y), 0, m_height))
			{
				direction.y = -direction.y;
			}
			
		});
	};

	void setBounds(float width, float height)
	{
		m_width = width;
		m_height = height;
	}

	float m_width;
	float m_height;
};