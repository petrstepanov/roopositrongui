/*
 * ProjectView.cpp
 *
 *  Created on: Apr 17, 2019
 *      Author: petrstepanov
 */

#include "ProjectView.h"
#include "ProjectPresenter.h"
#include "../../resources/Constants.h"
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
	TGVerticalFrame* rightVerticalFrame = new TGVerticalFrame(projectHorizontalFrame);
	TGVSplitter *splitter = new TGVSplitter(projectHorizontalFrame);
	splitter->SetWidth(Padding::dx);
	splitter->SetFrame(leftVerticalFrame, kTRUE);

	projectHorizontalFrame->AddFrame(leftVerticalFrame, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandY));
	projectHorizontalFrame->AddFrame(splitter, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandY));
	projectHorizontalFrame->AddFrame(rightVerticalFrame, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX | kLHintsExpandY));

	// Shutter (accordion)
    TGShutter *shutter = new TGShutter(leftVerticalFrame);

    TGShutterItem *spectraShutterItem = new TGShutterItem(shutter, new TGHotString("  1.  S P E C T R A"), 1000, kVerticalFrame);
    ((TGTextButton*)spectraShutterItem->GetButton())->SetTextJustify(kTextLeft | kTextCenterY);
    UiHelper::setHeight(spectraShutterItem->GetButton(), 32);
    shutter->AddItem(spectraShutterItem);
    shutter->SetSelectedItem(spectraShutterItem);

    TGShutterItem *modelShutterItem = new TGShutterItem(shutter, new TGHotString("  2.  M O D E L"), 1001, kVerticalFrame);
    ((TGTextButton*)modelShutterItem->GetButton())->SetTextJustify(kTextLeft | kTextCenterY);
    UiHelper::setHeight(modelShutterItem->GetButton(), 32);
    shutter->AddItem(modelShutterItem);

    TGShutterItem *fittingShutterItem = new TGShutterItem(shutter, new TGHotString("  3.  F I T T I N G"), 1002, kVerticalFrame);
    ((TGTextButton*)fittingShutterItem->GetButton())->SetTextJustify(kTextLeft | kTextCenterY);
    UiHelper::setHeight(fittingShutterItem->GetButton(), 32);
    shutter->AddItem(fittingShutterItem);
//    shutter->SetWidth(Constants::leftPanelWidth);
    leftVerticalFrame->AddFrame(shutter, new TGLayoutHints(kLHintsNormal | kLHintsExpandX | kLHintsExpandY, Padding::dx, 0, Padding::dx, Padding::dx));

    // Data files tab
    TGCompositeFrame *filesContainer = (TGCompositeFrame *)spectraShutterItem->GetContainer();
    UiHelper::setDarkBackground(filesContainer);

    TGViewPort* filesViewPort = (TGViewPort*)UiHelper::getParentFrame(filesContainer);
    filesView = new FilesView(filesContainer);
    filesContainer->AddFrame(filesView, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX | kLHintsExpandY, Padding::dx, Padding::dx, Padding::dy, Padding::dy));

    // Handle resize properly
    filesViewPort->Connect("ProcessedConfigure(Event_t*)", "ProjectView", this, "HandleConfigure(Event_t*)");

    //    TGCompositeFrame* child = new TGCompositeFrame(tab);
//    child->SetBackgroundColor(TColor::Number2Pixel(kBlue));
//    tab->AddFrame(child, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX | kLHintsExpandY, 30, 30, 30, 30));

    // Model tab
    // ...

    // Fitting tab
    // ...

    AddFrame(projectHorizontalFrame, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX | kLHintsExpandY));

    // Plots view
    PlotsView* plotsView = new PlotsView(rightVerticalFrame);
    rightVerticalFrame->AddFrame(plotsView, new TGLayoutHints(kLHintsNormal | kLHintsExpandX | kLHintsExpandY, 0, Padding::dx, Padding::dy*2, Padding::dy*2));
}

// Hack resize Files View
void ProjectView::HandleConfigure(Event_t *event){
	filesView->Resize(event->fWidth - Padding::dx*2, event->fHeight - Padding::dy*2);
	Layout();
}
