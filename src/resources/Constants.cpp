/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Constants.cpp
 * Author: petrstepanov
 *
 * Created on August 19, 2017, 11:30 PM
 */

#include "../resources/Constants.h"

#include <TMath.h>

// Application name
const char* Constants::applicationName = "RooLifetime";

UInt_t Constants::leftPanelWidth = 387;

// Convolution buffer fraction
// Double_t Constants::bufferFraction = 1.5;

// Convert sigma to FWHM: https://en.wikipedia.org/wiki/Full_width_at_half_maximum
// const Double_t Constants::sigmaToFwhm = 2 * TMath::Sqrt(2 * TMath::Log(2));
// const Double_t Constants::fwhmToSigma = 1 / sigmaToFwhm;

// RooConstVar* Constants::rooFwhmToSigma = new RooConstVar("rooFwhmToSigma", "Coefficient to convert FWHM to dispersion", Constants::fwhmToSigma);
// RooConstVar* Constants::pi = new RooConstVar("pi", "pi", TMath::Pi());
