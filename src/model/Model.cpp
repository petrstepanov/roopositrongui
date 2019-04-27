/*
 * Model.cpp
 *
 *  Created on: Apr 16, 2019
 *      Author: petrstepanov
 */

#include "Model.h"
#include "../util/Debug.h"
#include "../util/StringUtils.h"
#include <TUUID.h>
#include <TFile.h>
#include <TTree.h>

Model* Model::instance = 0;

Model::Model() {
	projectFilename = new TString("");
	projectModifiedAfterSave = kFALSE;
	projectModel = nullptr;
}

Model::~Model() {
}

Model* Model::getInstance(){
	if (instance == nullptr){
		instance = new Model();
	}
	return instance;
}

// Project
TString* Model::getProjectFilename(){
	return projectFilename;
};

Bool_t Model::isProjectModifiedAfterSave(){
	return isProjectModifiedAfterSave();
};

Bool_t Model::saveProjectToFile(const TString* filename){
	// Do nothing if filename is empty
	if (StringUtils::isEmpty(filename)){
		return kFALSE;
	}
	// TODO: Do save logic
	TFile f(filename->Data(),"RECREATE");
	// create a ROOT Tree
	TTree t4("t4","A Tree with ProjectModel");
	// create a pointer to an Event object
	// create two branches, split one
	t4.Branch("projectmodel_branch", "ProjectModel", projectModel, 16000,2);
	t4.Branch("projectmodel_not_split", "ProjectModel", projectModel, 16000,0);
	t4.Fill();
	// Write the file header
	f.Write();

	#ifdef USEDEBUG
		t4.Print();
	#endif

	// Notify presenters about new filename
	if (*filename != *projectFilename){
		*projectFilename = filename->Data();
		projectSaved(projectFilename);
	}
	return kTRUE;
}

Bool_t Model::readProjectFromFile(const TString* filename){
	projectCreated();
	return kTRUE;
}

void Model::newProject(){
	projectModel = new ProjectModel();
	projectCreated();
}

void Model::closeProject(){
	projectClosed();
}

// Spectra manipulation
void Model::deleteSpectra(){
	projectModel->spectra->Delete();
	spectraDeleted();
	// Signals
	setNumberOfChannels(0);
	spectraNumberChanged(0);
}

void Model::deleteSpectrum(Int_t id){
	TObject* object = projectModel->spectra->FindObject(Form("%d", id));
	if (object){
		projectModel->spectra->Remove(object);
		spectrumDeleted(id);
		// Signal
		projectModel->spectra->Print("V");
		spectraNumberChanged(projectModel->spectra->GetEntriesFast());
	}
}

void Model::addSpectrum(Spectrum* spectrum){
	projectModel->spectra->Add(spectrum);
	// Signals
	spectrumAdded(spectrum);
	spectraNumberChanged(projectModel->spectra->GetEntriesFast());
}

TObjArray* Model::getSpectra(){
	return projectModel->spectra;
}

// Number of channels
Int_t Model::getNumberOfChannels(){
	return projectModel->numberOfChannels;
}

void Model::setNumberOfChannels(Int_t channels){
	projectModel->numberOfChannels = channels;
	channelsNumberSet(channels);
}

// Spectra trim
void Model::setTrimChannels(Int_t minChannel, Int_t maxChannel){
	if ((minChannel >= 1 && minChannel <= projectModel->numberOfChannels) && //
		(maxChannel >= 1 && maxChannel <= projectModel->numberOfChannels)){
		projectModel->minTrimChannel = minChannel;
		projectModel->maxTrimChannel = maxChannel;
		// TODO: update RooRealVar channels

		TVector2* vector = new TVector2(projectModel->minTrimChannel, projectModel->maxTrimChannel);
		trimChannelsSet(vector);
	}
}

Int_t Model::getMinTrimChannel(){
	return projectModel->minTrimChannel;
}

Int_t Model::getMaxTrimChannel(){
	return projectModel->maxTrimChannel;
}

// Signals
void Model::channelsNumberSet(Int_t channels){
	Emit("channelsNumberSet(Int_t)", channels);
}

void Model::spectraNumberChanged(Int_t spectra){
	Emit("spectraNumberChanged(Int_t)", spectra);
}

void Model::projectCreated(){
	Emit("projectCreated()");
}

void Model::projectClosed(){
	Emit("projectClosed()");
}

void Model::projectSaved(TString* filename){
	Emit("projectSaved(TString*)", filename);
}

void Model::spectraDeleted(){
	Emit("spectraDeleted()");
}

void Model::spectrumDeleted(Int_t id){
	Emit("spectrumDeleted(Int_t)", id);
}

void Model::spectrumAdded(Spectrum* spectrum){
	Emit("spectrumAdded(Spectrum*)", spectrum);
}

void Model::trimChannelsSet(TVector2* vector){
	Emit("trimChannelsSet(TVector2*)", vector);
}

//
