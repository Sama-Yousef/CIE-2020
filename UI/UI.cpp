#include "UI.h"

UI::UI()
{
	AppMode = DESIGN;	//Design Mode is the startup mode

	//Initilaize interface colors
	DrawColor = BLACK;
	SelectColor = BLUE;
	ConnColor = RED;
	MsgColor = BLUE;
	BkGrndColor = WHITE;
	
	//Create the drawing window
	pWind = new window(width, height, wx, wy);	


	ChangeTitle("Logic Simulator Project");

	CreateDesignToolBar();	//Create the desgin toolbar
	CreateStatusBar();		//Create Status bar
}


int UI::getCompWidth() const
{
	return COMP_WIDTH;
}

int UI::getCompHeight() const
{
	return COMP_HEIGHT;
}

//======================================================================================//
//								Input Functions 										//
//======================================================================================//

void UI::GetPointClicked(int &x, int &y)
{
	pWind->WaitMouseClick(x, y);	//Wait for mouse click
}

string UI::GetSrting()
{
	//Reads a complete string from the user until the user presses "ENTER".
	//If the user presses "ESCAPE". This function should return an empty string.
	//"BACKSPACE" is also supported
	//User should see what he is typing at the status bar


	string userInput;
	char Key;
	while(1)
	{
		pWind->WaitKeyPress(Key);

		switch(Key)
		{
		case 27: //ESCAPE key is pressed
			PrintMsg("");
			return ""; //returns nothing as user has cancelled the input
		
		case 13:		//ENTER key is pressed
			return userInput;
		
		case 8:		//BackSpace is pressed
			if(userInput.size() > 0)
				userInput.resize(userInput.size() -1 );
			break;
		
		default:
			userInput+= Key;
		};
		
		PrintMsg(userInput);
	}

}

//This function reads the position where the user clicks to determine the desired action
ActionType UI::GetUserAction() const
{	
	int x,y;
	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click

	if(AppMode == DESIGN )	//application is in design mode
	{
		if (y >= 0 && y < ToolBarHeight && v == 1)
		{
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / ToolItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
			case ITM_RES:	return ADD_RESISTOR;
			case ITM_BULB:	return ADD_BULB;
			case ITM_SWI:	return ADD_SWITCH;
			case ITM_BAT:   return ADD_BATTERY;
			case ITM_GRO:   return ADD_GROUND;
			case ITM_BUZ:   return ADD_BUZZER;
			case ITM_FUE:   return ADD_FUES;
			case ITM_CON:   return ADD_CONNECTION;
			case ITM_SIM:	return SIM_MODE;
			case ITM_LABEL: return ADD_Label;
			case ITM_LOAD:	return LOAD;
			case ITM_MOD:	return ADD_MOD;
			case ITM_MODU:	return MOD_MODE;
			case ITM_EXIT:	return EXIT;

			default: return DSN_TOOL;	//A click on empty place in desgin toolbar
			}
		}

		//[2] User clicks on the drawing area
		if (y >= ToolBarHeight && y < height - StatusBarHeight)
		{
			if (v == 2)
				DrawActionBar();
			else
			{
				if (x < 25 && y<getHeight() - getStatusBarHeight() && y > getHeight() - getStatusBarHeight() - 40)
				{
					return ADD_REALISTIC;
				}
				return SELECT; //user wants to select/unselect a component
			}

		}

		if (y >= ToolBarHeight && y < height - StatusBarHeight)
		{

			int x1, y1;
			PrintMsg("Click on action to execute");
			pWind->WaitMouseClick(x1, y1);

			pWind->SetPen(WHITE);
			pWind->DrawRectangle(1135, 80, 1200, 600, FILLED);
			ClearStatusBar();
			int ClickedItemOrder = (y1 - ToolBarHeight) / 52;
			if (x1 > width - ActionBarWidth && x1 < width)
			{
				switch (ClickedItemOrder)
				{
				case ITMA_Edit:		return EDIT_Label;
				case ITMA_Move:		return MOVE;
				case ITMA_MDel:		return MDEL;
				case ITMA_Save:		return SAVE;
				case ITMA_Undo:		return UNDO;
				case ITMA_Redo:		return REDO;
				case ITMA_Copy:		return ADD_COPY;
				case ITMA_Cut:		return ADD_CUT;
				case ITMA_Paste:	return ADD_PASTE;
				case ITMA_Delete:	return DEL;
				default:			return DSN_TOOL;
				}
			}
		}
		//[3] User clicks on the status bar
		return STATUS_BAR;
	}
	}
	else	//Application is in Simulation mode
	{
		return SIM_MODE;	//This should be changed after creating the compelete simulation bar 
	}

}



//======================================================================================//
//								Output Functions										//
//======================================================================================//

