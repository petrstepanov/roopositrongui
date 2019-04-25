/*
 * ProjectModel.h
 *
 *  Created on: Apr 17, 2019
 *      Author: petrstepanov
 */

#ifndef SRC_MODEL_BRANCHES_PROJECTMODEL_H_
#define SRC_MODEL_BRANCHES_PROJECTMODEL_H_

#include <RtypesCore.h>
#include <TObject.h>
#include <TObjArray.h>
#include <RooRealVar.h>

class ProjectModel : public TObject {
public:
	ProjectModel();
	virtual ~ProjectModel();

	Int_t minTrimChannel = 1;
	Int_t maxTrimChannel = 8192;
	Int_t numberOfChannels = 0; // Originally is zero;
	TObjArray* spectra;
	RooRealVar* channels;

	ClassDef(ProjectModel, 1)
};

#endif /* SRC_MODEL_BRANCHES_PROJECTMODEL_H_ */
