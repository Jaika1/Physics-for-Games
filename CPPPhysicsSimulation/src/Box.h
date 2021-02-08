#pragma once
#include "RigidBody.h"

/// <summary>
/// A 2D box (or square) that can interract with other objects.
/// </summary>
class Box :
	public Rigidbody
{
public:
	/// <summary>
	/// The width and height of this box.
	/// </summary>
	glm::vec2 Dimensions;
};

