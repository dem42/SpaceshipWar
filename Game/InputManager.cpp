#include "Game/InputManager.h"

#include <SDL.h>
#include <iostream>
#include <algorithm>

#include "Game/Scene.h"
#include "Game/Constants.h"
#include "Components/PlayerInputComponent.h"

void InputManager::update(Scene& scene)
{
	using namespace std;

	auto pos = std::find_if(scene.playerInputs.begin(), scene.playerInputs.end(), [](auto& entityComponent) {
		return entityComponent.second.playerName == SpaceWarConstants::PLAYER_1_ID;
	});
	PlayerInputComponent& player1Input = (*pos).second;

	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {

		case SDL_QUIT:
			cout << "Quit requested" << endl;
			closeRequested = true;
			break;

		case SDL_MOUSEBUTTONDOWN:
			cout << "Start Shooting" << endl;
			break;

		case SDL_MOUSEBUTTONUP:
			cout << "Stop Shooting" << endl;
			break;

		case SDL_MOUSEMOTION:
			//cout << "Steering changed (" << event.motion.x << ", " << event.motion.y << ")" << endl;
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
