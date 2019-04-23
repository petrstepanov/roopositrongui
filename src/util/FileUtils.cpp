/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FileUtils.cpp
 * Author: petrstepanov
 * 
 * Created on November 9, 2016, 11:41 PM
 */

#include "FileUtils.h"
#include <TUnixSystem.h>
#include <TSystemDirectory.h>
#include <TSystemFile.h>
#include <TList.h>
#include "../resources/Constants.h"
#include "../util/StringUtils.h"
#include "../util/Debug.h"

TH1F* FileUtils::importTH1F(const char* filename, int skipLines, int readLines) {
	TH1F* histogram = new TH1F(TString::Format("histogram_%s", filename), TString::Format("ROOT histogram %s", filename), readLines, 0, readLines);

	// Open file
	std::ifstream inFile(filename);
	// Treminate if error
	if (!inFile) {
		std::cout << "File \"" << filename << "\" not found." << std::endl;
		exit(1);
	}

	// Skip spectrum header
	std::string sLine = filename;
	for (unsigned j = 0; j < skipLines; j++) {
		getline(inFile, sLine);
	}

	// Fill in histogram
	for (unsigned j = 1; j <= readLines; j++) {
		getline(inFile, sLine);
		std::istringstream streamLine(sLine);
		Double_t dCount;
		streamLine >> dCount;
		if (streamLine.fail()) {
			std::cout << "Failed parsing file." << std::endl;
			streamLine.clear();
			dCount = 0;
		}
		histogram->SetBinContent(j, dCount + 1); // The RooFit chi2 fit does not work when the bins have zero entries.
		histogram->SetBinError(j, sqrt(dCount + 1));
	}

	inFile.close();
	return histogram;
}
