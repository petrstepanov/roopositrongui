/*
 * ProjectView.cpp
 *
 *  Created on: Apr 17, 2019
 *      Author: petrstepanov
 */

#include "ProjectView.h"
#include "ProjectPresenter.h"
#include "../../resources/Constants.h"
#include "../files/FilesView.h"
#include "../../util/UiHelper.h"

ProjectView::ProjectView(const TGWindow *w) : AbstractView<ProjectPresenter>(w){
	// Instantinate presenter
	presenter = instantinatePresenter();
	// Initialize UI elements

	// Build UI
	initUI();
}

ProjectView::~ProjectView(){};

ProjectPresenter* ProjectView::instantinatePresenter(){
    return new ProjectPresenter(this);
}

void ProjectView::initUI(){
	SetLayoutManager(new TGVerticalLayout(this));
	UiHelper::setDarkBackground(this);

	// Splitter
	TGHorizontalFrame* projectHorizontalFrame = new TGHorizontalFrame(this);
	TGVerticalFrame* leftVerticalFrame = new TGVerticalFrame(projectHorizontalFrame);
	leftVerticalFrame->ChangeOptions(leftVerticalFrame->GetOptions() | kFixedWidth);
	leftVerticalFrame->SetWidth(Constants::leftPanelWidth);
	TGVerticalFrame* righterticalFrame = new TGVerticalFrame(projectHorizontalFrame);
	TGVSplitter *splitter = new TGVSplitter(projectHorizontalFrame);
	splitter->SetWidth(Padding::dx);
	splitter->SetFrame(leftVerticalFrame, kTRUE);

	projectHorizontalFrame->AddFrame(leftVerticalFrame, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandY));
	projectHorizontalFrame->AddFrame(splitter, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandY));
	projectHorizontalFrame->AddFrame(righterticalFrame, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX | kLHintsExpandY));

	// Shutter (accordion)
    TGShutter *shutter = new TGShutter(leftVerticalFrame);
    TGShutterItem *spectraShutterItem = new TGShutterItem(shutter, new TGHotString("SPECTRA"), 1000, kVerticalFrame);
    shutter->AddItem(spectraShutterItem);
    shutter->SetSelectedItem(spectraShutterItem);
    TGShutterItem *modelShutterItem = new TGShutterItem(shutter, new TGHotString("MODEL"), 1001, kVerticalFrame);
    shutter->AddItem(modelShutterItem);
    TGShutterItem *fittingShutterItem = new TGShutterItem(shutter, new TGHotString("FITTING"), 1002, kVerticalFrame);
    shutter->AddItem(fittingShutterItem);
//    shutter->SetWidth(Constants::leftPanelWidth);
    leftVerticalFrame->AddFrame(shutter, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX | kLHintsExpandY));

    // Data files tab
    TGCompositeFrame *tab = (TGCompositeFrame *)spectraShutterItem->GetContainer();
//    tab->ChangeOptions(tab->GetOptions() | kFixedHeight);
//    tab->SetHeight(300);
    UiHelper::setDarkBackground(tab);
    FilesView* filesView = new FilesView(tab);
    tab->AddFrame(filesView, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX | kLHintsExpandY, Padding::dx, Padding::dx, Padding::dy, Padding::dy));

    // Model tab
    // ...

    // Fitting tab
    // ...

    TGCanvas leftCanvas = new TGCanvas(this);


    AddFrame(projectHorizontalFrame, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX | kLHintsExpandY));
    righterticalFrame->SetBackgroundColor(fClient->GetShadow(GetDefaultFrameBackground()));
}
