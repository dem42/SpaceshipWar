#include <iostream>
#include <vector>

#include "Components/ViewComponent.h"
#include "Components/PositionComponent.h"
#include "Components/PlayerInputComponent.h"

#include "Engine/Entity.h"

#include "Game/Scene.h"
#include "Game/Game.h"
#include "Game/Constants.h"

Scene createTestScene() 
{
	Scene scene1;

	auto e1 = scene1.createEntity("PlayerEntity"); 
	scene1.playerInputs.addComponent(e1, PlayerInputComponent{ e1, SpaceWarConstants::PLAYER_1_ID });
	scene1.positions.addComponent(e1, PositionComponent{ e1, 250, 250 });
	scene1.headings.addComponent(e1, HeadingComponent{ e1 });
	scene1.views.addComponent(e1, ViewComponent{ e1, TextureKey{"images/test.jpg"}, 500, 500 });

	return scene1;
}

int main(int argc, char *argv[])
{
	auto scene = createTestScene();
	Game spaceWarGame;
		
	bool close = false;
		
	while (!close) {
		close = spaceWarGame.update(scene);		
	}

	return 0;
}