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

private:
	Double_t channelWidth;
	Int_t skipLinesSpectrum;
	Int_t maxSpectrumChannel;
	Int_t minTrimChannel;
	Int_t maxTrimChannel;
	TObjArray* spectra;

	ClassDef(ProjectModel, 1)
};

#endif /* SRC_MODEL_BRANCHES_PROJECTMODEL_H_ */
