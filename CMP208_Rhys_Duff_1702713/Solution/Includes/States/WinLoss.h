#pragma once
#include "State.h"
/*..Graphics..*/
#include "graphics/sprite.h"
#include "graphics/image_data.h"

/*..Assests..*/
#include "assets/png_loader.h"

class PawnController;
class UIButton;

// @brief Initial screen displayed on start up.
class WinLoseScreen : public State
{
public:

	WinLoseScreen(gef::Platform* platform_);
	~WinLoseScreen();

	virtual void OnEnter() override;
	virtual void Input(float delta_time) override;
	virtual bool Update(float delta_time) override;
	virtual void Render() override;
	virtual void OnExit() override;

	inline void GetFinalScore(const int& score) { final_score = score; }

private:

	void UpdateDisplay(float delta_time);
	void EvalButtons();
	void RenderButtons(gef::SpriteRenderer* sprite_renderer);

	void LoadBackdrop();
	void UpdateSprites();
	void RenderSprites(gef::SpriteRenderer* sprite_renderer);
	void RenderText();

	std::array<UIButton*, 2> buttons;
	std::array<gef::Sprite*, 3> sprites;

	gef::Font* final_score_text;
	int final_score;

	bool game_state;
	bool exit;

	float session_clock;
};
