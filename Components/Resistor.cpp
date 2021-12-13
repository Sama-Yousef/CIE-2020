#include "Resistor.h"

Resistor::Resistor(GraphicsInfo *r_GfxInfo):Component(r_GfxInfo)
{}

void Resistor::Draw(UI* pUI)
{
	//Call output class and pass resistor drawing info to it.
	pUI->DrawResistor(*m_pGfxInfo); //update to draw resistor

}

void Resistor::Operate()
{

}
void Resistor::load(int id, string LABELi, double VALUE)        //load if there is a Resistor in the saved file 
{
	ID = id,                             // id for the resistance
		m_Label = LABELi;                  //label for the resistance .
	resistance = VALUE;                //the value of the resitance 
}