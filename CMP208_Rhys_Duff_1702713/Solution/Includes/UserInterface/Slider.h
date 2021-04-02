#include "UIButton.h"


class Slider : public UIButton
{
protected:

	Slider(std::string text, gef::Vector2 position);

public:

	static Slider* Create( std::string text, gef::Vector2 position);

	~Slider();

	void Update(float delta_time) override;

	void UpdatePosition(const MouseData& mouse_data);

	//Special helper function to assign a texture to the backdrop.
	void SetBarBackdrop(const gef::Texture* texture);

	virtual void Render(gef::SpriteRenderer* sprite_renderer) override;

private:


	// @brief Min - Max volume values
	float min_value;
	float max_value;

	//Represents the bar backdrop.
	gef::Sprite bar_backdrop;
	AnchorData bar_backdrop_anchor_data;
};