#pragma once

#include "RE/H/hkpCollisionEvent.h"
#include "RE/h/hkpRigidBody.h"

namespace RE
{
	class hkContactPoint;
	class hkpContactPointProperties;
	class hkpVelocityAccumulator;

	using hkpShapeKey = std::uint32_t;

	struct hkpContactPointEvent : public hkpCollisionEvent
	{
	public:
		enum class Type
		{
			kTOI,
			kExpandManifold,
			kManifold,

			kManifoldAtEndOfStep,
			kManifoldFromSavedContactPoint
		};

		inline hkpShapeKey* GetShapeKeys(int a_bodyIdx) const
		{
			if (a_bodyIdx == 0 || a_bodyIdx == 1) {
				if (bodies[a_bodyIdx]->numShapeKeysInContactPointProperties > 0) {
					return shapeKeyStorage + (a_bodyIdx * bodies[0]->numShapeKeysInContactPointProperties);
				}
			}
			return nullptr;
		}

		// members
		Type                       type;
		hkContactPoint*            contactPoint;
		hkpContactPointProperties* contactPointProperties;
		bool                       firingCallbacksForFullManifold;
		bool                       firstCallbackForFullManifold;
		bool                       lastCallbackForFullManifold;
		float*                     separatingVelocity;
		float*                     rotateNormal;
		hkpShapeKey*               shapeKeyStorage;
		hkpVelocityAccumulator*    accumulators[2];
	};
	static_assert(sizeof(hkpContactPointEvent) == 0x68);
}
