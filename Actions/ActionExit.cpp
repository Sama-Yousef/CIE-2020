#include "ActionExit.h"


void Exit::Execute()
{
	UI* pUI = pManager->GetUI();

	pUI->PrintMsg("Do you really want to exit?(y/n)");

    userinput = pUI-> Getstring()

    if (*userinput == "y")
        exit(1);
    else if (*userinput == "n")
        pUI-> ClearStatusBar();
    else 
    {
        pUI->PrintMsg("please enter (y/n)!");
        Exit::Execute();
    }
};