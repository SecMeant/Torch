#ifndef TEMPLATESCENE_H
#define TEMPLATESCENE_H

#include "../Scene.hpp"

#include "../../utility/complexTypes.hpp"

#include <SFML/Graphics.hpp>

#include <vector>
#include <memory>

class TEMPLATESCENE:public Scene
{
private:
	virtual sceneID eventLoop() override;

public:
	explicit TEMPLATESCENE(const std::shared_ptr<sf::RenderWindow> &wnd);

	virtual sceneID switchScene() override;
};

#endif // TEMPLATESCENE_H
