/*
 * ProjectPresenter.cpp
 *
 *  Created on: Apr 17, 2019
 *      Author: petrstepanov
 */

#include "ProjectPresenter.h"
#include "ProjectView.h"
#include "../AbstractPresenter.h"
#include "../../model/Model.h"

#include <TGFileDialog.h>

ProjectPresenter::ProjectPresenter(ProjectView* view) : AbstractPresenter<Model, ProjectView>(view) {
	model = instantinateModel();
	onInitModel();
}

ProjectPresenter::~ProjectPresenter(){}

Model* ProjectPresenter::instantinateModel() {
	return Model::getInstance();
}

// Slots from Model
void ProjectPresenter::onInitModel() {
}

// Slots from View
