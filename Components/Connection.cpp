#include "Connection.h"

Connection::Connection(GraphicsInfo *r_GfxInfo, Component *cmp1, Component *cmp2)
{
	pGfxInfo = r_GfxInfo;
	Cmpnt1 = cmp1;
	Cmpnt2 = cmp2;
}
void Connection::Draw(UI* pUI)
{
	pUI->DrawConnection(*pGfxInfo);
}


void Connection::load(Component* C1, Component* C2)  //load connection
{
	Comp1 = C1;        // the first component which the loading connection will be connected with
	Comp2 = C2;        // the second component which the loading connection will be connected with

}
void Connection::EditConnection(Component* component1, Component* component2, GraphicsInfo* pGInfo, UI* pUI)
{
	/*pUI->DeleteConnection(*pGfxInfo);*/
	if (Comp1 == this->getOtherComponent(component1))
	{


		Comp1 = component2;
		pGfxInfo->PointsList[0].x = pGInfo->PointsList[0].x;
		pGfxInfo->PointsList[0].y = pGInfo->PointsList[0].y;
	}
	else if (Comp2 == this->getOtherComponent(component1))
	{

		Comp2 = component2;
		pGfxInfo->PointsList[1].x = pGInfo->PointsList[0].x;
		pGfxInfo->PointsList[1].y = pGInfo->PointsList[0].y;

	}


}