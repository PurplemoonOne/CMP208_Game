#include "PawnController.h"

/*..gef input devices includes..*/
#include "input/input_manager.h"
#include "input/keyboard.h"
#include "input/sony_controller_input_manager.h"
#include "input/touch_input_manager.h"


PawnController::PawnController(gef::Platform* p_ptr, Pawn* p)
	: 
	platform_ptr(p_ptr),
	pawn(p),
	input_manager(nullptr),
	active_touch_id_(-1)
{

}

PawnController::~PawnController()
{
}

void PawnController::InitialiseInputManagers(gef::Platform& platform)
{
	/*..Create a new input manager..*/
	input_manager = gef::InputManager::Create(platform);

	/*..Create a new keyboard object..*/
	//KEYBOARD

	/*..Create a new sony entertainment controller manager..*/
	sce_in_manager = input_manager->controller_input();


	// make sure if there is a panel to detect touch input, then activate it
	if (input_manager && input_manager->touch_manager() && (input_manager->touch_manager()->max_num_panels() > 0))
		input_manager->touch_manager()->EnablePanel(0);

}

void PawnController::ControllerHandler()
{
		const gef::SonyController* sce_controller = sce_in_manager->GetController(0);
	
		

		if (sce_controller)
		{
				switch (sce_controller->buttons_pressed())
				{
					case gef_SONY_CTRL_OPTIONS:
	
					
						break;
					case gef_SONY_CTRL_CROSS:
	
	
						break;
					case gef_SONY_CTRL_CIRCLE:
	
	
						break;
					case gef_SONY_CTRL_TRIANGLE:
	
	
						break;
					case gef_SONY_CTRL_SQUARE:
	
	
						break;
					case gef_SONY_CTRL_UP:
	
	
						break;
					case gef_SONY_CTRL_RIGHT:
	
	
						break;
					case gef_SONY_CTRL_DOWN:
	
	
						break;
					case gef_SONY_CTRL_LEFT:
	
	
						break;
					case gef_SONY_CTRL_L1:
	
	
						break;
					case gef_SONY_CTRL_L2:
	
	
						break;
					case gef_SONY_CTRL_L3:
	
	
						break;
					case gef_SONY_CTRL_R1:
	
	
						break;
					case gef_SONY_CTRL_R2:
	
	
						break;
					case gef_SONY_CTRL_R3:
	
				
						break;	
					case gef_SONY_CTRL_CIRCLE & gef_SONY_CTRL_CROSS:


						break;
					default:
						break;
				}
		}

}


void PawnController::ProcessInputDevices()
{

	//if (input_manager_)
	//{
	//	input_manager_->Update();


	//	ProcessTouchInput();

	//}

}
