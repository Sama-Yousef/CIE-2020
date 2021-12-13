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
void Switch::load(int id, string LABELi, double VALUE)
{
	ID = id;              // id for the switch 
	m_Label = LABELi;    //label for the switch. 
	status = VALUE;      //status for the switch 
}