#pragma once

#include <IvyyyQuaternion.h>

template<int N>
struct KeplerianOrbitData
{
	float m_n[N];
	float m_t[N];
	Quaternion m_orientation[N];
};
