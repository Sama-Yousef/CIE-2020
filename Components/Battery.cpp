#include "Battery.h"

Battery::Battery(GraphicsInfo* r_GfxInfo) :Component(r_GfxInfo)
{}

void Battery::Draw(UI* pUI)
{
	//Call output class and pass resistor drawing info to it.
	pUI->DrawResistor(*m_pGfxInfo); //update to draw resistor

}

void Battery::Operate()
{

}