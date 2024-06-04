/*
 * PlotsPresenter.cpp
 *
 *  Created on: Apr 23, 2019
 *      Author: petrstepanov
 */

#include "PlotsPresenter.h"
#include "PlotsView.h"
#include "../AbstractPresenter.h"
#include "../../model/Model.h"

#include <TGFileDialog.h>

PlotsPresenter::PlotsPresenter(PlotsView* view) : AbstractPresenter<Model, PlotsView>(view) {
	model = instantinateModel();
	onInitModel();
}

PlotsPresenter::~PlotsPresenter(){}

Model* PlotsPresenter::instantinateModel() {
	return Model::getInstance();
}

void PlotsPresenter::onInitModel() {
  // Connect slots to <- Model signals
  //model->Connect("spectraDeleted()", "FilesPresenter", this, "handleSpectraDeleted()");
  //model->Connect("spectrumDeleted(Int_t)", "FilesPresenter", this, "handleSpectrumDeleted(Int_t)");
  model->Connect("spectrumAdded(Spectrum*)", "FilesPresenter", this, "handleSpectrumAdded(Spectrum*)");
  //model->Connect("channelsNumberSet(Int_t)", "FilesPresenter", this, "handleChannelsNumberSet(Int_t)");
  //model->Connect("trimChannelsSet(TVector2*)", "FilesPresenter", this, "handleTrimChannelsSet(TVector2*)");
  //model->Connect("spectraNumberChanged(Int_t)", "FilesPresenter", this, "handleSpectraNumberChanged(Int_t)");
}

// Slots for <- Model signals
void PlotsPresenter::handleSpectrumAdded(Spectrum *spectrum) {
  view->addSpectrum(spectrum);
}

// Slots from View
