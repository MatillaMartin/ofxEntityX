#pragma once

#include "ofxEntityX.h"
#include <string>

#include "Components.h"
#include "Systems.h"

class Level : public ofxEntityX {
public:
	struct LevelInfo
	{
		LevelInfo(	unsigned int nFly, 
					unsigned int nGravity, 
					unsigned int particleMinSize, 
					unsigned int particleMaxSize, 
					bool bCollide)
			:
			nFly(nFly),
			nGravity(nGravity),
			particleMinSize(particleMinSize),
			particleMaxSize(particleMaxSize),
			bCollide(bCollide)
		{}
		unsigned int nFly;
		unsigned int nGravity;
		unsigned int particleMinSize;
		unsigned int particleMaxSize;
		bool bCollide;
	};
	

	explicit Level(LevelInfo info)
	{
		systems.add<CollisionSystem>();
		systems.add<BoundsSystem>();
		systems.add<MovementSystem>();
		systems.add<DebugSystem>();
		systems.configure();

		for (unsigned int i = 0; i < info.nFly; i++)
		{
			entityx::Entity entity = entities.create();
			entity.assign<PositionComponent>(rand() % 500, rand() % 500);
			entity.assign<DirectionComponent>((rand() % 1000) - 500, (rand() % 1000) - 500);
			entity.assign<CircleComponent>(info.particleMinSize + rand() % info.particleMaxSize);
			entity.assign<RenderComponent>(ofColor(rand() % 255, rand() % 255, rand() % 255));
		}

		for (unsigned int i = 0; i < info.nGravity; i++)
		{
			entityx::Entity entity = entities.create();
			entity.assign<PositionComponent>(rand() % 1000, rand() % 1000);
			entity.assign<DirectionComponent>((rand() % 100) - 50, 0);
			entity.assign<CircleComponent>(info.particleMinSize + rand() % info.particleMaxSize);
			entity.assign<GravityComponent>();
			entity.assign<RenderComponent>(ofColor(rand() % 255, rand() % 255, rand() % 255));
		}

		systems.system<CollisionSystem>()->bCollide = info.bCollide;
	}

	void update(TimeDelta dt) {
		// order is quite important
		systems.update<CollisionSystem>(dt);
		systems.update<BoundsSystem>(dt);
		systems.update<MovementSystem>(dt);
		systems.update<DebugSystem>(dt);
	}

	void render()
	{
		for(auto entity : entities.entities_with_components<PositionComponent, CircleComponent, RenderComponent>())
		{
			ofColor color = entity.component<RenderComponent>()->color;
			float radius = entity.component<CircleComponent>()->radius;
			ofVec2f position (entity.component<PositionComponent>()->x, entity.component<PositionComponent>()->y);

			ofSetColor(color);
			ofDrawCircle(position, radius);
		}
	}

	void onWindowResize(unsigned int width, unsigned int height)
	{
		systems.system<BoundsSystem>()->setBounds(width, height);
	}
};