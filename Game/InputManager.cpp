#include "Game/InputManager.h"

#include <SDL.h>

#include "Game/Scene.h"
#include "Game/Constants.h"
#include "Components/PlayerComponent.h"

void InputManager::update(Scene& scene)
{
	PlayerComponent& player1Input = scene.players.getComponent(*scene.playerEntity);

	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {

		case SDL_QUIT:
			closeRequested = true;
			break;

		case SDL_MOUSEBUTTONDOWN:
			if (scene.getLevel() == 0) {
				continue;
			}
			if (event.button.button == SDL_BUTTON_LEFT) {				
				player1Input.holdingLeftMouse = true;
			} else if (event.button.button == SDL_BUTTON_RIGHT) {				
				player1Input.pressedRightMouse = true;				
			}

			break;

		case SDL_MOUSEBUTTONUP:
			if (event.button.button == SDL_BUTTON_LEFT) {
				player1Input.holdingLeftMouse = false;
			}
			break;

		case SDL_MOUSEMOTION:
			player1Input.hasStreeringInput = true;
			player1Input.lastMouseX = static_cast<float>(event.motion.x);
			player1Input.lastMouseY = static_cast<float>(event.motion.y);
			break;			

		case SDL_KEYDOWN:
			switch (event.key.keysym.scancode) {
			case SDL_SCANCODE_RETURN:
				player1Input.closeTutorial = true;
				break;
			}
		}
	}
}

bool InputManager::isCloseRequested() const
{
	return closeRequested;
}
