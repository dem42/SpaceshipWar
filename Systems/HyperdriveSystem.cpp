#include "Systems/HyperdriveSystem.h"

#include "Game/Constants.h"
#include "Game/RandomnessSource.h"

HyperdriveSystem::HyperdriveSystem(const std::shared_ptr<RandomnessSource>& rand) : rand(rand)
{
}

void HyperdriveSystem::hyperdriveJump(PlayerComponent& player, Scene& scene)
{
	player.hyperdriveReady = false;
	player.hyperdriveActivated = false;

	float newX = rand->sampleRandomScreenXPos();
	float newY = rand->sampleRandomScreenYPos();
	auto& position = scene.positions.getComponent(player.getEntity());
	position.x = newX;
	position.y = newY;
}

void HyperdriveSystem::update(float dt, Scene& scene)
{
	for (auto& player : scene.players) {

		if (player.hyperdriveActivated) {
			hyperdriveJump(player, scene);
		}
		else {
			player.hyperdriveCharge += dt;
			auto& textUi = scene.textViews.getComponent(*scene.hyperdriveUiEntity);

			if (player.hyperdriveReady || player.hyperdriveCharge >= SpaceWarConstants::HYPERDRIVE_TIMER) {
				player.hyperdriveCharge = 0.f;
				player.hyperdriveReady = true;
				textUi.text = SpaceWarConstants::HYPERDRIVE_LABEL + "100%";
			}
			else {
				player.hyperdriveReady = false;
				textUi.text = SpaceWarConstants::HYPERDRIVE_LABEL + std::to_string(static_cast<int>(100 * player.hyperdriveCharge / SpaceWarConstants::HYPERDRIVE_TIMER)) + "%";
			}
		}
	}

}
