#pragma once
#include "State.h"
#include "UserInterface/Slider.h"
#include "graphics/image_data.h"

class UIButton;

class Options : public State
{
public:

	Options(gef::Platform* platform);
	~Options();

	virtual void OnEnter() override;
	virtual void Input(float delta_time) override;
	virtual bool Update(float delta_time) override;
	virtual void Render() override;
	virtual void OnExit() override;

private:

	bool back;


	gef::ImageData image;
	std::vector<Slider*> sliders;
	UIButton* button;
};

