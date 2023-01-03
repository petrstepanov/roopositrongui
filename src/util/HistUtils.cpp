/*
 * HistProcessor.cpp
 *
 *  Created on: Apr 24, 2019
 *      Author: petrstepanov
 */

#include "HistUtils.h"

#include <TUnixSystem.h>
#include <TSystemDirectory.h>
#include <TSystemFile.h>
#include <TList.h>
#include <TMath.h>
#include <fstream>
#include <sstream>
#include <RooArgList.h>
#include "../resources/Constants.h"
#include "../util/StringUtils.h"
#include "../util/Debug.h"

TH1* HistUtils::importTH1I(const char *filename) {
  // Open file
  std::ifstream inFile(filename);

  // Treminate if error
  if (!inFile) {
    std::cout << "File \"" << filename << "\" not found." << std::endl;
    return nullptr;
  }

  // Skip spectrum header (12 lines)
  std::string sLine = "";
  for (UInt_t i = 0; i < 12; i++) {
    getline(inFile, sLine);
  }

  // Now 12's line contains number of channels in spectrum - usually "0 8191"
  std::istringstream streamLine(sLine);
  Int_t channels;
  streamLine >> channels;
  streamLine >> channels;

  // Realistically number of channels id 8192 - increasing by one
  channels++;

  static int uid = 0;
  uid++;
  // Create and import everything into ROOT histogram
  TString name = TString::Format("hist_%d", uid);
  TH1I *histogram = new TH1I(name.Data(), filename, channels, 0, channels);

  // Read correspondent number of channels
  for (UInt_t i = 1; i <= channels; i++) {
    getline(inFile, sLine);
    std::istringstream streamLine(sLine);
    Int_t count;
    streamLine >> count;
    if (streamLine.fail()) {
#ifdef USEDEBUG
      std::cout << "FileUtils::importTH1I" << std::endl
          << "Failed parsing file." << std::endl;
#endif
      streamLine.clear();
      count = 0;
    }
    // The RooFit chi2 fit does not work when the bins have zero entries.
    // So we always increase count by 1 just in case
    histogram->SetBinContent(i, count + 1);
    histogram->SetBinError(i, TMath::Sqrt((Double_t) count + 1));
  }

  inFile.close();
  return histogram;
}

TH1* HistUtils::cutHist(TH1 *histogram, Int_t minBin, Int_t maxBin) {
  minBin = TMath::Max(1, minBin);
  maxBin = TMath::Min(histogram->GetXaxis()->GetNbins(), maxBin);

  TString name = TString::Format("cut%s", histogram->GetName());
  TString title = TString::Format("Cut %s", histogram->GetTitle());

  Int_t lowMinBinEdge = histogram->GetXaxis()->GetBinLowEdge(minBin);
  Int_t upMaxBinEdge = histogram->GetXaxis()->GetBinUpEdge(maxBin);

  TH1 *cutHistogram = new TH1I(name.Data(), title.Data(), maxBin - minBin + 1,
      lowMinBinEdge, upMaxBinEdge);

  for (UInt_t i = minBin; i <= maxBin; i++) {
    Int_t value = histogram->GetBinContent(i);
    Double_t error = histogram->GetBinError(i);
    cutHistogram->SetBinContent(i - minBin + 1, value);
    cutHistogram->SetBinError(i - minBin + 1, error);
  }

  return cutHistogram;
}

RooDataHist* HistUtils::makeRooDataHist(TH1 *histogram, RooRealVar *channels) {
  TString name = TString::Format("data%s", histogram->GetName());
  TString title = TString::Format("Data %s", histogram->GetTitle());
  // RooDataHist(const char *name, const char *title, const RooArgList& vars, const TH1* hist, Double_t initWgt=1.0) ;
  // RooArgList(const RooAbsArg& var1, const char *name="");

  RooDataHist *dataHist = new RooDataHist(name.Data(), title.Data(),
      RooArgList(*channels), histogram);
  return dataHist;

}
