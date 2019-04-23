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

class ProjectModel : public TObject {
public:
	ProjectModel();
	virtual ~ProjectModel();

	Double_t channelWidth;
	Int_t skipLines;
	Int_t readLines;
//	Int_t maxSpectrumChannel;
	TObjArray* spectra;

	ClassDef(ProjectModel, 1)
};

#endif /* SRC_MODEL_BRANCHES_PROJECTMODEL_H_ */
