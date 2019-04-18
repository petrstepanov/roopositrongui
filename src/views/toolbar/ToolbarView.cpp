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
	presenter = instantinatePresenter();
	newButton = new TGPictureButton(this, Images::makeTGPicture(Images::projectNewXpm));
    openButton = new TGPictureButton(this, Images::makeTGPicture(Images::projectOpenXpm));
    saveButton = new TGPictureButton(this, Images::makeTGPicture(Images::projectSaveXpm));
    saveAsButton = new TGPictureButton(this, Images::makeTGPicture(Images::projectSaveAsXpm));
    closeButton = new TGPictureButton(this, Images::makeTGPicture(Images::projectCloseXpm));
//    filenameLabel = new TGLabel(this, "Current project: /home/petrstepanov/pCloudDrive/LifetimeSpectroscopy/Data/2016-08-20-Cu-Poly-Irrad-Stand-No-Tape.root");
    initUI();
}

ToolbarPresenter* ToolbarView::instantinatePresenter(){
    return new ToolbarPresenter(this);
}

void ToolbarView::initUI(){
	SetLayoutManager(new TGHorizontalLayout(this));
    // SetBackgroundColor(TColor::Number2Pixel(kWhite));
	AddFrame(newButton, new TGLayoutHints(kLHintsLeft, 0));
	newButton->Connect("Clicked()", "ToolbarPresenter", presenter, "onNewButtonClicked()");
	AddFrame(openButton, new TGLayoutHints(kLHintsLeft, Padding::dx));
    openButton->Connect("Clicked()", "ToolbarPresenter", presenter, "onOpenButtonClicked()");
    AddFrame(saveButton, new TGLayoutHints(kLHintsLeft, Padding::dx));
    saveButton->Connect("Clicked()", "ToolbarPresenter", presenter, "onSaveButtonClicked()");
    saveButton->SetEnabled(kFALSE);
    AddFrame(saveAsButton, new TGLayoutHints(kLHintsLeft, Padding::dx));
    saveAsButton->Connect("Clicked()", "ToolbarPresenter", presenter, "onSaveAsButtonClicked()");
    saveAsButton->SetEnabled(kFALSE);
    AddFrame(closeButton, new TGLayoutHints(kLHintsRight, Padding::dx));
    closeButton->Connect("Clicked()", "ToolbarPresenter", presenter, "onCloseButtonClicked()");
    closeButton->SetEnabled(kFALSE);
    // AddFrame(filenameLabel, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, Padding::dx, Padding::dx, Padding::dx, Padding::dx));
    // TGFont *font = gClient->GetFont("-*-helvetica-medium-r-*-*-14-*-*-*-*-*");
    // filenameLabel->SetTextFont(font, kTRUE);
    // filenameLabel->SetTextJustify(kTextRight | kTextCenterY);
}
