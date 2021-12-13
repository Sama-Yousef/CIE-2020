#include "ActionEdit.h"
#include "../ApplicationManager.h"

ActionEdit::ActionEdit(ApplicationManager * pApp) :Action(pApp)
{
}

ActionEdit::~ActionEdit(void)
{
}

void ActionEdit::Execute()
{
	int x = 0;
	int y = 0;	

	//Get a Pointer to the user Interfaces
	UI* pUI = pManager->GetUI();

	                                                     
	pUI->PrintMsg("Choose to Edit");   //Print Action Message
	pUI->GetPointClicked(x,y);
    Component* comp= pManager->GetComponentByCordinates(x, y);
	Connection* connection = pManager->GetConnectionByCordinates(x, y);

	if (comp)
	{
		int r ;
		if (comp->getResistance() == 0 && comp->getSourceVoltage() == 0)
		{
		  r = 1;
		}
		else 
		{
		 pUI->PrintMsg("Choose 1 to Edit the label or choose 2 to Edit the value");
		 r = stoi(pUI->GetSrting());
		}	
		   if (r == (1))
			{
				pUI->PrintMsg("enter the new label");
				comp->Setlabel(pUI->GetSrting());
				pUI->ClearStatusBar();
			}
			if (r == (2))
			{
				string Check;
				bool isNumber;                    // putting a value for the battery 
				do {
					pUI->PrintMsg("Enter the new value");
					Check = pUI->GetSrting();
					isNumber = true;
					for (int i = 0; i < Check.length(); i++)
					{
						if (isdigit(Check[i]) == false)
						{
							isNumber = false;
						}
					}
				} while (!isNumber);
				double intCheck = stoi(Check);
				if (comp->getResistance() > comp->getSourceVoltage())
				{
					comp->setResistance(intCheck);

				}
				else if (comp->getResistance() <= comp->getSourceVoltage())
				{
					comp->setSourceVoltage(intCheck);
				}
				pUI->ClearStatusBar();
			}
		
    }
	else if(connection)
	{
		pUI->PrintMsg("choose the component that you want to change");
		pUI->GetPointClicked(x, y);
		Component* component1 = pManager->GetComponentByCordinates(x, y);
		Component* compConnect= connection->getOtherComponent(component1);

		TerminalNum tur = component1->whichTerminal(connection);
		if (tur==TERM1)
		{
			component1->removeTerm1Connection(connection);
		}
		else if(tur == TERM2)
		{
			component1->removeTerm2Connection(connection);
		}
		pUI->PrintMsg("choose the componet the component to be connect ");
		pUI->GetPointClicked(x, y);
		Component* component2 = pManager->GetComponentByCordinates(x, y);
		GraphicsInfo* pGInfo = new GraphicsInfo(1); //Gfx info to be used to construct the Comp
		tur = component2->whichTerminal(connection);
		if (tur == TERM1)
		{
			component2->addTerm1Connection(connection);
		}
		else if (tur == TERM2)
		{
			component2->addTerm2Connection(connection);
		}
	//Calculate the rectangle Corners
		int compWidth = pUI->getCompWidth();
		int compHeight = pUI->getCompHeight();
		
		pGInfo->PointsList[0].y = component2->getCompCentery(pUI);
		
		if (x < component2->getCompCenterx(pUI))
		{
			pGInfo->PointsList[0].x = component2->getCompCenterx(pUI) - compWidth / 2;
		}
		else
		{
			pGInfo->PointsList[0].x = component2->getCompCenterx(pUI) + compWidth / 2;
		}
		connection->EditConnection(compConnect, component2, pGInfo,pUI);
		pUI->ClearStatusBar();

	}


	GraphicsInfo* pGInfo = new GraphicsInfo(2); //Gfx info to be used to construct the Comp

	//Calculate the rectangle Corners
	int compWidth = pUI->getCompWidth();
	int compHeight = pUI->getCompHeight();

	pGInfo->PointsList[0].x = Cx - compWidth / 2;
	pGInfo->PointsList[0].y = Cy - compHeight / 2;
	pGInfo->PointsList[1].x = Cx + compWidth / 2;
	pGInfo->PointsList[1].y = Cy + compHeight / 2;	
}

void ActionEdit::Undo()
{}

void ActionEdit::Redo()
{}

