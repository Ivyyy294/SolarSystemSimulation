#pragma once

#include <IvyyyGameObject.h>
#include "CelestialObjectDefinition.h"

using namespace Ivyyy;

template <int N>
class CelestialObjectManager :
    public GameObject
{
//Variables
public:
	CelestialObjectDefinition <N> m_celestialObjectData;
	GameObject* m_celestialObjects [N];
//Methods
public:
	inline int Size(){return N;}
};

