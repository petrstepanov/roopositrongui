/*
 * FilesView.cpp
 *
 *  Created on: Apr 18, 2019
 *      Author: petrstepanov
 */

#include "FilesView.h"
#include "FilesPresenter.h"
#include "TGLabel.h"
#include "TGListBox.h"
#include "../../util/UiHelper.h"

FilesView::FilesView(const TGWindow *w) : AbstractView<FilesPresenter>(w){
	// Instantinate presenter
	presenter = instantinatePresenter();
	// Initialize UI elements

	// Build UI
	initUI();
}

FilesView::~FilesView(){};

FilesPresenter* FilesView::instantinatePresenter(){
    return new FilesPresenter(this);
}

void FilesView::initUI(){
	SetLayoutManager(new TGVerticalLayout(this));
    UiHelper::setDarkBackground(this);

	// Layout UI elements and attach signals
	TGLabel* filesNumberLabel = new TGLabel(this, "No files loaded");
    UiHelper::setDarkBackground(filesNumberLabel);
	AddFrame(filesNumberLabel, new TGLayoutHints(kLHintsLeft | kLHintsTop, 0, 0, Padding::dy, Padding::dy));

	TGListBox* filesListBox = new TGListBox(this);
	AddFrame(filesListBox, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX | kLHintsExpandY, 0, 0, Padding::dy, Padding::dy));

	TGHorizontalFrame* horizohtalFrame = new TGHorizontalFrame(this);
	TGButton* addFilesButton = new TGTextButton(horizohtalFrame, "Add files...");
	TGButton* removeFilesButton = new TGTextButton(horizohtalFrame, "Remove");
	horizohtalFrame->AddFrame(addFilesButton, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX, 0, Padding::dx/2, 0, 0));
	horizohtalFrame->AddFrame(removeFilesButton, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX, Padding::dx/2, 0, 0, 0));
	AddFrame(horizohtalFrame, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX, 0, 0, Padding::dy, Padding::dy));
    UiHelper::setDarkBackground(horizohtalFrame);

	// Connect slots
	addFilesButton->Connect("Clicked()", "FilesPresenter", presenter, "onAddFilesClicked()");
	removeFilesButton->Connect("Clicked()", "FilesPresenter", presenter, "onRemoveFilesClicked()");
}
