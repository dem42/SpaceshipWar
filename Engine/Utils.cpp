#include "Engine/Utils.h"

#include <algorithm>
#include "Game/Constants.h"

float clamp(float x, float mini, float maxi)
{
	using namespace std;
	return min(maxi, max(mini, x));
}

float clampToScreenX(float x)
{
	return clamp(x, static_cast<float>(SpaceWarConstants::MARGIN_X), static_cast<float>(SpaceWarConstants::SCREEN_WIDTH - SpaceWarConstants::MARGIN_X));
}

float clampToScreenY(float y)
{
	return clamp(y, static_cast<float>(SpaceWarConstants::MARGIN_Y), static_cast<float>(SpaceWarConstants::SCREEN_HEIGHT - SpaceWarConstants::MARGIN_Y));
}
