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

ProjectPresenter::ProjectPresenter(ProjectView* view) : AbstractPresenter<ProjectModel, ProjectView>(view) {
	model = instantinateModel();
	onInitModel();
}

ProjectPresenter::~ProjectPresenter(){}

ProjectModel* ProjectPresenter::instantinateModel() {
	return Model::getInstance()->getProjectModel();
}

// Slots from Model
void ProjectPresenter::onInitModel() {
}

// Slots from View
