#pragma once
#include "State.h"
#include "UserInterface/Slider.h"
#include "graphics/image_data.h"

class UIButton;

class Options : public State
{
public:

	Options();
	~Options();

	virtual void OnEnter() override;
	virtual void Input(float delta_time) override;
	virtual bool Update(float delta_time) override;
	virtual void Render() override;
	virtual void OnExit() override;

private:

	std::vector<UIButton*> buttons;
	gef::ImageData image;

};

