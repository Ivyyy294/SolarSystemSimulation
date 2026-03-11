#pragma once
#include "CelestialObjectAppearance.h"
#include "OrbitalElement.h"

template <int N>
struct CelestialObjectDefinition
{
	//Variables
	OrbitalElement<N> m_orbitalElement;
	CelestialObjectAppearance<N> m_appearance;
	int m_parentIndex [N];
	float m_mass[N];
};
