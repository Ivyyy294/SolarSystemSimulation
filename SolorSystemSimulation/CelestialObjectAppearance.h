#pragma once

#include <IvyyyColor.h>

using namespace Ivyyy;

template <int N>
struct CelestialObjectAppearance
{
	//Variables
	float m_radius[N];
	Color m_color[N];
	bool m_rings[N];

	//Methods
public:
	void Set (const int index, const float radius, const Color& color, const bool rings)
	{
		m_radius[index] = radius;
		m_color[index] = color;
		m_radius[index] = rings;
	}
};
