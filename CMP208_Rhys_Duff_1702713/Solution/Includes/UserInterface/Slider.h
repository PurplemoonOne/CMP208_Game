#include "UIButton.h"


class Slider : public UIButton
{
protected:

	// @brief Constructs a slider object.
	// @param[in] Text to be displayed.
	// @param[in] Position to be on screen.
	Slider(std::string text, gef::Vector4 position);

public:

	// @brief Returns a new heap allocated Slider.
	// @param[in] Text to be displayed.
	// @param[in] Position to be on screen.
	static Slider* Create( std::string text, gef::Vector4 position);

	~Slider();

	// @brief Update the objects attributes.
	// @param[in] Time since last frame.
	void Update(float delta_time) override;

	// @brief Updates the volume bars position.
	// @param[in] Reference to the mouse data struct.
	// @param[in] Value passed by the d-pad. (If controller input is active)
	void UpdatePosition(const MouseData& mouse_data, float d_pad_input);

	// @brief Set the texture for the bar backdrop.
	// @param[in] Takes a const pointer to a texture.
	void SetBarBackdrop(const gef::Texture* texture);

	// @brief Set the volume graphics for this bar.
	// @param[in] Takes a pointer to a texture object.
	void SetBarVolumeTexture(const gef::Texture* texture);

	// @brief Renders this volume bar.
	// @param[in] Pointer to the sprite renderer.
	virtual void Render(gef::SpriteRenderer* sprite_renderer) override;

	// @brief Get the minimum bar for volume.
	inline const float& MinVolume() { return min_volume; }
	// @brief Get the maximum volume for this bar.
	inline const float& MaxVolume() { return max_volume; }
	// @brief Maximum x-position.
	inline const float& MaxPosition() { return max_value; }
	// @brief Minimum x-position.
	inline const float& MinPosition() { return min_value; }

	// @brief Get the value for this volume bar.
	inline const float& Percentage() { return percentage_value; }

	gef::Sprite& BackBarGraphics() { return bar_backdrop; }

private:

	//Sldier attributes.

	void CalculateBackBarAnchors();

	//Min - Max volume values
	float min_volume;
	float max_volume;

	//Min - Max positional values
	float min_value;
	float max_value;

	//Volume value.
	float percentage_value;

	//Represents the bar backdrop.
	gef::Sprite bar_backdrop;
	gef::Sprite bar_volume;

	// @brief Update the scale of the volume bar.
	void UpdateVolumeBar();

	AnchorData backdrop_anchor_data;
};