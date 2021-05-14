#pragma once
#include "State.h"
#include "UserInterface/Slider.h"
#include "graphics/image_data.h"

class UIButton;
class ParallaxBackground;

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

	int& TilesToRender() { return tiles_to_render; }
	void CurrentTilesBeingRendered(int& value) { tiles_to_render = value; }

private:

	bool back;

	void UpdateVolume();
	void CleanSprites();
	void EvalButton();
	void InitSliders();
	void RenderFont();

	ParallaxBackground* parallax_bg;
	gef::ImageData image;

	//Volume options.
	std::vector<Slider*> sliders;
	std::array<gef::Font*, 3> option_text;

	//Tiling options.
	void InitTileOptions();
	void EvalArrowButtons(const int index);
	void RenderTilesFont();
	void IncrimentTiles(const int& index);
	void UpdateDpadTextures(const int& index);
	std::array<UIButton*, 2> tile_option_arrows;
	std::array<gef::Font*, 2> tiles_font;
	int tiles_to_render;
	bool tile_arrows_selected;


	float slider_values[3];
	bool not_exit;
	int index;
	UIButton* button;
};

