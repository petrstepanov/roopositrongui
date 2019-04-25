/*
 * PlotsView.cpp
 *
 *  Created on: Apr 23, 2019
 *      Author: petrstepanov
 */

#include "PlotsView.h"
#include "PlotsPresenter.h"

#include "../../util/UiHelper.h"
#include <TGTab.h>
#include <TRootEmbeddedCanvas.h>
#include <TGDoubleSlider.h>
#include <TGButton.h>

PlotsView::PlotsView(const TGWindow *w) : AbstractView<PlotsPresenter>(w){
	// Build UI
	initUI();

	// Instantinate presenter
	presenter = instantinatePresenter();
	connectSlots();
}

PlotsView::~PlotsView(){};

PlotsPresenter* PlotsView::instantinatePresenter(){
    return new PlotsPresenter(this);
}

void PlotsView::initUI(){
	SetLayoutManager(new TGVerticalLayout(this));

	// Layout UI elements and attach signals
    TGTab* plotTabs = new TGTab(this);

    // Import spectrum tab
    TGCompositeFrame *tabImport = plotTabs->AddTab("temp-spectrum.Spe");
    TRootEmbeddedCanvas* embeddedCanvas = new TRootEmbeddedCanvas("canvas_temp-spectrum.Spe", tabImport);
    tabImport ->AddFrame(embeddedCanvas, new TGLayoutHints(kLHintsNormal | kLHintsExpandX | kLHintsExpandY, Padding::dx, Padding::dx, Padding::dy*2, Padding::dy*2));

    AddFrame(plotTabs, new TGLayoutHints(kLHintsNormal | kLHintsExpandX | kLHintsExpandY, 0, 0, 0, Padding::dy));

    // Add bottom slider
    TGHorizontalFrame* controlsHorizontalFrame = new TGHorizontalFrame(this);
    TGDoubleHSlider* scaleSlider = new TGDoubleHSlider(controlsHorizontalFrame, 1, kDoubleScaleBoth, -1, kHorizontalFrame, GetDefaultFrameBackground(), kFALSE, kFALSE);
    // scaleSlider->Connect("PositionChanged()", ...
    scaleSlider->SetRange(0, 8192);
    scaleSlider->SetPosition(0, 8192);
    TGTextButton* exportPointsTextButton = new TGTextButton(controlsHorizontalFrame, "Export data points");
    TGTextButton* saveImagesTextButton = new TGTextButton(controlsHorizontalFrame, "Save images");
    controlsHorizontalFrame->AddFrame(scaleSlider, new TGLayoutHints(kLHintsNormal | kLHintsExpandX, 0, Padding::dx));
    controlsHorizontalFrame->AddFrame(exportPointsTextButton, new TGLayoutHints(kLHintsNormal, Padding::dx));
    controlsHorizontalFrame->AddFrame(saveImagesTextButton, new TGLayoutHints(kLHintsNormal, Padding::dx));

    AddFrame(controlsHorizontalFrame, new TGLayoutHints(kLHintsNormal | kLHintsExpandX, 0, 0, Padding::dy, 0));
}

void PlotsView::connectSlots(){
	// button->Connect("Clicked()", "__View", presenter, "onButtonClicked()");
}
