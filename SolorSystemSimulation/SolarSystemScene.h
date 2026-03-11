#pragma once
#include <IvyyyScene.h>
#include "CelestialObjectManager.h"

using namespace Ivyyy;


class SolarSystemScene :
    public Scene
{
//Variables
private:
	CelestialObjectManager<11>* m_manager;
//Methods
private:
	void Init() override;

	void InitCelestialObjectManager ();
	void SpawnCelestialObjects();
};

