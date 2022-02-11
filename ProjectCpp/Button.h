#pragma once
#include "UiElements.h"
#include "IUi.h"
#include <iostream>

enum class ButtonState
{
    IDLE, HOVER, CLICK
};

class Button : public UiElements
{
public:
    Button();
    Button(Vector2 pos, Texture2D spriteP, float widthP, float heightP, bool use9SliceP);
    Button(Vector2 pos, float widthP, float heightP);
    ~Button();

    void ButtonCliqued();
    void ButtonHovered();

    void Update() override;
   // void Draw() override;

    Vector2* mousePos;

    void CliquedSendFunction();
    void CliquedSendFunctionWithInt();

    void (*functPrt)();
    void (*functPrtInt)(int);

    int value;



private:
    ButtonState state;
    bool use9Slice;

    Rectangle buttonRectangle;




};

//Faire en sorte qu'on puisse mettre du texte dans le bouton
//Mettre la possibilité que le boutton fasse la taille de l'image dedans
