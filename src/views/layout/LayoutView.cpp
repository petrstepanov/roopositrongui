/*
 * LayoutView.cpp
 *
 *  Created on: Apr 26, 2019
 *      Author: petrstepanov
 */

#include "LayoutView.h"
#include "LayoutPresenter.h"
#include <TG3DLine.h>
#include <TGStatusBar.h>
#include "../toolbar/ToolbarView.h"
#include "../project/ProjectView.h"
#include "../../util/UiHelper.h"

LayoutView::LayoutView(const TGWindow *w) : AbstractView<LayoutPresenter>(w){
	// Build UI
	initUI();

	// Instantinate presenter and connect slots
	presenter = instantinatePresenter();
	connectSignalsToPresenter();
}

LayoutView::~LayoutView(){};

LayoutPresenter* LayoutView::instantinatePresenter(){
    return new LayoutPresenter(this);
}

void LayoutView::initUI(){
	SetLayoutManager(new TGVerticalLayout(this));

	// Toolbar
    ToolbarView* toolbar = new ToolbarView(this);
    AddFrame(toolbar, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX, Padding::dx, Padding::dx, Padding::dx, Padding::dx));

    // Horizontal line
    AddFrame(new TGHorizontal3DLine(this), new TGLayoutHints(kLHintsExpandX, 0, 0, 0, 0));

    // Project container
    projectContainer = new TGCompositeFrame(this);
    UiHelper::setDarkerBackground(projectContainer);
    AddFrame(projectContainer, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX | kLHintsExpandY));

//    Int_t parts[] = {100};
    TGStatusBar* statusBar = new TGStatusBar(this);
    AddFrame(statusBar, new TGLayoutHints(kLHintsBottom | kLHintsLeft | kLHintsExpandX));
    statusBar->SetText("Welcome to RooLifetime. Create New Project or open existing.",0);

}

void LayoutView::connectSignalsToPresenter(){
	// button->Connect("Clicked()", "LayoutView", presenter, "onButtonClicked()");
}

void LayoutView::createNewProjectView(){
	TGCompositeFrame* projectView = UiHelper::getFirstChildFrame(projectContainer);
 	UiHelper::removeFrame(projectView);

    ProjectView* newProjectView = new ProjectView(projectContainer);
    projectContainer->AddFrame(newProjectView, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX | kLHintsExpandY));
    projectContainer->MapSubwindows();
    projectContainer->Layout();
}

void LayoutView::removeProjectView(){
	TGCompositeFrame* projectView = UiHelper::getFirstChildFrame(projectContainer);
 	UiHelper::removeFrame(projectView);
 	projectContainer->MapSubwindows();
    projectContainer->Layout();
}
