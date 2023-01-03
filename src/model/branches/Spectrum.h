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

class Spectrum : public TObject {
public:
  Spectrum(const char* filepath);
  virtual ~Spectrum();

  // Override equals operator
  bool operator==(const Spectrum& other);

  const char* getFilePath();

private:
  UInt_t id;
  TString filepath;
  TH1* histogram;                 // ROOT histogram
  TH1* cutHistogram;              // ROOT histogram, cut
//	RooDataHist* dataHistogram;   // RooFit histogram
//	Double_t integral;            // total counts
//	Int_t numberOfBins;
//	Int_t binWithMinimumCount;    // bin number with minimum value in the range
//	Int_t binWithMaximumCount;    // bin number with maximum value in the range
//	Double_t minimumCount;        // minimum count across all bins
//	Double_t maximumCount;        // maximum count across all bins
//	Double_t averageBackground;
//  RooAbsPdf *model;
//  RooAbsPdf *resolutionFunction;
  UInt_t leftBin;
  UInt_t rightBin;
  Double_t binWidthNs;
  // TCanvas preview;
  RooPlot* plot;

ClassDef(Spectrum, 1)  // Event structure
};

#endif /* SRC_MODEL_BRANCHES_SPECTRUM_H_ */
