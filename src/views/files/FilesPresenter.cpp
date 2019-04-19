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

#include <TGFileDialog.h>

FilesPresenter::FilesPresenter(FilesView* view) : AbstractPresenter<Model, FilesView>(view) {
	model = instantinateModel();
	onInitModel();
}

FilesPresenter::~FilesPresenter(){}

Model* FilesPresenter::instantinateModel() {
	return Model::getInstance();
}

// Slots from Model
void FilesPresenter::onInitModel() {
}

// Slots from View
void FilesPresenter::onAddFilesClicked(){

}

void FilesPresenter::onRemoveFilesClicked(){

}
