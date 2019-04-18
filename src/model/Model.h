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

class Model : public TQObject {
public:
	static Model* getInstance();

	// Objects saved and read to hard drive
	ProjectModel* projectModel;

	void newProject();
	Bool_t saveProjectToFile(TString* filename);
	Bool_t readProjectFromFile(TString* filename);
	void closeProject();

    void projectCreated(); // *SIGNAL*
    void projectClosed(); // *SIGNAL*
    void projectSaved(TString* filename); // *SIGNAL*

    // Getters
    TString* getProjectFilename();
    Bool_t isProjectModifiedAfterSave();

private:
	Model();
	virtual ~Model();

	static Model* instance;

	// Objects stored in memory but not saved to disk
	TString* projectFilename;
	Bool_t projectModifiedAfterSave;

	ClassDef(Model, 0)
};

#endif /* SRC_MODEL_MODEL_H_ */
