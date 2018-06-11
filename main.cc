#include "SceneManager/SceneManager.hpp"
#include "Tests/TestUnit.hpp"

int main(void)
{
	TestUnit tu;
	tu.crashTestLevelClass();

	TextureManager tm; // ctor loads textures to memory
	SceneManager sm;
	sm.run();


	return 0;
}

