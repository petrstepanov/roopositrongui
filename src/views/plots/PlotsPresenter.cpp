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

// Slots from Model
void PlotsPresenter::onInitModel() {
}

// Slots from View
