#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "../Scene/Scene.hpp"

#include "../utility/stdshared.hpp"

#include <vector>
#include <memory>

#include <stdio.h>

class SceneManager
{
private:
	sceneID currentScene;

	// Holds all available scenes
	std::vector<std::unique_ptr<Scene> > scenes;
	std::shared_ptr<sf::RenderWindow> mainWindow;

public:
	SceneManager();

	// Used from other scenes to switch to each other
	// argument is desired secene
	void switchScene(sceneID scene);

	template<typename T>
	void registerScene();

	// runs scene loop
	void run();
};

#endif // SCENEMANAGER_H
