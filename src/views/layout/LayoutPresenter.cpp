/*
 * LayoutPresenter.cpp
 *
 *  Created on: Apr 26, 2019
 *      Author: petrstepanov
 */

#include "LayoutPresenter.h"
#include "LayoutView.h"
#include "../AbstractPresenter.h"
#include "../../model/Model.h"
#include "../../util/UiHelper.h"
#include "../project/ProjectView.h"

#include <TGFileDialog.h>

LayoutPresenter::LayoutPresenter(LayoutView* view) : AbstractPresenter<Model, LayoutView>(view) {
	model = instantinateModel();
	onInitModel();
}

LayoutPresenter::~LayoutPresenter(){}

Model* LayoutPresenter::instantinateModel() {
	return Model::getInstance();
}

void LayoutPresenter::onInitModel() {
    // Conect slots to <- Model signals
    model->Connect("projectCreated()", "LayoutPresenter", this, "handleProjectCreated()");
    model->Connect("projectClosed()", "LayoutPresenter", this, "handleProjectClosed()");
}

// Slots for <- Model Signals
void LayoutPresenter::handleProjectCreated(){
	// Remove current ProjectView if any
	view->createNewProjectView();
}

void LayoutPresenter::handleProjectClosed(){
	view->removeProjectView();
}
