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

Bool_t Model::saveProjectToFile(TString* filename){
	// Do nothing if filename is empty
	if (StringUtils::isEmpty(filename)){
		return kFALSE;
	}
	// TODO: Do save logic

	// Notify presenters about new filename
	if (*filename != *projectFilename){
		projectFilename = filename;
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
	// When deleting spectra reset number of channels
	setNumberOfChannels(0);
}

void Model::deleteSpectrum(Int_t id){
	TObject* object = projectModel->spectra->FindObject(Form("%d", id));
	if (object){
		projectModel->spectra->Remove(object);
		spectrumDeleted(id);
	}
}

void Model::addSpectrum(Spectrum* spectrum){
	projectModel->spectra->Add(spectrum);
	spectrumAdded(spectrum);
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

// Signals
void Model::channelsNumberSet(Int_t channels){
	Emit("channelsNumberSet(Int_t)", channels);
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

//
