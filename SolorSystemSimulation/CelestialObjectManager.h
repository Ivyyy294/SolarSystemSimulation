#pragma once
#include <cmath>
#include<IvyyyMathF.h>
#include <IvyyyPhysic.h>
#include <IvyyyComponent.h>
#include <IvyyyTime.h>
#include "CelestialObjectDefinition.h"
#include "KeplerianOrbitData.h"

using namespace Ivyyy;

template <int N>
class CelestialObjectManager :
    public Component
{
//Variables
public:
	CelestialObjectDefinition <N> m_celestialObjectData;
	GameObject* m_celestialObjects [N];
	float m_timer = 0.f;

private:
	KeplerianOrbitData <N> m_keplarianOrbitData;
	float m_gravScale = 1.f;
	float m_sizeScale = 1.f;
	float m_distanceScale = 1.f;
//Methods
public:
	inline int Size(){return N;}

	inline void SetGravScale (float scale) {m_gravScale = scale;}
	inline void SetSizeScale (float scale) {m_sizeScale = scale;}
	inline void SetDistanceScale (float scale) {m_distanceScale = scale;}

	void Start() override
	{
		CallculateKeplarianOrbitData();
	}

	void Update() override
	{
		UpdateOrbitalPosition();
		m_timer += Time::DeltaTime();
	}

private:

	void CallculateKeplarianOrbitData()
	{
		for (int i = 0; i < N; ++i)
		{
			const int parentIndex = m_celestialObjectData.m_parentIndex[i];

			if (parentIndex < 0)
				continue;

			Quaternion q_o = Quaternion::AroundAxis(Vector3::Forward, m_celestialObjectData.m_orbitalElement.m_o[i] * MathF::Deg2Rad);
			Quaternion q_i = Quaternion::AroundAxis(Vector3::Up, m_celestialObjectData.m_orbitalElement.m_i[i] * MathF::Deg2Rad);
			Quaternion q_w = Quaternion::AroundAxis(Vector3::Forward, m_celestialObjectData.m_orbitalElement.m_w[i] * MathF::Deg2Rad);

			m_keplarianOrbitData.m_orientation[i] = (q_o * q_i * q_w);

			float parentMass = m_celestialObjectData.m_mass[parentIndex];
			float gm = IvyyyPhysic::GravitationalConstant() * (parentMass * m_gravScale);
			float a = m_celestialObjectData.m_orbitalElement.m_a[i];
			m_keplarianOrbitData.m_n[i] = std::sqrtf (gm / (a * a * a));
			m_keplarianOrbitData.m_t[i] = 2.f * float(M_PI) / m_keplarianOrbitData.m_n[i];
		}
	};

	void UpdateOrbitalPosition()
	{
		for (int i = 0; i < N; ++i)
		{
			//Adjust scale
			float scale = m_celestialObjectData.m_appearance.m_radius[i] * m_sizeScale;
			m_celestialObjects[i]->transform.SetLocalScale({ scale, scale, scale });

			const int parentIndex = m_celestialObjectData.m_parentIndex[i];

			if (parentIndex < 0)
				continue;

			const Vector3 parentPos = m_celestialObjects[parentIndex]->transform.GetPosition();

			float eccentricAnomaly = CalculateEccentricAnomaly(m_celestialObjectData.m_orbitalElement.m_m0[i], m_celestialObjectData.m_orbitalElement.m_e[i]
			, m_keplarianOrbitData.m_n[i], m_timer);

			Vector3 newPos = parentPos + CalculateOrbitalPositionAtTime(m_celestialObjectData.m_orbitalElement.m_a[i]
			, m_celestialObjectData.m_orbitalElement.m_e[i], m_keplarianOrbitData.m_orientation[i], eccentricAnomaly);

			m_celestialObjects[i]->transform.SetPosition(newPos);
		}
	}

	Vector3 CalculateOrbitalPositionAtTime(const float majorAxis, const float eccentricity, const Quaternion& orientation, const float eccentricAnomaly)
	{
		Vector3 orbitalPosition(
			majorAxis * (std::cos(eccentricAnomaly) - eccentricity),
			majorAxis * std::sqrt(1.0f - eccentricity * eccentricity) * std::sin(eccentricAnomaly),
			0.0f
		);

		Vector3 pos = orientation * orbitalPosition;

		return pos * m_distanceScale;
	}

	float CalculateEccentricAnomaly(const float meanAnomalyAtEpoch, const float eccentricity, const float meanMotion, float time)
	{
		float M = (meanAnomalyAtEpoch * MathF::Deg2Rad) + meanMotion * time;

		// Wrap into [0, 2?]
		M = std::fmod(M, 2.0f * float(M_PI));
		if (M < 0.0f)
			M += 2.0f * float(M_PI);

		// --- 2. Solve Kepler's equation E - e*sin(E) = M ---
		float E = M; // initial guess
		const float e = eccentricity;

		for (int iter = 0; iter < 10; ++iter)
		{
			float f = E - e * std::sin(E) - M;
			float fp = 1.0f - e * std::cos(E);
			E -= f / fp;
		}

		// Wrap E into [0, 2?]
		E = std::fmod(E, 2.0f * float(M_PI));
		if (E < 0.0f)
			E += 2.0f * float(M_PI);

		return E;
	}
};

