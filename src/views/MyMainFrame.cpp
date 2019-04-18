/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   MyMainFrame.cpp
 * Author: petrstepanov
 *
 * Created on October 15, 2017, 1:47 AM
 */

#include "MyMainFrame.h"

#include <TApplication.h>
#include <TG3DLine.h>
#include <TGStatusBar.h>
#include <iostream>
#include <TGFrame.h>
#include "../resources/Constants.h"
#include "../resources/Images.h"
#include "../util/UiHelper.h"
#include "toolbar/ToolbarView.h"
#include "project/ProjectView.h"

MyMainFrame::MyMainFrame() : TGMainFrame(gClient->GetRoot(), Constants::windowWidth, Constants::windowHeight) {
	projectView = nullptr;

	SetIconPixmap(Images::applicationIcon);
	SetWindowName(Constants::applicationName);
	SetCleanup(kDeepCleanup);

	// Exit this application via the Exit button or Window Manager.
	Connect("CloseWindow()", "MyMainFrame", this, "exit()");
    DontCallClose();

    // SetBackgroundColor(TColor::Number2Pixel(kWhite));
    // SetBackgroundColor(fClient->GetShadow(GetDefaultFrameBackground()));

    // Save reverence to MyMainFrame in UiHelper (for centering of modal dialogs)
    UiHelper::getInstance()->setMainFrame(this);
    SetLayoutManager(new TGVerticalLayout(this));

    // Toolbar
    ToolbarView* toolbar = new ToolbarView(this);
    AddFrame(toolbar, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX, Padding::dx, Padding::dx, Padding::dx, Padding::dx));

    // Horizontal line
    // AddFrame(new TGHorizontal3DLine(this), new TGLayoutHints(kLHintsExpandX, 0, 0, 0, 0));

    // Project container
    projectContainer = new TGCompositeFrame(this);
    projectContainer->SetBackgroundColor(fClient->GetShadow(GetDefaultFrameBackground()));
    AddFrame(projectContainer, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX | kLHintsExpandY));

//    Int_t parts[] = {100};
    TGStatusBar* statusBar = new TGStatusBar(this);
    AddFrame(statusBar, new TGLayoutHints(kLHintsBottom | kLHintsLeft | kLHintsExpandX));
    statusBar->SetText("Welcome to RooLifetime. Create New Project or open existing.",0);

    // Conect slots to model signals
    Model* model = Model::getInstance();
    model->Connect("projectCreated()", "MyMainFrame", this, "handleProjectCreated()");
    model->Connect("projectClosed()", "MyMainFrame", this, "handleProjectClosed()");
}

MyMainFrame::~MyMainFrame(){
    Cleanup();
}

void MyMainFrame::show(){
	// Set minimum and maximum window size for window manager
	SetWMSizeHints(Constants::windowWidth, Constants::windowHeight, 1E4, 1E4, 1, 1);
	MapSubwindows();
	Layout();
	// Issue - GetDefaultSize() returns zeros on Ubuntu 18.04.
    Resize(Constants::windowWidth, Constants::windowHeight);
    // Maps the window "id" and all of its subwindows that have had map requests on the screen and put this window on the top of of the stack of all windows
    MapWindow();
}

void MyMainFrame::exit(){
	// DeleteWindow();              // to stay in the ROOT session
	gApplication->Terminate();   // to exit and close the ROOT session
}

// Slots for Model Signals
void MyMainFrame::handleProjectCreated(){
	Debug("MyMainFrame::handleProjectCreated");
	// Create new Project view when new Project was created
	if (projectView != nullptr){
		UiHelper::removeFrame(projectView);
	}
    projectView = new ProjectView(projectContainer);
    projectContainer->AddFrame(projectView, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX | kLHintsExpandY));
    projectContainer->MapSubwindows();
    projectContainer->Layout();
}

void MyMainFrame::handleProjectClosed(){
	Debug("MyMainFrame::handleProjectClosed");
	projectContainer->GetList()->Print();
	// Remove Project view when new Project closed
	if (projectView != nullptr){
		UiHelper::removeFrame(projectView);
	}
	projectContainer->GetList()->Print();
	projectContainer->MapSubwindows();
    projectContainer->Layout();
}
