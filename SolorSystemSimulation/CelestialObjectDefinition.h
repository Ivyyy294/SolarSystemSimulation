#pragma once
#include "CelestialObjectAppearance.h"
#include "OrbitalElement.h"

template <int N>
struct CelestialObjectDefinition
{
	//Variables
	OrbitalElement<N> orbitalElement;
	CelestialObjectAppearance<N> appearance;
	int parentIndex [N];
	float mass[N];
};
