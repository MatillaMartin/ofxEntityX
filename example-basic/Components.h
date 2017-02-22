#pragma once

#include "ofxEntityX.h"

// these components could easily be substituted by ofVec2f, but are used for clarity in the example

struct PositionComponent {
	PositionComponent(float x = 0.0f, float y = 0.0f) : x(x), y(y) {}

	float x, y;

	float distance(const PositionComponent & other)
	{
		float vx = x - other.x;
		float vy = y - other.y;
		return (float)sqrt(vx*vx + vy*vy);
	}
};

struct DirectionComponent {
	DirectionComponent(float x = 0.0f, float y = 0.0f) : x(x), y(y) {}

	float x, y;
};

struct CircleComponent {
	CircleComponent(float radius) : radius(radius) {}

	float radius;
};


struct GravityComponent {
	// no need to set gravity value here, it is handled in the system as it is a global value
};

struct CollisionComponent {
	CollisionComponent(entityx::Entity left, entityx::Entity right) : left(left), right(right) {}

	entityx::Entity left, right;
};

struct RenderComponent {
	RenderComponent(ofColor color) : color(color) {}

	ofColor color;
};