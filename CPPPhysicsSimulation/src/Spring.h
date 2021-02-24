#pragma once
#include "PhysicsObject.h"

class Rigidbody;

class Spring :
	public PhysicsObject
{
public:
	/// <summary>
	/// do this please ty
	/// </summary>
	Spring(Rigidbody* body1, Rigidbody* body2, float restLength, float springCoefficient, float damping = 0.1f, glm::vec2 contact1 = glm::vec2(0, 0), glm::vec2 contact2 = glm::vec2(0, 0));
	
	/// <inheritdoc/>
	void fixedUpdate(glm::vec2 gravity, float timeStep) override;
	void draw() override;
protected:
	Rigidbody* m_body1;
	Rigidbody* m_body2;

	glm::vec2 m_contact1;
	glm::vec2 m_contact2;

	float m_damping;
	float m_restLength;
	float m_springCoefficient;
};

