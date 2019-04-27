/*
 * Model.h
 *
 *  Created on: Apr 16, 2019
 *      Author: petrstepanov
 */

#ifndef SRC_MODEL_MODEL_H_
#define SRC_MODEL_MODEL_H_

#include <TQObject.h>
#include <RtypesCore.h>
#include <TString.h>
#include "branches/ProjectModel.h"
#include "branches/Spectrum.h"
#include <TVector2.h>

class Model : public TQObject {
public:
	static Model* getInstance();

	// Project
    TString* getProjectFilename();
    Bool_t isProjectModifiedAfterSave();
	Bool_t saveProjectToFile(const TString* filename);
	Bool_t readProjectFromFile(const TString* filename);
	void newProject();
	void closeProject();

	// Spectra manipulation
	void deleteSpectra();
	void deleteSpectrum(Int_t id);
    void addSpectrum(Spectrum* spectrum);
    TObjArray* getSpectra();

    // Number of channels
    Int_t getNumberOfChannels();
    void setNumberOfChannels(Int_t channels);

    // Spectra trim
    void setTrimChannels(Int_t minChannel, Int_t maxChannel);
    Int_t getMinTrimChannel();
    Int_t getMaxTrimChannel();

	// Signals
    void channelsNumberSet(Int_t channels); // *SIGNAL*
    void spectraNumberChanged(Int_t number); // *SIGNAL*
	void projectCreated(); // *SIGNAL*
    void projectClosed(); // *SIGNAL*
    void projectSaved(TString* filename); // *SIGNAL*
    void spectraDeleted(); // *SIGNAL*
    void spectrumDeleted(Int_t id); // *SIGNAL*
    void spectrumAdded(Spectrum* spectrum); // *SIGNAL*
	void trimChannelsSet(TVector2* ); // *SIGNAL*

private:
	Model();
	virtual ~Model();

	static Model* instance;
	ProjectModel* projectModel;

	// Objects stored in memory but not saved to disk
	TString* projectFilename;
	Bool_t projectModifiedAfterSave;

	// ClassDef(<ClassName>,<VersionNumber>)
	// When a class has version 0 it is not stored in a root file but its base classes are
	ClassDef(Model, 0)
};

#endif /* SRC_MODEL_MODEL_H_ */
