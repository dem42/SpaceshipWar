#include "Game/InputManager.h"

#include <SDL.h>
#include <iostream>
#include <algorithm>

#include "Game/Scene.h"
#include "Game/Constants.h"
#include "Components/PlayerComponent.h"

void InputManager::update(Scene& scene)
{
	using namespace std;

	auto pos = std::find_if(scene.players.begin(), scene.players.end(), [](auto& entityComponent) {
		return entityComponent.playerName == SpaceWarConstants::PLAYER_1_ID;
	});
	PlayerComponent& player1Input = (*pos);

	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {

		case SDL_QUIT:
			closeRequested = true;
			break;

		case SDL_MOUSEBUTTONDOWN:			
			if (event.button.button == SDL_BUTTON_LEFT) {
				cout << "Start Shooting" << endl;
				player1Input.holdingLeftMouse = true;
			} else if (event.button.button == SDL_BUTTON_RIGHT) {
				cout << "Use warp drive" << endl;
				player1Input.pressedRightMouse = true;				
			}

			break;

		case SDL_MOUSEBUTTONUP:
			if (event.button.button == SDL_BUTTON_LEFT) {
				player1Input.holdingLeftMouse = false;
				//player1Input.timeUntilNextShotCanBeFired = 0.f;
			}
			break;

		case SDL_MOUSEMOTION:
			player1Input.hasStreeringInput = true;
			player1Input.lastMouseX = static_cast<float>(event.motion.x);
			player1Input.lastMouseY = static_cast<float>(event.motion.y);
			break;			

		case SDL_KEYDOWN:
			// keyboard API for key pressed 
			switch (event.key.keysym.scancode) {
			case SDL_SCANCODE_RETURN:
				break;
			}
		}
	}
}

bool InputManager::isCloseRequested() const
{
	return closeRequested;
}
