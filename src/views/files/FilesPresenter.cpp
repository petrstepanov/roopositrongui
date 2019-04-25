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
#include "../../util/HistUtils.h"
#include "../../util/RootHelper.h"

#include <TRandom.h>
#include <TGFileDialog.h>
#include <TObjString.h>
#include <TSystem.h>
#include <TGMsgBox.h>

FilesPresenter::FilesPresenter(FilesView* view) : AbstractPresenter<Model, FilesView>(view) {
	model = instantinateModel();
	onInitModel();
}

FilesPresenter::~FilesPresenter() {
}

Model* FilesPresenter::instantinateModel() {
	return Model::getInstance();
}

void FilesPresenter::onInitModel() {
	// Connect Model signals to slots
	model->Connect("spectraDeleted()", "FilesPresenter", this, "handleSpectraDeleted()");
	model->Connect("spectrumDeleted(Int_t)", "FilesPresenter", this, "handleSpectrumDeleted(Int_t)");
	model->Connect("spectrumAdded(Spectrum*)", "FilesPresenter", this, "handleSpectrumAdded(Spectrum*)");
	model->Connect("channelsNumberSet(Int_t)", "FilesPresenter", this, "handleChannelsNumberSet(Int_t)");

	// Update ui with default model values
	// Reflect list of spectra
	TObjArray* spectra = model->getSpectra();
	for (UInt_t i = 0; i < spectra->GetSize(); i++){
		if (Spectrum* spectrum = dynamic_cast<Spectrum*>(spectra->At(i))){
			handleSpectrumAdded(spectrum);
		}
	}

	// Set trimming limits
	handleChannelsNumberSet(model->getNumberOfChannels());
}

// Slots from View
void FilesPresenter::onAddFilesClicked() {
	// Get new spectra fileInfolenames from fileInfole dilog
	const char *filetypes[] = { "Maestro spectra", "*.Spe", "All files", "*", 0, 0 };
	TList* newFilenamesList = UiHelper::getInstance()->getFilesFromDialog(filetypes);
	if (newFilenamesList->GetSize()==0) return;

	// See if import limits were changed. Delete existing model spectra and mark for re-import
	// Int_t skipLines = atoi(view->skipLinesNumberEntry->GetNumberEntry()->GetText());
	// Int_t readLines = atoi(view->readChannelsNumberEntry->GetNumberEntry()->GetText());

	// Iterate through new filenames and add them to model
	TIter next(newFilenamesList);
	while (TObject *obj = next()){
		if (TObjString* objString = dynamic_cast<TObjString*>(obj)){
			// Create unique identifier for new spectrum
			Int_t intUID = RootHelper::getInstance()->getRandomInt();
			Spectrum* newSpectrum = new Spectrum(intUID);
			const char* fileNamePath = objString->GetString().Data();
			// Set spectrum name
			newSpectrum->filename = new TString(gSystem->BaseName(fileNamePath));
			// Import histogram
			newSpectrum->histogram = HistUtils::importTH1I(fileNamePath);
			// Add spectrum if number of channels is consistent
			if (checkImportSuccessful(newSpectrum->histogram)){
				model->addSpectrum(newSpectrum);
			}
			else {
				TString message = TString::Format("Spectrum %s has incorrect channels number", newSpectrum->filename->Data());
				UiHelper::getInstance()->showOkDialog(message.Data(), EMsgBoxIcon::kMBIconStop);
			}
		}
	}
}

Bool_t FilesPresenter::checkImportSuccessful(TH1* histogram){
	if (histogram == nullptr) return kFALSE;
	if (model->getNumberOfChannels() == 0){
		model->setNumberOfChannels(histogram->GetXaxis()->GetNbins());
		return kTRUE;
	}
	return model->getNumberOfChannels() == histogram->GetXaxis()->GetNbins();
}

void FilesPresenter::onRemoveFilesClicked() {
	Int_t selectedId = view->filesListBox->GetSelected();
	model->deleteSpectrum(selectedId);
}

// Slots from Model

void FilesPresenter::handleSpectrumAdded(Spectrum* spectrum){
	view->filesListBox->AddEntry(spectrum->filename->Data(), spectrum->id);
	view->filesListBox->Layout();
	view->importSpectraButton->SetEnabled(kTRUE);
}

void FilesPresenter::handleChannelsNumberSet(Int_t channels){
	if (channels == 0){
		view->minChannelNumberEntry->SetState(kFALSE);
		view->maxChannelNumberEntry->SetState(kFALSE);
		return;
	}
	view->minChannelNumberEntry->SetState(kTRUE);
	view->maxChannelNumberEntry->SetState(kTRUE);
	view->minChannelNumberEntry->SetLimitValues(1, channels);
	view->maxChannelNumberEntry->SetLimitValues(1, channels);
}

void FilesPresenter::handleSpectrumDeleted(Int_t id){
	view->filesListBox->RemoveEntry(id);
	if (model->getSpectra()->GetSize()==0){
		view->importSpectraButton->SetEnabled(kFALSE);
	}
}

void FilesPresenter::handleSpectraDeleted(){
	view->filesListBox->RemoveAll();
}
