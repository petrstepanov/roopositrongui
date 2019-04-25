/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   SWCalculatorFrame.cpp
 * Author: petrstepanov
 *
 * Created on August 1, 2017, 5:02 PM
 */

#include "ToolbarView.h"
#include "ToolbarPresenter.h"
#include <TGButton.h>
#include "../../resources/Images.h"
#include "../../resources/Constants.h"

ToolbarView::ToolbarView(const TGWindow *w) : AbstractView<ToolbarPresenter>(w){
	// Build UI
	initUI();

	// Instantinate presenter and connect slots
	presenter = instantinatePresenter();
	connectSlots();
}

ToolbarPresenter* ToolbarView::instantinatePresenter(){
    return new ToolbarPresenter(this);
}

void ToolbarView::initUI(){
	newButton = new TGPictureButton(this, Images::makeTGPicture(Images::projectNewXpm));
    openButton = new TGPictureButton(this, Images::makeTGPicture(Images::projectOpenXpm));
    saveButton = new TGPictureButton(this, Images::makeTGPicture(Images::projectSaveXpm));
    saveAsButton = new TGPictureButton(this, Images::makeTGPicture(Images::projectSaveAsXpm));
    closeButton = new TGPictureButton(this, Images::makeTGPicture(Images::projectCloseXpm));


	SetLayoutManager(new TGHorizontalLayout(this));
    // SetBackgroundColor(TColor::Number2Pixel(kWhite));
	AddFrame(newButton, new TGLayoutHints(kLHintsLeft, 0));
	AddFrame(openButton, new TGLayoutHints(kLHintsLeft, Padding::dx));
    AddFrame(saveButton, new TGLayoutHints(kLHintsLeft, Padding::dx));
    saveButton->SetEnabled(kFALSE);
    AddFrame(saveAsButton, new TGLayoutHints(kLHintsLeft, Padding::dx));
    saveAsButton->SetEnabled(kFALSE);
    AddFrame(closeButton, new TGLayoutHints(kLHintsRight, Padding::dx));
    closeButton->SetEnabled(kFALSE);
    // AddFrame(filenameLabel, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, Padding::dx, Padding::dx, Padding::dx, Padding::dx));
    // TGFont *font = gClient->GetFont("-*-helvetica-medium-r-*-*-14-*-*-*-*-*");
    // filenameLabel->SetTextFont(font, kTRUE);
    // filenameLabel->SetTextJustify(kTextRight | kTextCenterY);
}

void ToolbarView::connectSlots(){
	newButton->Connect("Clicked()", "ToolbarPresenter", presenter, "onNewButtonClicked()");
    openButton->Connect("Clicked()", "ToolbarPresenter", presenter, "onOpenButtonClicked()");
    saveButton->Connect("Clicked()", "ToolbarPresenter", presenter, "onSaveButtonClicked()");
    saveAsButton->Connect("Clicked()", "ToolbarPresenter", presenter, "onSaveAsButtonClicked()");
    closeButton->Connect("Clicked()", "ToolbarPresenter", presenter, "onCloseButtonClicked()");
}
