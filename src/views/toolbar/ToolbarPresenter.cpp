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

ClassImp(ToolbarPresenter);

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
	model->newProject();
}

void ToolbarPresenter::onOpenButtonClicked(){
	const char *filetypes[] = { Form("%s projects", Constants::applicationName), "*.root", 0, 0 };
	const TString* fileNamePath = UiHelper::getInstance()->openFileDialog(filetypes);
    model->readProjectFromFile(fileNamePath);
}

void ToolbarPresenter::onSaveButtonClicked(){
	// If no filename set do "Save As.." instead
	TString* filename = model->getProjectFilename();
	if (filename->Length()==0){
		onSaveAsButtonClicked();
		return;
	}
	// Otherwise save to existing filename
	model->saveProjectToFile(filename);
}

void ToolbarPresenter::onSaveAsButtonClicked(){
	const char *filetypes[] = { Form("%s project", Constants::applicationName), "*.root", 0, 0 };
	const TString* filename = UiHelper::getInstance()->saveFileDialog(filetypes);
	model->saveProjectToFile(filename);
}

void ToolbarPresenter::onCloseButtonClicked(){
	model->closeProject();
}

// Slots for signals from Model
void ToolbarPresenter::handleProjectCreated(){
	view->ShowFrame(view->saveButton);
	// view->saveButton->SetEnabled(kTRUE);
	view->ShowFrame(view->saveAsButton);
	// view->saveAsButton->SetEnabled(kTRUE);
	view->ShowFrame(view->closeButton);
	// view->closeButton->SetEnabled(kTRUE);
}

void ToolbarPresenter::handleProjectClosed(){
	view->HideFrame(view->saveButton);
	// view->saveButton->SetEnabled(kFALSE);
	view->HideFrame(view->saveAsButton);
	// view->saveAsButton->SetEnabled(kFALSE);
	view->HideFrame(view->closeButton);
	// view->closeButton->SetEnabled(kFALSE);
}
