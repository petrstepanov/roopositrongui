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
  // Initialize UI elements
  initUI();
  // Instantinate presenter
  presenter = instantinatePresenter();
  connectSlots();
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
  filesNumberLabel = new TGLabel(this, "No files loaded");
  // filesNumberLabel->SetTextJustify(kTextLeft);
  UiHelper::setDarkBackground(filesNumberLabel);
  UiHelper::setDarkBackground(filesNumberLabel);
  AddFrame(filesNumberLabel, new TGLayoutHints(kLHintsNormal | kLHintsExpandX, 0, 0, Padding::dy, Padding::dy));
  filesListBox = new TGListBox(this);
  // UiHelper::setSolidBorder(filesListBox);

//	filesListBox->AddEntry("file1",0);
  AddFrame(filesListBox, new TGLayoutHints(kLHintsNormal | kFitWidth | kLHintsExpandY, 0, 0, Padding::dy, Padding::dy));

  // Files list buttons
  TGHorizontalFrame *horizohtalFrame = new TGHorizontalFrame(this);
  addFilesButton = new TGTextButton(horizohtalFrame, "Import files...");
  removeFilesButton = new TGTextButton(horizohtalFrame, "Remove");
  horizohtalFrame->AddFrame(removeFilesButton, new TGLayoutHints(kLHintsNormal | kLHintsExpandX, 0, Padding::dx / 2, 0, 0));
  horizohtalFrame->AddFrame(addFilesButton, new TGLayoutHints(kLHintsNormal | kLHintsExpandX, Padding::dx / 2, 0, 0, 0));
  removeFilesButton->SetEnabled(kFALSE);
  AddFrame(horizohtalFrame, new TGLayoutHints(kLHintsNormal | kLHintsExpandX, 0, 0, Padding::dy, Padding::dy));
  UiHelper::setDarkBackground(horizohtalFrame);

  // Skip header lines
//	TGCompositeFrame* skipLinesFrame = new TGHorizontalFrame(this);
//	UiHelper::setDarkBackground(skipLinesFrame);
//	TGLabel* skipLinesLabel = new TGLabel(skipLinesFrame, "Skip header lines");
//	UiHelper::setDarkBackground(skipLinesLabel);
//	TGNumberEntry* skipLinesNumberEntry = new TGNumberEntry(skipLinesFrame, 12, 5, -1, TGNumberFormat::kNESInteger, TGNumberFormat::kNEANonNegative,
//			TGNumberFormat::kNELLimitMinMax, 0, 99);
//	skipLinesFrame->AddFrame(skipLinesLabel, new TGLayoutHints(kLHintsLeft | kLHintsCenterY));
//	skipLinesFrame->AddFrame(skipLinesNumberEntry, new TGLayoutHints(kLHintsRight | kLHintsCenterY));
//	AddFrame(skipLinesFrame, new TGLayoutHints(kLHintsNormal | kLHintsExpandX, 0, 0, Padding::dy, Padding::dy));
//
//	// Read channels
//	TGCompositeFrame* readChannelsFrame = new TGHorizontalFrame(this);
//	UiHelper::setDarkBackground(readChannelsFrame);
//	TGLabel* readChannelsLabel = new TGLabel(readChannelsFrame, "Read channels");
//	UiHelper::setDarkBackground(readChannelsLabel);
//	readChannelsNumberEntry = new TGNumberEntry(readChannelsFrame, 8192, 5, -1, TGNumberFormat::kNESInteger, TGNumberFormat::kNEANonNegative,
//			TGNumberFormat::kNELLimitMinMax, 0, 99999);
//	readChannelsFrame->AddFrame(readChannelsLabel, new TGLayoutHints(kLHintsLeft | kLHintsCenterY));
//	readChannelsFrame->AddFrame(readChannelsNumberEntry, new TGLayoutHints(kLHintsRight | kLHintsCenterY));
//	AddFrame(readChannelsFrame, new TGLayoutHints(kLHintsNormal | kLHintsExpandX, 0, 0, Padding::dy, Padding::dy));

// Trim data points
  TGLabel *trimPointsLabel = new TGLabel(this, "Trim channels (will clear existing fits)");
  UiHelper::setDarkBackground(trimPointsLabel);
  AddFrame(trimPointsLabel, new TGLayoutHints(kLHintsNormal, 0, 0, 3 * Padding::dy, Padding::dy));

  TGCompositeFrame *trimPointsFrame = new TGHorizontalFrame(this);
  UiHelper::setDarkBackground(trimPointsFrame);
  minChannelNumberEntry = new TGNumberEntry(trimPointsFrame, 1, 5, -1, TGNumberFormat::kNESInteger, TGNumberFormat::kNEANonNegative,
      TGNumberFormat::kNELLimitMinMax, 1, 99999);
  TGLabel *dashLabel = new TGLabel(trimPointsFrame, "  -  ");
  UiHelper::setDarkBackground(dashLabel);
  maxChannelNumberEntry = new TGNumberEntry(trimPointsFrame, 8192, 5, -1, TGNumberFormat::kNESInteger, TGNumberFormat::kNEANonNegative,
      TGNumberFormat::kNELLimitMinMax, 1, 99999);
  trimSpectraButton = new TGTextButton(trimPointsFrame, "Trim");
  trimSpectraButton->SetEnabled(kFALSE);

  trimPointsFrame->AddFrame(minChannelNumberEntry, new TGLayoutHints(kLHintsLeft | kLHintsCenterY));
  trimPointsFrame->AddFrame(dashLabel, new TGLayoutHints(kLHintsLeft | kLHintsCenterY));
  trimPointsFrame->AddFrame(maxChannelNumberEntry, new TGLayoutHints(kLHintsLeft | kLHintsCenterY));
  trimPointsFrame->AddFrame(trimSpectraButton, new TGLayoutHints(kLHintsLeft | kLHintsCenterY | kLHintsExpandX, Padding::dx));
  AddFrame(trimPointsFrame, new TGLayoutHints(kLHintsNormal | kLHintsExpandX, 0, 0, Padding::dy, Padding::dy));
}

void FilesView::connectSlots() {
  addFilesButton->Connect("Clicked()", "FilesPresenter", presenter, "onAddFilesClicked()");
  removeFilesButton->Connect("Clicked()", "FilesPresenter", presenter, "onRemoveFilesClicked()");
  trimSpectraButton->Connect("Clicked()", "FilesPresenter", presenter, "onTrimSpectraClicked()");
  filesListBox->Connect("Selected(Int_t)", "FilesView", this, "onFileSelected(Int_t)");
  filesListBox->Connect("SelectionChanged()", "FilesView", this, "onSelectionChanged()");
}

// Slots
void FilesView::onFileSelected(Int_t selectedNumber) {
   removeFilesButton->SetEnabled(kTRUE);
}

void FilesView::onSelectionChanged() {
  if (filesListBox->GetSelected() == -1){
    removeFilesButton->SetEnabled(kFALSE);
  }
  else {
    removeFilesButton->SetEnabled(kTRUE);
  }
//  if (selectedNumber >= 0) {
//    removeFilesButton->SetEnabled(kTRUE);
//    return;
//  }
//  removeFilesButton->SetEnabled(kFALSE);
}
