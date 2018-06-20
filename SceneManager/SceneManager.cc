#include "SceneManager.hpp"

#include "../Scene/MainScene/MainScene.hpp"
#include "../Scene/GameScene/GameScene.hpp"
#include "../Scene/CreditsScene/CreditsScene.hpp"

SceneManager::SceneManager()
: mainWindow()
{
	puts("Creating scene manager");
	this->mainWindow =
		std::make_unique<sf::RenderWindow>
		(sf::VideoMode(1280,720),
		 "Torch", sf::Style::Close);
	this->mainWindow->setFramerateLimit(60);

	this->registerScene<MainScene>();
	this->registerScene<GameScene>();
	this->registerScene<CreditsScene>();

	this->currentScene = sceneID::mainmenu;
}

void SceneManager::switchScene(sceneID scene)
{
	if(this->scenes.size() == 0)
		return;

	sceneID scenecopy = this->currentScene;
	try
	{
		this->currentScene = scene;
		this->scenes.at(scene)->switchScene();
	}
	catch(const std::out_of_range &ex)
	{
		printf("Error - cannot switch to scene with id: %i.\n",scene);
		this->currentScene = scenecopy;
	}
}

template<typename T>
void SceneManager::registerScene()
{
	static bool exists = 0;

	if(exists)
	{
		printf("Cannot create Scene.\n%s already exists.\n",
				__PRETTY_FUNCTION__);
		return;
	}

	this->scenes.push_back(
			std::make_unique<T>(this->mainWindow));
	exists = true;
}

void SceneManager::run()
{
	sceneID nextScene;
	while(this->currentScene != sceneID::none)
	{
		nextScene = this->scenes[this->currentScene]->switchScene();
		this->currentScene = nextScene;
	}
}


