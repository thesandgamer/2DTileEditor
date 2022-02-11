#include "Button.h"

Button::Button()
{
}

Button::Button(Vector2 pos, Texture2D spriteP, float widthP, float heightP, bool use9SliceP)
	:UiElements(pos,spriteP,widthP,  heightP ),
	state(ButtonState::IDLE), use9Slice(use9SliceP), functPrt(nullptr), functPrtInt(nullptr)
{
}

Button::Button(Vector2 pos, float widthP, float heightP) 
	: UiElements(pos, widthP, heightP ),
	state(ButtonState::IDLE), use9Slice(false), functPrt(nullptr), functPrtInt(nullptr)
{
}

Button::~Button()
{

}

void Button::Update()
{
	mousePos = &GetMousePosition();
	//Check Si la souris est en hover
	if ( ( position.x < mousePos->x && mousePos->x < position.x + width ) 
		&& (position.y < mousePos->y&& mousePos->y < position.y + height) )
	{
		state = ButtonState::HOVER;
		drawColor = DARKGREEN;
	}
	else
	{
		state = ButtonState::IDLE;
		drawColor = GREEN;
	}

	if (state == ButtonState::HOVER)
	{
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			TraceLog(LOG_INFO, " Button cliqued");
			drawColor = GRAY;
			CliquedSendFunction();

			CliquedSendFunctionWithInt();

		}
	}

}


void Button::CliquedSendFunction()
{
	if (functPrt != nullptr)
	{
		(*functPrt)();
	}
}

void Button::CliquedSendFunctionWithInt()
{
	if (functPrtInt != nullptr)
	{
		if (value != NULL)
		{
			(*functPrtInt)(value);
		}
	}
}

