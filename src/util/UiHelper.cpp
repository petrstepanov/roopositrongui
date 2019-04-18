/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   UiHelper.cpp
 * Author: petrstepanov
 *
 * Created on October 11, 2017, 1:31 AM
 */

#include "UiHelper.h"
#include <TList.h>
#include <TGMsgBox.h>
#include <TGFileDialog.h>
#include "../resources/Constants.h"
#include <iostream>

UiHelper::UiHelper() {}

UiHelper* UiHelper::instance = NULL;

TGFileInfo* UiHelper::getFileFromDialog(const char* fileDescription, const char* fileExtension){
    // show file dialog
    TGFileInfo* fileInfo = new TGFileInfo();
    const char* filetypes[] = { fileDescription, fileExtension, 0, 0 };
    static TString dir(".");
    fileInfo->fFileTypes = filetypes;
    fileInfo->fIniDir = StrDup(dir);
    // Show the dialog
    new TGFileDialog(gClient->GetRoot(), mainFrame ? mainFrame : gClient->GetRoot(), EFileDialogMode::kFDOpen, fileInfo);
    // printf("Open file: %s (dir: %s)\n", fileInfo->fFilename, fileInfo->fIniDir);
    return fileInfo;
}

int UiHelper::showOkDialog(const char* message){
    int retval;
    new TGMsgBox(gClient->GetRoot(), mainFrame ? mainFrame : gClient->GetRoot(), Constants::applicationName, message, kMBIconAsterisk, kMBOk, &retval);
    return retval;
}

void UiHelper::setLabelColor(TGLabel* label, const char* color){
    ULong_t lblFileNameTextColor;
    gClient->GetColorByName(color, lblFileNameTextColor);
    label->SetTextColor(15);
}

void UiHelper::setMainFrame(TGWindow* w) {
    mainFrame = w;
}

UiHelper* UiHelper::getInstance() {
    if (!instance){
        instance = new UiHelper();
    }
    return instance;
}


TGCompositeFrame* UiHelper::getParentFrame(TGFrame* frame){
	const TGWindow* parentWindow = frame->GetParent();
	TGCompositeFrame* parentFrame = dynamic_cast<TGCompositeFrame*>(const_cast<TGWindow*>(parentWindow));
	return parentFrame;
}

TGCompositeFrame* UiHelper::getFirstChildFrame(TGCompositeFrame* frame){
	TList* childFrames = frame->GetList();
	TObject* obj = childFrames->At(0);
	if (TGCompositeFrame* childFrame = dynamic_cast<TGCompositeFrame*>(obj)){
		return childFrame;
	}
	return nullptr;
}

void UiHelper::removeFrame(TGCompositeFrame* &frame){
	// https://root-forum.cern.ch/t/how-to-remove-a-button-from-a-gui/21365/3
	if (!frame) return;

	TGCompositeFrame* parentFrame = getParentFrame(frame);
	parentFrame->RemoveFrame(frame);
	frame->UnmapWindow();
	frame->ReparentWindow(gClient->GetDefaultRoot());
	delete frame;
	frame = 0;
}
