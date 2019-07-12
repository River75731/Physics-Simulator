#include "Model.h"

PhysicsSpace::PhysicsSpace() {
	m_StepSize = DEFAULT_STEPSIZE; /* 10ms */
	m_Force = originPoint;
}

void PhysicsSpace::addRigidBody(const RigidBody InputRigidBody) {
	if(m_RigidBodySet.size()<RB_MAXN) m_RigidBodySet.push_back(InputRigidBody);
	else printf("You cannot have more than %d rigid bodies.", RB_MAXN);
}

void PhysicsSpace::addRigidBody(const Poly &InputShape, const double &InputMass, const Vec &InputVelocity, const double &InputAngularVelocity) {
	m_RigidBodySet.push_back(RigidBody(InputShape, InputMass, InputVelocity, InputAngularVelocity));
}

void PhysicsSpace::deleteRigidBody(const int & InputId) {
	for (std::vector<RigidBody>::iterator i = m_RigidBodySet.begin(); i != m_RigidBodySet.end(); ) {
		if (i->getId() == InputId)
			i = m_RigidBodySet.erase(i);
		else
			i++;
	}
}

void PhysicsSpace::setStepSize(const double &dt) {
	m_StepSize = dt;
}

void PhysicsSpace::goStep(const int &n) {
	for (int i = 0; i < n; i++) {
		for (std::vector<RigidBody>::iterator i = m_RigidBodySet.begin(); i != m_RigidBodySet.end(); i++) {
			i->applyForce(m_Force);
			i->accelerate(m_StepSize);
			i->move(m_StepSize);
			i->rotate(m_StepSize);
		}
		/* Collision */
		for (std::vector<RigidBody>::iterator hsRB = m_RigidBodySet.begin(); hsRB != m_RigidBodySet.end(); hsRB++) {
			for (std::vector<RigidBody>::iterator inRB = m_RigidBodySet.begin(); inRB != m_RigidBodySet.end(); inRB++) {
				if (hsRB == inRB) continue;
				hsRB->collide(*inRB);
			}
		}
	}
}

void PhysicsSpace::addForceField(const Vec & InputForce) {
	m_Force += InputForce;
}

Vec PhysicsSpace::getForceField() {
	return m_Force;
}

std::vector<RigidBody> PhysicsSpace::getRigidBodys() {
	return m_RigidBodySet;
}