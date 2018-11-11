#include "Scene.h"

Scene::Scene() {
	planets.reserve(PLANET_COUNT * 3);
	for (int i = 0; i < PLANET_COUNT * 3; i+=3) {
		planets.push_back(new Planet(MESHES.get_Sphere_textured_red(), (i + 1) * ORBIT_SPACING));
		planets.push_back(new Planet(MESHES.get_Sphere_textured_green(), (i + 2) * ORBIT_SPACING));
		planets.push_back(new Planet(MESHES.get_Sphere_textured_blue(), (i + 3) * ORBIT_SPACING));
	}
	clouds.reserve(CLOUD_COUNT);
	for (int i = 0; i < CLOUD_COUNT; i++) {
		clouds.push_back(new Cloud(MESHES.get_Sphere_alpha_blue()));
	}
	starfield = new Skybox(MESHES.get_Sphere_black(), MESHES.get_Sphere_points_white());
	centralStar = new Star(MESHES.get_Sphere_white());
	distantStar = new DistantStar(MESHES.get_Circle_yellow_gradient());
	ringSystem = new RingSystem(MESHES.get_Ring_rainbow());
	spaceship = new Spaceship(MESHES.get_Spaceship());
}

Scene::~Scene() {/*
	for (Planet* planet : planets) {
		delete planet;
	}
	for (Cloud* cloud : clouds) {
		delete cloud;
	}
	delete starfield;
	delete centralStar;
	delete distantStar;
	delete ringSystem;
	delete spaceship;*/
}

void Scene::performInitialRender(Renderer& renderer) {
	starfield->performInitialRender(renderer);
	distantStar->performInitialRender(renderer);
	spaceship->performInitialRender(renderer);
	ringSystem->performInitialRender(renderer);
	centralStar->performInitialRender(renderer);
	
	for (Planet* planet : planets) {
		planet->performInitialRender(renderer);
	}
	for (Cloud* cloud : clouds) {
		cloud->performInitialRender(renderer);
	}
	
}

void Scene::update(float delta) {
	for (Planet* planet : planets) {
		planet->update(delta);
	}
	if (planets.size() > 0) {
		ringSystem->setNewLocation(planets.at(0)->getXPos(), planets.at(0)->getZPos());
		ringSystem->update(delta);
	}
}

void Scene::render(Renderer& renderer) {
	for (Planet* planet : planets) {
		planet->render(renderer);
	}
	ringSystem->render(renderer);
}