/*
 * Spectrum.cpp
 *
 *  Created on: Apr 23, 2019
 *      Author: petrstepanov
 */

#include "Spectrum.h"
#include "../../util/HistUtils.h"
#include "../../util/RootHelper.h"

#include <string.h>

ClassImp(Spectrum);

Spectrum::Spectrum(const char* filepath) : TObject() {
  // Assign unique ID and original file path
  id = RootHelper::getInstance()->getHash();
  this->filepath = TString(filepath);

  // Import histogram
  histogram = HistUtils::importTH1I(filepath);
  cutHistogram=histogram;

  binWidthNs = 0;
  leftBin=1;
  rightBin=histogram->GetNbinsX();

  plot = nullptr;
}

Spectrum::~Spectrum() {
  delete histogram;
  delete cutHistogram;
  delete plot;
}

const char* Spectrum::getFilePath(){
  return filepath.Data();
}

bool Spectrum::operator==(const Spectrum& other){
  // Crude implementation of comparison
  // Compare number of bins
  if (this->histogram->GetXaxis()->GetNbins() != other.histogram->GetXaxis()->GetNbins()) return false;
  // Compare left edge
  if (this->histogram->GetXaxis()->GetBinLowEdge(1) != other.histogram->GetXaxis()->GetBinLowEdge(1)) return false;
  // Comapre right edge
  if (this->histogram->GetXaxis()->GetBinUpEdge(this->histogram->GetXaxis()->GetNbins()) != other.histogram->GetXaxis()->GetBinUpEdge(other.histogram->GetXaxis()->GetNbins())) return false;

  // Compare content
  for (int i=1; i < this->histogram->GetXaxis()->GetNbins(); i++){
    if (this->histogram->GetBinContent(i) != other.histogram->GetBinContent(i)) return false;
  }
  return true;
}
