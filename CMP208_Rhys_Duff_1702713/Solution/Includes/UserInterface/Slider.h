#include "UIButton.h"


class Slider : public UIButton
{
protected:

	Slider(std::string text, gef::Vector4 position, float depth);

public:

	static Slider* Create( std::string text, gef::Vector4 position, float depth);

	~Slider();

	void Update(float delta_time) override;

	void UpdatePosition(const MouseData& mouse_data);

	//Special helper function to assign a texture to the backdrop.
	void SetBarBackdrop(const gef::Texture* texture);
	void SetBarVolumeTexture(const gef::Texture* texture);

	virtual void Render(gef::SpriteRenderer* sprite_renderer) override;

	inline const float& MinVolume() { return min_volume; }
	inline const float& MaxVolume() { return max_volume; }
	inline const float& MaxPosition() { return max_value; }
	inline const float& MinPosition() { return min_value; }

	inline const float& Percentage() { return percentage_value; }

private:

	float min_volume;
	float max_volume;

	// @brief Min - Max volume values
	float min_value;
	float max_value;

	float percentage_value;

	//Represents the bar backdrop.
	gef::Sprite bar_backdrop;
	gef::Sprite bar_volume;
	void UpdateVolumeBar();

	AnchorData bar_backdrop_anchor_data;
};