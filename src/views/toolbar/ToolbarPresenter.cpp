/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ToolbarPresenter.cpp
 * Author: petrstepanov
 * 
 * Created on October 6, 2017, 6:31 PM
 */

#include "ToolbarPresenter.h"
#include "ToolbarView.h"
#include "../AbstractPresenter.h"

#include "../../resources/Constants.h"
#include "../../model/Model.h"
#include "../../util/Debug.h"
#include "../../util/UiHelper.h"


#include <TGFileDialog.h>

ToolbarPresenter::ToolbarPresenter(ToolbarView* view) : AbstractPresenter<Model, ToolbarView>(view) {
	model = instantinateModel();
	onInitModel();
}

Model* ToolbarPresenter::instantinateModel() {
	return Model::getInstance();
}

void ToolbarPresenter::onInitModel() {
	// Connect Model signals to slots
	model->Connect("projectClosed()", "ToolbarPresenter", this, "handleProjectClosed()");
	model->Connect("projectCreated()", "ToolbarPresenter", this, "handleProjectCreated()");
}

// Slots for signals from View
void ToolbarPresenter::onNewButtonClicked(){
	Debug("ToolbarPresenter::onNewButtonClicked");
	model->newProject();
}

void ToolbarPresenter::onOpenButtonClicked(){
	const char *filetypes[] = { Form("%s projects", Constants::applicationName), "*.root", 0, 0 };
	const TString* fileNamePath = UiHelper::getInstance()->getFileFromDialog(filetypes);
    model->readProjectFromFile(fileNamePath);
}

void ToolbarPresenter::onSaveButtonClicked(){
	TString* filename = model->getProjectFilename();
	if (filename->Length()==0){
		onSaveAsButtonClicked();
		return;
	}
	model->saveProjectToFile(filename);
}

void ToolbarPresenter::onSaveAsButtonClicked(){
	TString* filename = model->getProjectFilename();
	model->saveProjectToFile(filename);
}

void ToolbarPresenter::onCloseButtonClicked(){
	model->closeProject();
}

// Slots for signals from Model
void ToolbarPresenter::handleProjectCreated(){
	Debug("ToolbarPresenter::handleProjectCreated");
	view->saveButton->SetEnabled(kTRUE);
	view->saveAsButton->SetEnabled(kTRUE);
	view->closeButton->SetEnabled(kTRUE);
}

void ToolbarPresenter::handleProjectClosed(){
	Debug("ToolbarPresenter::handleProjectClosed");
	view->saveButton->SetEnabled(kFALSE);
	view->saveAsButton->SetEnabled(kFALSE);
	view->closeButton->SetEnabled(kFALSE);
}
