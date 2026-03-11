#pragma once

template <int N>
struct OrbitalElement
{
	//Variables
	//Semi major axis
	float m_a[N];

	//Eccentricity
	float m_e[N];

	//Inclination
	float m_i[N];

	//Longitude of ascending node
	float m_o[N];

	//Argument of periapsis
	float m_w[N];

	//Mean anomaly at epoch
	float m_m0[N];

	//Methods
	public:
	void Set (const int index, const float a, const float e, const float i, const float o, const float w, const float m0)
	{
		m_a[index] = a;
		m_e[index] = e;
		m_i[index] = i;
		m_o[index] = o;
		m_w[index] = w;
		m_m0[index] = m0;
	}
};
