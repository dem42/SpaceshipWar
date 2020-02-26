#pragma once

#include <string>

#include "Engine/Component.h"

class TextUiViewComponent : public Component {
public:
	TextUiViewComponent(const std::shared_ptr<Entity>& entity, const std::string& text, bool visible)
		: Component(ComponentType::TEXT_UI_VIEW, entity), text(text), visible(visible)
	{
	}

	std::string text;
	bool visible;	
};
