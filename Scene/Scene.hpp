#ifndef SCENE_H
#define SCENE_H

#include "../utility/stdshared.hpp"

#include <memory>

class Scene
{
protected:
	renderObject background;
	std::shared_ptr<sf::RenderWindow> parentWindow;

	void initializeBackground();
	virtual sceneID eventLoop() = 0;
public:
	explicit Scene(const std::shared_ptr<sf::RenderWindow> &wnd);

	// Used to make scene specific restoring actions
	// switchScene should return when scene is Closed
	// Value returned is scene that should be switched next
	// If sceneID::none is returned application closes
	virtual sceneID switchScene() = 0;
};

#endif // SCENE_H
