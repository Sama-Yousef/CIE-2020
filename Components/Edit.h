#pragma once

#include "Component.h"

class Edit :public Component
{
public:
	Edit(GraphicsInfo* r_GfxInfo, UI* pUI);
	virtual void Draw(UI*);	//Draws the bulb
	virtual void Operate();
};
