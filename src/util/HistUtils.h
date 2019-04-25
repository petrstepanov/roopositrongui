/*
 * HistProcessor.h
 *
 *  Created on: Apr 24, 2019
 *      Author: petrstepanov
 */

#ifndef SRC_UTIL_HISTUTILS_H_
#define SRC_UTIL_HISTUTILS_H_

#include <TH1.h>
#include <RooDataHist.h>
#include <RooRealVar.h>

class HistUtils {

public:
    static TH1* importTH1I(const char* filename);
	static TH1* cutHist(TH1* histogram, Int_t minBin, Int_t maxBin);
	static RooDataHist* makeRooDataHist(TH1* histogram, RooRealVar* channels);
};

#endif /* SRC_UTIL_HISTUTILS_H_ */
