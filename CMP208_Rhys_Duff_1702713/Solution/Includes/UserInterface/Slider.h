#include "UIButton.h"


class Slider : public UIButton
{
protected:

	Slider(std::string text, gef::Vector2 position);

public:

	static Slider* Create( std::string text, gef::Vector2 position);

	~Slider();

	void Update(float delta_time) override;

	//Special helper function to assign a texture to the backdrop.
	void SetBarBackdrop(const gef::Texture* texture);

private:

	// @brief Min - Max volume values
	float min_value;
	float max_value;

	//Represents the bar backdrop.
	gef::Sprite bar_backdrop;

};