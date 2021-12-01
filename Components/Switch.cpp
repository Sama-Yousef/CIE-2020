#include "Switch.h"

Switch::Switch(GraphicsInfo* r_GfxInfo) :Component(r_GfxInfo)
{}

void Switch::Draw(UI* pUI)
{
	//Call output class and pass Switch drawing info to it.
	pUI->DrawSwitch(*m_pGfxInfo); //update to draw Switch

}

void Switch::Operate()
{

}