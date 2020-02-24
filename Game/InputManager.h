#pragma once

class Scene;

class InputManager {
public:
	void update(Scene& scene);
	bool isCloseRequested() const;
private:
	bool closeRequested = false;
};
