/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2017/07
----------------------------------------------*/
#ifndef __MYSOLVER_H_
#define __MYSOLVER_H_

#include "MyRigidBody.h"

#define REPULSIONFORCE .015f
namespace Simplex
{

	class MySolver
	{
		vector3 m_v3Acceleration = ZERO_V3; //Acceleration of the MySolver
		vector3 m_v3Position = ZERO_V3; //Position of the MySolver
		vector3 m_v3Size = vector3(1.0f); //Size of the MySolver
		vector3 m_v3Velocity = ZERO_V3; //Velocity of the MySolver
		quaternion m_qOrientation = quaternion(); //orientation of the MySolver
		float m_fMass = 1.0f; //Mass of the solver
		bool m_bIsCollding = false; //Is Solver colliding with any object?
	public:
		/*
		USAGE: Constructor
		ARGUMENTS: ---
		OUTPUT: object instance
		*/
		MySolver(void);
		/*
		USAGE: Copy Constructor
		ARGUMENTS: object to copy
		OUTPUT: object instance
		*/
		MySolver(MySolver const& other);
		/*
		USAGE: Copy Assignment Operator
		ARGUMENTS: object to copy
		OUTPUT: this instance
		*/
		MySolver& operator=(MySolver const& other);
		/*
		USAGE: Destructor
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		~MySolver(void);
		/*
		USAGE: Content Swap
		ARGUMENTS: object to swap content with
		OUTPUT: ---
		*/
		void Swap(MySolver& other);

		/*
		USAGE: Sets the value of m_bIsColliding
		ARGUMENTS: bool a_bIsColliding -> Sets the colliding value
		OUTPUT: ---
		*/
		void SetIsColliding(bool a_bIsColliding = true);

		/*
		USAGE: Sets the position of the solver
		ARGUMENTS: vector3 a_v3Position -> position to set
		OUTPUT: ---
		*/
		void SetPosition(vector3 a_v3Position);
		/*
		USAGE: Gets the position of the solver
		ARGUMENTS: ---
		OUTPUT: position of the solver
		*/
		vector3 GetPosition(void);

		/*
		USAGE: Sets the orientation of the solver
		ARGUMENTS: quaternion a_qOrientation -> orientation to set
		OUTPUT: ---
		*/
		void SetOrientation(quaternion a_qOrientation);
		/*
		USAGE: Gets the orientation of the solver
		ARGUMENTS: ---
		OUTPUT: orientation of the solver
		*/
		quaternion GetOrientation(void);

		/*
		USAGE: Sets the Size of the solver
		ARGUMENTS: vector3 a_v3Size -> position to set
		OUTPUT: ---
		*/
		void SetSize(vector3 a_v3Size);
		/*
		USAGE: Gets the size of the solver
		ARGUMENTS: ---
		OUTPUT: size of the solver
		*/
		vector3 GetSize(void);

		/*
		USAGE: Sets the velocity of the solver
		ARGUMENTS: vector3 a_v3Velocity -> velocity to set
		OUTPUT: ---
		*/
		void SetVelocity(vector3 a_v3Velocity);
		/*
		USAGE: Gets the velocity of the solver
		ARGUMENTS: ---
		OUTPUT: velocity of the solver
		*/
		vector3 GetVelocity(void);

		/*
		USAGE: Sets the mass of the solver
		ARGUMENTS: float a_fMass -> mass to set
		OUTPUT: ---
		*/
		void SetMass(float a_fMass);
		/*
		USAGE: Gets mass of the solver
		ARGUMENTS: ---
		OUTPUT: mass of the object
		*/
		float GetMass(void);

		/*
		USAGE: Applies friction to the movement
		ARGUMENTS: float a_fFriction = 0.1f -> friction to apply negative friction gets minimized to 0.01f
		OUTPUT: ---
		*/
		void ApplyFriction(float a_fFriction = 0.1f);
		/*
		USAGE: Applies a force to the solver
		ARGUMENTS: vector3 a_v3Force -> Force to apply
		OUTPUT: ---
		*/
		void ApplyForce(vector3 a_v3Force);
		/*
		USAGE: Updates the MySolver
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		void Update(void);
		/*
		USAGE: Resolve the collision between two solvers
		ARGUMENTS: MySolver* a_pOther -> other solver to resolve collision with
		OUTPUT: ---
		*/
		void ResolveCollision(MySolver* a_pOther);
	private:
		/*
		Usage: Deallocates member fields
		Arguments: ---
		Output: ---
		*/
		void Release(void);
		/*
		Usage: Allocates member fields
		Arguments: ---
		Output: ---
		*/
		void Init(void);
	};//class

} //namespace Simplex

#endif //__SOLVER_H_

  /*
  USAGE:
  ARGUMENTS: ---
  OUTPUT: ---
  */