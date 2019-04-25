/*
 * Spectrum.h
 *
 *  Created on: Apr 23, 2019
 *      Author: petrstepanov
 */

#ifndef SRC_MODEL_BRANCHES_SPECTRUM_H_
#define SRC_MODEL_BRANCHES_SPECTRUM_H_

#include <TObject.h>
#include <TH1F.h>
#include <RooDataHist.h>
#include <RooAbsPdf.h>
#include <RooPlot.h>

class Spectrum : public TNamed {
public:
	Spectrum(Int_t _id);
	virtual ~Spectrum();

	Int_t id;
	TString* filename;
	TH1* histogram;              // ROOT histogram
//	TH1* cutHistogram;           // ROOT histogram, cut
//	RooDataHist* dataHistogram;   // RooFit histogram
//	Double_t integral;            // total counts
//	Int_t numberOfBins;
//	Int_t binWithMinimumCount;    // bin number with minimum value in the range
//	Int_t binWithMaximumCount;    // bin number with maximum value in the range
//	Double_t minimumCount;        // minimum count across all bins
//	Double_t maximumCount;        // maximum count across all bins
//	Double_t averageBackground;
	RooAbsPdf* model;
	RooAbsPdf* resolutionFunction;
	RooPlot* plot;

	ClassDef(Spectrum, 1)  // Event structure
};

#endif /* SRC_MODEL_BRANCHES_SPECTRUM_H_ */
