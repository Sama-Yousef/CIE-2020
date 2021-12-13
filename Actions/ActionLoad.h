#pragma once
#include <iostream>
using namespace std;
#include <fstream>
#include "Action.h"
#include "../ApplicationManager.h"
#include "../UI/UI.h"
#include <string>
#include "../Components/Battery.h"
#include "../Components/Bulb.h"
#include "../Components/Buzzer.h"
#include "../Components/Component.h"
#include "../Components/Fues.h"
#include "../Components/Ground.h"
#include "../Components/Resistor.h"

#include "../Components/Switch.h"
class ActionLoad : public Action
{
	string filename;    // name of the file which will be loaded
	int ComID;          // id for the component 
	string input;       // variable to take string 
	Component* comp01;  // pointer to comp 
	Component* comp02; 
public :
	ActionLoad(ApplicationManager* pApp); //constructor


	~ActionLoad(void);//destructor 
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo(); //undo for the load

	virtual void Redo(); //Redo for the load 

};


