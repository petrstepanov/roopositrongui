/*
 * FilesView.cpp
 *
 *  Created on: Apr 18, 2019
 *      Author: petrstepanov
 */

#include "FilesView.h"
#include "FilesPresenter.h"
#include <TGLabel.h>
#include <TGListBox.h>
#include <TGNumberEntry.h>
#include <TColor.h>
#include "../../util/UiHelper.h"
#include "../../util/Debug.h"

FilesView::FilesView(const TGWindow *w) :
		AbstractView<FilesPresenter>(w) {
	// Instantinate presenter
	presenter = instantinatePresenter();
	// Initialize UI elements

	// Build UIFilesView::onFileSelectionChanges
	initUI();
}

FilesView::~FilesView() {
}
;

FilesPresenter* FilesView::instantinatePresenter() {
	return new FilesPresenter(this);
}

void FilesView::initUI() {
	SetLayoutManager(new TGVerticalLayout(this));
	UiHelper::setDarkBackground(this);

	// Files list box
	TGLabel* filesNumberLabel = new TGLabel(this, "No files loaded");
	// filesNumberLabel->SetTextJustify(kTextLeft);
	UiHelper::setDarkBackground(filesNumberLabel);
	UiHelper::setDarkBackground(filesNumberLabel);
	AddFrame(filesNumberLabel, new TGLayoutHints(kLHintsNormal, 0, 0, Padding::dy, Padding::dy));
	filesListBox = new TGListBox(this);
	// UiHelper::setSolidBorder(filesListBox);

//	filesListBox->AddEntry("file1",0);
	AddFrame(filesListBox, new TGLayoutHints(kLHintsNormal | kFitWidth | kLHintsExpandY, 0, 0, Padding::dy, 0));

	// Files list buttons
	TGHorizontalFrame* horizohtalFrame = new TGHorizontalFrame(this);
	TGButton* addFilesButton = new TGTextButton(horizohtalFrame, "Add files...");
	removeFilesButton = new TGTextButton(horizohtalFrame, "Remove");
	horizohtalFrame->AddFrame(addFilesButton, new TGLayoutHints(kLHintsNormal | kLHintsExpandX, 0, Padding::dx / 2, 0, 0));
	horizohtalFrame->AddFrame(removeFilesButton, new TGLayoutHints(kLHintsNormal | kLHintsExpandX, Padding::dx / 2, 0, 0, 0));
	removeFilesButton->SetEnabled(kFALSE);
	AddFrame(horizohtalFrame, new TGLayoutHints(kLHintsNormal | kLHintsExpandX, 0, 0, Padding::dy, Padding::dy));
	UiHelper::setDarkBackground(horizohtalFrame);

	// Skip header lines
	TGCompositeFrame* skipLinesFrame = new TGHorizontalFrame(this);
	UiHelper::setDarkBackground(skipLinesFrame);
	TGLabel* skipLinesLabel = new TGLabel(skipLinesFrame, "Skip header lines");
	UiHelper::setDarkBackground(skipLinesLabel);
	TGNumberEntry* skipLinesNumberEntry = new TGNumberEntry(skipLinesFrame, 12, 5, -1, TGNumberFormat::kNESInteger, TGNumberFormat::kNEANonNegative,
			TGNumberFormat::kNELLimitMinMax, 0, 99);
	skipLinesFrame->AddFrame(skipLinesLabel, new TGLayoutHints(kLHintsLeft | kLHintsCenterY));
	skipLinesFrame->AddFrame(skipLinesNumberEntry, new TGLayoutHints(kLHintsRight | kLHintsCenterY));
	AddFrame(skipLinesFrame, new TGLayoutHints(kLHintsNormal | kLHintsExpandX, 0, 0, Padding::dy, Padding::dy));

	// Read channels
	TGCompositeFrame* readChannelsFrame = new TGHorizontalFrame(this);
	UiHelper::setDarkBackground(readChannelsFrame);
	TGLabel* readChannelsLabel = new TGLabel(readChannelsFrame, "Read channels");
	UiHelper::setDarkBackground(readChannelsLabel);
	readChannelsNumberEntry = new TGNumberEntry(readChannelsFrame, 8192, 5, -1, TGNumberFormat::kNESInteger, TGNumberFormat::kNEANonNegative,
			TGNumberFormat::kNELLimitMinMax, 0, 99999);
	readChannelsFrame->AddFrame(readChannelsLabel, new TGLayoutHints(kLHintsLeft | kLHintsCenterY));
	readChannelsFrame->AddFrame(readChannelsNumberEntry, new TGLayoutHints(kLHintsRight | kLHintsCenterY));
	AddFrame(readChannelsFrame, new TGLayoutHints(kLHintsNormal | kLHintsExpandX, 0, 0, Padding::dy, Padding::dy));

	// Trim data points
//	TGCompositeFrame* trimPointsFrame = new TGHorizontalFrame(this);
//	UiHelper::setDarkBackground(trimPointsFrame);
//	TGLabel* trimPointsLabel = new TGLabel(trimPointsFrame, "Trim data points");
//	UiHelper::setDarkBackground(trimPointsLabel);
//	TGLabel* dashLabel = new TGLabel(trimPointsFrame, "  -  ");
//	UiHelper::setDarkBackground(dashLabel);
//	TGNumberEntry* minChannelNumberEntry = new TGNumberEntry(trimPointsFrame, 1, 5, -1, TGNumberFormat::kNESInteger, TGNumberFormat::kNEANonNegative,
//			TGNumberFormat::kNELLimitMinMax, 1, 99999);
//	TGNumberEntry* maxChannelNumberEntry = new TGNumberEntry(trimPointsFrame, 8192, 5, -1, TGNumberFormat::kNESInteger, TGNumberFormat::kNEANonNegative,
//			TGNumberFormat::kNELLimitMinMax, 1, 99999);
//	trimPointsFrame->AddFrame(trimPointsLabel, new TGLayoutHints(kLHintsLeft | kLHintsCenterY));
//	trimPointsFrame->AddFrame(maxChannelNumberEntry, new TGLayoutHints(kLHintsRight | kLHintsCenterY));
//	trimPointsFrame->AddFrame(dashLabel, new TGLayoutHints(kLHintsRight | kLHintsCenterY));
//	trimPointsFrame->AddFrame(minChannelNumberEntry, new TGLayoutHints(kLHintsRight | kLHintsCenterY));
//	AddFrame(trimPointsFrame, new TGLayoutHints(kLHintsNormal | kLHintsExpandX, 0, 0, Padding::dy, Padding::dy));

	// Import Button
	TGTextButton* importSpectraButton = new TGTextButton(this, "Import Spectra");
	AddFrame(importSpectraButton, new TGLayoutHints(kLHintsNormal | kLHintsExpandX, 0, 0, Padding::dy, Padding::dy));
	importSpectraButton->SetEnabled(kFALSE);

	// Connect slots
	addFilesButton->Connect("Clicked()", "FilesPresenter", presenter, "onAddFilesClicked()");
	removeFilesButton->Connect("Clicked()", "FilesPresenter", presenter, "onRemoveFilesClicked()");
	importSpectraButton->Connect("Clicked()", "FilesPresenter", presenter, "onImportSpectraClicked()");
//	filesListBox->Connect("SelectionChanged()", "FilesView", this, "onFileSelectionChanged()");
	filesListBox->Connect("Selected(Int_t)", "FilesView", this, "onFileSelected(Int_t)");
}

void FilesView::onFileSelected(Int_t selectedNumber){
	if (selectedNumber >= 0){
		removeFilesButton->SetEnabled(kTRUE);
		return;
	}
	removeFilesButton->SetEnabled(kFALSE);
}

//void FilesView::onFileSelectionChanged(){
//	Debug("FilesView::onFileSelectionChanged");
//}