//////////////////////////////////////////////////////////////////////////////////
void UI::ChangeTitle(string Title) const
{
	pWind->ChangeTitle(Title);
}
//////////////////////////////////////////////////////////////////////////////////
void UI::CreateStatusBar() const
{
	pWind->SetPen(RED,3);
	pWind->DrawLine(0, height-StatusBarHeight, width, height-StatusBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////
void UI::PrintMsg(string msg) const
{
	ClearStatusBar();	//Clear Status bar to print message on it
	// Set the Message offset from the Status Bar
	int MsgX = 25;
	int MsgY = StatusBarHeight - 10;

	// Print the Message
    pWind->SetFont(20, BOLD | ITALICIZED, BY_NAME, "Arial"); 
	pWind->SetPen(MsgColor); 
	pWind->DrawString(MsgX, height - MsgY, msg);
}
//////////////////////////////////////////////////////////////////////////////////
void UI::ClearStatusBar()const
{
	// Set the Message offset from the Status Bar
	int MsgX = 25;
	int MsgY = StatusBarHeight - 10;

	//Overwrite using bachground color to erase the message
	pWind->SetPen(BkGrndColor);
	pWind->SetBrush(BkGrndColor);
	pWind->DrawRectangle(MsgX, height - MsgY, width, height);
}
//////////////////////////////////////////////////////////////////////////////////////////
//Clears the drawing (degin) area
void UI::ClearDrawingArea() const
{
	pWind->SetPen(RED, 1);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, ToolBarHeight, width, height - StatusBarHeight);
	
}
//////////////////////////////////////////////////////////////////////////////////////////
//Draws the menu (toolbar) in the Design mode
void UI::CreateDesignToolBar() 
{
	AppMode = DESIGN;	//Design Mode

	//You can draw the tool bar icons in any way you want.

	//First prepare List of images for each menu item
	string MenuItemImages[ITM_DSN_CNT];
	MenuItemImages[ITM_RES] = "images\\Menu\\Menu_Resistor.jpg";
	MenuItemImages[ITM_BAT] = "images\\Menu\\Menu_Battery.jpg";
	MenuItemImages[ITM_SWI] = "images\\Menu\\Menu_Switch.jpg";
	MenuItemImages[ITM_EXIT] = "images\\Menu\\Menu_Exit.jpg";

	//TODO: Prepare image for each menu item and add it to the list

	//Draw menu item one image at a time
	for(int i=0; i<ITM_DSN_CNT; i++)
		pWind->DrawImage(MenuItemImages[i],i*ToolItemWidth,0,ToolItemWidth, ToolBarHeight);


	//Draw a line under the toolbar
	pWind->SetPen(RED,3);
	pWind->DrawLine(0, ToolBarHeight, width, ToolBarHeight);	

}
//////////////////////////////////////////////////////////////////////////////////////////
//Draws the menu (toolbar) in the simulation mode
void UI::CreateSimulationToolBar()
{
	AppMode = SIMULATION;	//Simulation Mode

	//TODO: Write code to draw the simualtion toolbar (similar to that of design toolbar drawing)


}

//======================================================================================//
//								Components Drawing Functions							//
//======================================================================================//

void UI::DrawResistor(const GraphicsInfo &r_GfxInfo, bool selected) const
{
	string ResImage;
	if(selected)	
		ResImage ="Images\\Comp\\Resistor_HI.jpg";	//use image of highlighted resistor
	else  
		ResImage = "Images\\Comp\\Resistor.jpg";	//use image of the normal resistor

	//Draw Resistor at Gfx_Info (1st corner)
	pWind->DrawImage(ResImage, r_GfxInfo.PointsList[0].x, r_GfxInfo.PointsList[0].y, COMP_WIDTH, COMP_HEIGHT);
}

void UI::DrawBattery(const GraphicsInfo& r_GfxInfo, bool selected) const
{
	string BatImage;
	if (selected)
		BatImage = "Images\\Comp\\Battery_HI.jpg";	//use image of highlighted battery
	else
		BatImage = "Images\\Comp\\Battery.jpg";	//use image of the normal battery

	//Draw battery at Gfx_Info (1st corner)
	pWind->DrawImage(BatImage, r_GfxInfo.PointsList[0].x, r_GfxInfo.PointsList[0].y, COMP_WIDTH, COMP_HEIGHT);
}
//TODO: Add similar functions to draw all other components
void UI::DrawSwitch(const GraphicsInfo& r_GfxInfo, bool selected) const
{
	string SwiImage;
	if (selected)
			SwiImage = "Images\\Comp\\Switch_HI.jpg";	//use image of highlighted switch
		else
			SwiImage = "Images\\Comp\\Switch.jpeg";	//use image of the normal switch
	//Draw switch at Gfx_Info (1st corner)        // Draw the image of the switch after adding the width and the height
	pWind->DrawImage(SwiImage, r_GfxInfo.PointsList[0].x, r_GfxInfo.PointsList[0].y, COMP_WIDTH, COMP_HEIGHT);
}



void UI::DrawConnection(const GraphicsInfo &r_GfxInfo, bool selected) const
{
	if (selected == true)
		//if (AppMode == DESIGN)	//application is in design mode
	{
		//if (r_GfxInfo.PointsList[0].y > ToolBarHeight && r_GfxInfo.PointsList[0].y < height - StatusBarHeight && r_GfxInfo.PointsList[1].y > ToolBarHeight && r_GfxInfo.PointsList[1].y < height - StatusBarHeight)
		pWind->SetPen(PINK, 3);
		pWind->DrawLine(r_GfxInfo.PointsList[0].x, r_GfxInfo.PointsList[0].y, r_GfxInfo.PointsList[1].x, r_GfxInfo.PointsList[1].y);
	}
	else
	{
		pWind->SetPen(BLACK, 3);
		pWind->DrawLine(r_GfxInfo.PointsList[0].x, r_GfxInfo.PointsList[0].y, r_GfxInfo.PointsList[1].x, r_GfxInfo.PointsList[1].y);
	}

}

void UI::DrawBulb(const GraphicsInfo &r_GfxInfo, bool selected) const
{
	string ResImage;
	if(selected)	
		ResImage ="Images\\Comp\\Bulb_HI.jpg";	//use image of highlighted bulb
	else  
		ResImage = "Images\\Comp\\Bulb.png";	//use image of the normal bulb

	//Draw bulb at Gfx_Info (1st corner)
	pWind->DrawImage(ResImage, r_GfxInfo.PointsList[0].x, r_GfxInfo.PointsList[0].y, COMP_WIDTH, COMP_HEIGHT);
}


UI::~UI()
{
	delete pWind;
}
