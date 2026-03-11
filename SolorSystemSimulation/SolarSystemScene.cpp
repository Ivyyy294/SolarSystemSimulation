#include "SolarSystemScene.h"
#include "CelestialObjectDefinition.h"
void SolarSystemScene::Init()
{
	CelestialObjectDefinition <11> celestialObjects;

	//Sun
	celestialObjects.appearance.Set (0, 0.3f, Color::Yellow, false);
	celestialObjects.parentIndex[0] = -1;
	celestialObjects.mass[0] = 1.988475e30;

	//Mercury
	celestialObjects.appearance.Set(1, 0.1f, { 1.f, 0.5f, 0.f, 1.0f }, false);
	celestialObjects.orbitalElement.Set (1, 0.387098f, 0.205630f, 6.35f, 48.331f, 29.124f, 174.796f);
	celestialObjects.parentIndex[1] = 0;
	celestialObjects.mass[1] = 3.301e23;

	//Venus
	celestialObjects.appearance.Set(2, 0.15f, { 1.f, 0.83f, 0.57f, 1.0f }, false);
	celestialObjects.orbitalElement.Set(2, 0.723332f, 0.006772f, 2.15f, 76.680f, 54.884f, 50.115f);
	celestialObjects.parentIndex[2] = 0;
	celestialObjects.mass[2] = 4.867e24;

	//Earth
	celestialObjects.appearance.Set(3, 0.15f, Color::Blue, false);
	celestialObjects.orbitalElement.Set(3, 1.000003f, 0.0167086f, 0.00005f, -11.26064f, 114.20783f, 358.617f);
	celestialObjects.parentIndex[3] = 5.972e24;
}
