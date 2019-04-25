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
#include <TGClient.h>
#include <TColor.h>
#include <TGFrame.h>
#include <iostream>
#include "../resources/Constants.h"
#include "Debug.h"

UiHelper::UiHelper() {}

UiHelper* UiHelper::instance = NULL;

TList* UiHelper::getFilesFromDialog(const char** filetypes){
	static TString dir(".");
	TGFileInfo fileInfo;
	fileInfo.fFileTypes = filetypes;
	fileInfo.fIniDir = StrDup(dir);
	TList* newFilenamesList;

	const TGWindow* mainFrame = UiHelper::getInstance()->getMainFrame(); // For dialog centering
	new TGFileDialog(gClient->GetRoot(), mainFrame ? mainFrame : gClient->GetRoot(), EFileDialogMode::kFDOpen, &fileInfo);

	// Save current directory
	dir = fileInfo.fIniDir;
	if (fileInfo.fMultipleSelection && fileInfo.fFileNamesList) {
		newFilenamesList = (TList*)(fileInfo.fFileNamesList->Clone("newFilenamesList"));
	}
	else {
		newFilenamesList = new TList();
		if (fileInfo.fFilename){
			newFilenamesList->Add(new TObjString(fileInfo.fFilename));
		}
	}
	#ifdef USEDEBUG
		Debug("UiHelper::getFilesFromDialog");
		newFilenamesList->Print("V");
	#endif
	return newFilenamesList;
}

const TString* UiHelper::getFileFromDialog(const char** filetypes){
	TList* files = getFilesFromDialog(filetypes);
	TObject* o = files->At(0);
	TObjString* objString = dynamic_cast<TObjString*>(o);
	const TString* s = &(objString->GetString());
	return s;
}

int UiHelper::showOkDialog(const char* message, const EMsgBoxIcon msgBoxIcon){
    int retval;
    new TGMsgBox(gClient->GetRoot(), mainFrame ? mainFrame : gClient->GetRoot(), Constants::applicationName, message, msgBoxIcon, kMBOk, &retval);
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

const TGWindow* UiHelper::getMainFrame() {
    return mainFrame;
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
	if (childFrames->GetSize() == 0) return nullptr;

	TObject* obj = childFrames->At(0);
	TGFrameElement* firstFrameElement = dynamic_cast<TGFrameElement*>(obj);
	TGFrame* firstFrame = firstFrameElement->fFrame;
	TGCompositeFrame* firstCompositeFrame = dynamic_cast<TGCompositeFrame*>(firstFrame);
	return firstCompositeFrame;
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

void UiHelper::setDarkBackground(TGFrame* frame){
    // frame->SetBackgroundColor(gClient->GetShadow(TGFrame::GetDefaultFrameBackground()));
	frame->SetBackgroundColor(TColor::Number2Pixel(kGray));
}

void UiHelper::setDarkerBackground(TGFrame* frame){
    // frame->SetBackgroundColor(gClient->GetShadow(TGFrame::GetDefaultFrameBackground()));
	frame->SetBackgroundColor(TColor::Number2Pixel(kGray+1));
}

void UiHelper::setLightBackground(TGFrame* frame){
	frame->SetBackgroundColor(TColor::Number2Pixel(kWhite));
}
//
//void UiHelper::setSolidBorder(TGFrame* frame){
//	frame->ChangeOptions(frame->GetOptions() | kDoubleBorder);
//	frame->SetBackgroundColor(gClient->GetShadow(TGFrame::GetDefaultFrameBackground()));
//}

void UiHelper::setHeight(TGFrame* frame, int height){
    frame->SetHeight(height);
    frame->ChangeOptions(frame->GetOptions() | kFixedHeight);
}
