/*
 * ProjectModel.cpp
 *
 *  Created on: Apr 17, 2019
 *      Author: petrstepanov
 */

#include "ProjectModel.h"

ProjectModel::ProjectModel() {
	minTrimChannel = 1;
	maxTrimChannel = 8192;
	spectra = new TObjArray();
	channels = new RooRealVar("channels", "Channels axis", minTrimChannel-1, maxTrimChannel, "ch");
}

ProjectModel::~ProjectModel() {}

