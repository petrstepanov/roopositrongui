/*
 * Spectrum.h
 *
 *  Created on: Apr 16, 2019
 *      Author: petrstepanov
 */

#ifndef SRC_MODEL_BRANCHES_SPECTRUM_H_
#define SRC_MODEL_BRANCHES_SPECTRUM_H_

#include <TObject.h>
#include <TH1F.h>
#include <RooDataHist.h>

class Spectrum : public TObject {

private:
	TString filename;
	TH1F* histogram;              // ROOT histogram
	RooDataHist* dataHistogram;   // RooFit histogram
	Double_t integral;            // total counts
	Int_t numberOfBins;
	Int_t binWithMinimumCount;    // bin number with minimum value in the range
	Int_t binWithMaximumCount;    // bin number with maximum value in the range
	Double_t minimumCount;        // minimum count across all bins
	Double_t maximumCount;        // maximum count across all bins
	Double_t averageBackground;
	RooAbsPdf* model;
	RooAbsPdf* resolutionFunction;

	ClassDef(Spectrum,1)  //Event structure
};

#endif /* SRC_MODEL_BRANCHES_SPECTRUM_H_ */
