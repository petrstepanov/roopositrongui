/*
 * Spectrum.cpp
 *
 *  Created on: Apr 23, 2019
 *      Author: petrstepanov
 */

#include "Spectrum.h"

ClassImp(Spectrum);

Spectrum::Spectrum(Int_t _id) :
    TNamed(Form("%d", _id), "") {
  id = _id;
  filename = nullptr;
  histogram = nullptr;
//	cutHistogram = nullptr;
//	dataHistogram = nullptr;
//	integral = 0;
//	numberOfBins = 0;
//	binWithMinimumCount = 0;
//	binWithMaximumCount = 0;
//	minimumCount = 0;
//	maximumCount = 0;
//	averageBackground = 0;
  model = nullptr;
  resolutionFunction = nullptr;
  plot = nullptr;
}

Spectrum::~Spectrum() {
}

