/*
 * FilesPresenter.cpp
 *
 *  Created on: Apr 18, 2019
 *      Author: petrstepanov
 */

#include "FilesPresenter.h"
#include "FilesView.h"
#include "../AbstractPresenter.h"
#include "../../model/Model.h"
#include "../../model/branches/Spectrum.h"
#include "../../util/UiHelper.h"
#include "../../util/FileUtils.h"

#include <TRandom.h>
#include <TGFileDialog.h>
#include <TObjString.h>
#include <TSystem.h>
#include <TGMsgBox.h>

FilesPresenter::FilesPresenter(FilesView *view) :
    AbstractPresenter<Model, FilesView>(view) {
  model = instantinateModel();
  onInitModel();
}

FilesPresenter::~FilesPresenter() {
}

Model* FilesPresenter::instantinateModel() {
  return Model::getInstance();
}

void FilesPresenter::onInitModel() {
  // Connect slots to <- Model signals
  model->Connect("spectraDeleted()", "FilesPresenter", this, "handleSpectraDeleted()");
  model->Connect("spectrumDeleted(Int_t)", "FilesPresenter", this, "handleSpectrumDeleted(Int_t)");
  model->Connect("spectrumAdded(Spectrum*)", "FilesPresenter", this, "handleSpectrumAdded(Spectrum*)");
  model->Connect("channelsNumberSet(Int_t)", "FilesPresenter", this, "handleChannelsNumberSet(Int_t)");
  model->Connect("trimChannelsSet(TVector2*)", "FilesPresenter", this, "handleTrimChannelsSet(TVector2*)");
  model->Connect("spectraNumberChanged(Int_t)", "FilesPresenter", this, "handleSpectraNumberChanged(Int_t)");

  // Update ui with default model values
  // Reflect list of spectra
  TObjArray *spectra = model->getSpectra();
  for (UInt_t i = 0; i < spectra->GetSize(); i++) {
    if (Spectrum *spectrum = dynamic_cast<Spectrum*>(spectra->At(i))) {
      handleSpectrumAdded(spectrum);
    }
  }

  // Set trimming limits
  handleChannelsNumberSet(model->getNumberOfChannels());
  TVector2 *trimChannels = new TVector2(model->getMinTrimChannel(), model->getMaxTrimChannel());
  handleTrimChannelsSet(trimChannels);

  // Enable/disable trim button
  view->trimSpectraButton->SetEnabled(model->getSpectra()->GetSize() > 0);
}

// Slots from View
void FilesPresenter::onAddFilesClicked() {
  // Get new spectra fileInfolenames from fileInfole dilog
  const char *filetypes[] = { "Maestro spectra", "*.Spe", "All files", "*", 0, 0 };
  TList *newFilenamesList = UiHelper::getInstance()->openFilesDialog(filetypes);
  if (newFilenamesList->GetSize() == 0)
    return;

  // See if import limits were changed. Delete existing model spectra and mark for re-import
  // Int_t skipLines = atoi(view->skipLinesNumberEntry->GetNumberEntry()->GetText());
  // Int_t readLines = atoi(view->readChannelsNumberEntry->GetNumberEntry()->GetText());

  // Iterate through new filenames and add them to model
  TIter next(newFilenamesList);
  while (TObject *obj = next()) {
    if (TObjString *objString = dynamic_cast<TObjString*>(obj)) {

      // Create unique integer identifier for new spectrum
      TString spectrumPath = objString->GetString().Data();
      Spectrum *newSpectrum = new Spectrum(spectrumPath);

      // Do not ensure the same channels because we fit with time axis
      model->addSpectrum(newSpectrum);
      // Ensure spectrum has same number of channels.
      // if (checkImportSuccessful(newSpectrum->histogram)) {
      //   model->addSpectrum(newSpectrum);
      // } else {
      //   TString message = TString::Format("Spectrum %s has incorrect number of channels.", newSpectrum->filename->Data());
      //   UiHelper::getInstance()->showOkDialog(message.Data(), EMsgBoxIcon::kMBIconStop);
      // }
    }
  }
}

Bool_t FilesPresenter::checkImportSuccessful(TH1 *histogram) {
  if (histogram == nullptr)
    return kFALSE;
  if (model->getNumberOfChannels() == 0) {
    model->setNumberOfChannels(histogram->GetXaxis()->GetNbins());
    return kTRUE;
  }
  return model->getNumberOfChannels() == histogram->GetXaxis()->GetNbins();
}

void FilesPresenter::onRemoveFilesClicked() {
  Int_t selectedId = view->filesListBox->GetSelected();
  model->deleteSpectrum(selectedId);
}

void FilesPresenter::onTrimSpectraClicked() {
  Int_t minChannel = view->minChannelNumberEntry->GetNumberEntry()->GetNumber();
  Int_t maxChannel = view->maxChannelNumberEntry->GetNumberEntry()->GetNumber();
  model->setTrimChannels(minChannel, maxChannel);
}

// Slots for <- Model signals
void FilesPresenter::handleSpectrumAdded(Spectrum *spectrum) {
  PathComponents pc = FileUtils::parseFilePath(spectrum->getFilePath());
  // List Box only accepts
  // std::string id_std_string = spectrum.id;
  // listBoxIdVector.push_back(id_std_string);
  // TODO: fix
  view->filesListBox->AddEntry(pc.base.Data(), 1);
  view->filesListBox->Layout();
  view->trimSpectraButton->SetEnabled(kTRUE);
}

void FilesPresenter::handleChannelsNumberSet(Int_t channels) {
  if (channels == 0) {
    view->minChannelNumberEntry->SetState(kFALSE);
    view->maxChannelNumberEntry->SetState(kFALSE);
    return;
  }
  view->minChannelNumberEntry->SetState(kTRUE);
  view->maxChannelNumberEntry->SetState(kTRUE);
  view->minChannelNumberEntry->SetLimitValues(1, channels);
  view->maxChannelNumberEntry->SetLimitValues(1, channels);
}

void FilesPresenter::handleSpectraNumberChanged(Int_t number) {
  switch (number) {
  case 0:
    view->filesNumberLabel->SetText("No files loaded");
    break;
  case 1:
    view->filesNumberLabel->SetText("1 file loaded");
    break;
  default:
    view->filesNumberLabel->SetText(Form("%d files loaded", number));
  }
}

void FilesPresenter::handleSpectrumDeleted(Int_t id) {
  view->filesListBox->RemoveEntry(id);
  if (model->getSpectra()->GetSize() == 0) {
    view->trimSpectraButton->SetEnabled(kFALSE);
  }
}

void FilesPresenter::handleSpectraDeleted() {
  view->filesListBox->RemoveAll();
}

void FilesPresenter::handleTrimChannelsSet(TVector2 *vector) {
  view->minChannelNumberEntry->GetNumberEntry()->SetNumber((double) vector->X());
  view->maxChannelNumberEntry->GetNumberEntry()->SetNumber((double) vector->Y());
}
