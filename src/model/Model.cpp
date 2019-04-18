/*
 * Model.cpp
 *
 *  Created on: Apr 16, 2019
 *      Author: petrstepanov
 */

#include "Model.h"
#include "../util/Debug.h"

Model* Model::instance = 0;

Model::Model() {
	projectFilename = new TString();
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

void Model::newProject(){
	Debug("Model::newProject");
	projectCreated();
}

Bool_t Model::saveProjectToFile(TString* filename){
	Debug("Model::saveProjectToFile", filename->Data());
	projectSaved(filename);
	return kTRUE;
}

Bool_t Model::readProjectFromFile(TString* filename){
	Debug("Model::readFromFile", filename->Data());
	projectCreated();
	return kTRUE;
}

void Model::closeProject(){
	projectClosed();
}

// Signals
void Model::projectCreated(){
	Emit("projectCreated()");
}

void Model::projectClosed(){
	Emit("projectClosed()");
}

void Model::projectSaved(TString* filename){
	Emit("projectSaved(TString*)");
}

// Setters and getters
TString* Model::getProjectFilename(){
	return projectFilename;
};

Bool_t Model::isProjectModifiedAfterSave(){
	return isProjectModifiedAfterSave();
};
