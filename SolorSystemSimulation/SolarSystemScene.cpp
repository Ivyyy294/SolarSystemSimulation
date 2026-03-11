#include <IvyyyMeshRenderer.h>
#include <IvyyyCamera.h>

#include "SolarSystemScene.h"
#include "CelestialObjectDefinition.h"
#include "CelestialObjectManager.h"
#include "ColorMaterial.h"

void SolarSystemScene::Init()
{
	IvyyyPhysic::SetGravitationalConstant (6.67430e-11);

	//Add Light
	auto light = AddGameObject<GameObject>()->AddComponent<DirectionalLight>();
	light->GetTransform()->SetParent(Camera::MainCamera()->GetTransform());
	light->SetColor(Color(1.f, 1.f, 1.f, 0.5f));

	InitCelestialObjectManager();
	SpawnCelestialObjects();
}

void SolarSystemScene::InitCelestialObjectManager()
{
	m_manager = AddGameObject()->AddComponent<CelestialObjectManager<11 >>().get();
	m_manager->SetGravScale(1e-20);
	m_manager->SetSizeScale(1.f);
	m_manager->SetDistanceScale(4.f);

	//Sun
	m_manager->m_celestialObjectData.m_appearance.Set(0, 0.3f, Color::Yellow, false);
	m_manager->m_celestialObjectData.m_parentIndex[0] = -1;
	m_manager->m_celestialObjectData.m_mass[0] = 1.988475e30;

	//Mercury
	m_manager->m_celestialObjectData.m_appearance.Set(1, 0.1f, { 1.f, 0.5f, 0.f, 1.0f }, false);
	m_manager->m_celestialObjectData.m_orbitalElement.Set(1, 0.387098f, 0.205630f, 6.35f, 48.331f, 29.124f, 174.796f);
	m_manager->m_celestialObjectData.m_parentIndex[1] = 0;
	m_manager->m_celestialObjectData.m_mass[1] = 3.301e23;

	//Venus
	m_manager->m_celestialObjectData.m_appearance.Set(2, 0.15f, { 1.f, 0.83f, 0.57f, 1.0f }, false);
	m_manager->m_celestialObjectData.m_orbitalElement.Set(2, 0.723332f, 0.006772f, 2.15f, 76.680f, 54.884f, 50.115f);
	m_manager->m_celestialObjectData.m_parentIndex[2] = 0;
	m_manager->m_celestialObjectData.m_mass[2] = 4.867e24;

	//Earth
	m_manager->m_celestialObjectData.m_appearance.Set(3, 0.15f, Color::Blue, false);
	m_manager->m_celestialObjectData.m_orbitalElement.Set(3, 1.000003f, 0.0167086f, 0.00005f, -11.26064f, 114.20783f, 358.617f);
	m_manager->m_celestialObjectData.m_parentIndex[3] = 0;
	m_manager->m_celestialObjectData.m_mass[3] = 5.972e24;
}

void SolarSystemScene::SpawnCelestialObjects()
{
	for (int i = 0; i < m_manager->Size(); ++i)
	{
		GameObject* celestialObject = AddGameObject();

		auto renderer = celestialObject->AddComponent<MeshRenderer>();
		renderer->SetMesh(Mesh::Sphere(16, 16));
		auto mat = std::make_shared<ColorMaterial>();
		mat->SetColor(m_manager->m_celestialObjectData.m_appearance.m_color[i]);
		renderer->SetMaterial(mat);
		
		m_manager->m_celestialObjects[i] = celestialObject;
	}
}

