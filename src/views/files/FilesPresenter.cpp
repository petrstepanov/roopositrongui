/*
 * FilesPresenter.cpp
 *
 *  Created on: Apr 18, 2019
 *      Author: petrstepanov
 */

#include "FilesPresenter.h"
#include "FilesView.h"
#include "../AbstractPresenter.h"
#include "../../model/Model.h"
#include "../../model/branches/Spectrum.h"
#include "../../util/UiHelper.h"
#include "../../util/FileUtils.h"

#include <TObject.h>
#include <TGFileDialog.h>
#include <TObjString.h>

FilesPresenter::FilesPresenter(FilesView* view) : AbstractPresenter<Model, FilesView>(view) {
	model = instantinateModel();
	onInitModel();
}

FilesPresenter::~FilesPresenter() {
}

Model* FilesPresenter::instantinateModel() {
	return Model::getInstance();
}

void FilesPresenter::onInitModel() {
	// Connect Model signals to slots
	model->Connect("spectraDeleted()", "FilesPresenter", this, "handleSpectraDeleted()");
}

// Slots from View
void FilesPresenter::onAddFilesClicked() {

	// Get new spectra fileInfolenames from fileInfole dilog
	const char *fileInfoletypes[] = { "Maestro spectra", "*.Spe", "All files", "*", 0, 0 };
	static TString dir(".");
	TGFileInfo fileInfo;
	fileInfo.fFileTypes = fileInfoletypes;
	fileInfo.fIniDir = StrDup(dir);
	TList* newFilenamesList;

	const TGWindow* mainFrame = UiHelper::getInstance()->getMainFrame(); // For dialog centering
	new TGFileDialog(gClient->GetRoot(), mainFrame ? mainFrame : gClient->GetRoot(), EFileDialogMode::kFDOpen, &fileInfo);

	// Save current directory
	dir = fileInfo.fIniDir;
	if (fileInfo.fMultipleSelection && fileInfo.fFileNamesList) {
		newFilenamesList = fileInfo.fFileNamesList;
//		TObjString *el;
//		TIter next(fileInfo.fFileNamesList);
//		while ((el = (TObjString *) next())) {
//			new TFile(el->GetString(), "update");
//		}
	} else if (fileInfo.fFilename) {
		newFilenamesList = new TList();
		newFilenamesList->Add(new TObjString(fileInfo.fFilename));
	}

	#ifdef USEDEBUG
		Debug("FilesPresenter::onAddFilesClicked");
		newFilenamesList->Print("V");
	#endif
	if (newFilenamesList->GetSize()==0) return;

	// See if import limits were changed. Delete existing model spectra and mark for re-import
	Int_t skipLines = atoi(view->skipLinesNumberEntry->GetNumberEntry()->GetText());
	Int_t readLines = atoi(view->readChannelsNumberEntry->GetNumberEntry()->GetText());

	if (skipLines != model->getProjectModel()->skipLines || readLines != model->getProjectModel()->readLines){
		TObjArray* spectraObjArray = model->getSpectra();
		for (Int_t i=0 ; i<spectraObjArray->GetSize(); i++){
			TObject* o = spectraObjArray->At(i);
			if (TNamed* n = dynamic_cast<TNamed*>(o)){
				newFilenamesList->Add(new TObjString(n->GetName()));
			}
		}
		model->deleteSpectra();
	}

	// Iterate through new filenames
	TObjArray* currentSpectra = model->getProjectModel()->spectra;
	TIter next(newFilenamesList);
	while (TObject *obj = next()){
		if (TObjString* objString = dynamic_cast<TObjString*>(obj)){
			// See if filename already exists
			const char* filename = objString->GetString().Data();
			if (!model->getProjectModel()->spectra->FindObject(filename)){
//				Spectrum* spectrum = new Spectrum();
//				spectrum->SetName(filename);
				// Import and convert spectrum
			}
		}
	}

	// Update model spectra map with new Spectra()

	// If changed "Skip lines" or "Read channels" - recalculate all
	// Otherwise only new
}

void FilesPresenter::onRemoveFilesClicked() {

}

void FilesPresenter::onImportSpectraClicked() {

}


