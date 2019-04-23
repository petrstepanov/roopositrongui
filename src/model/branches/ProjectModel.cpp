/*
 * ProjectModel.cpp
 *
 *  Created on: Apr 17, 2019
 *      Author: petrstepanov
 */

#include "ProjectModel.h"

ProjectModel::ProjectModel() {
	channelWidth = 0.006186;
	skipLines = 12;
	readLines = 8192;
//	minTrimChannel = 1;
//	maxTrimChannel = 8192;
	spectra = new TObjArray();
}

ProjectModel::~ProjectModel() {}

