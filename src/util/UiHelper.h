/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   UiHelper.h
 * Author: petrstepanov
 *
 * Created on October 11, 2017, 1:31 AM
 */

#ifndef UIHELPER_H
#define UIHELPER_H

#include <TGFileDialog.h>
#include <TGLabel.h>
#include <TGWindow.h>
#include <TGMsgBox.h>

class UiHelper {
public:
    static UiHelper* getInstance();
    static void setLabelColor(TGLabel* label, const char* color);

    TList* getFilesFromDialog(const char** filetypes);
    const TString* getFileFromDialog(const char** filetypes);
    int showOkDialog(const char* message, EMsgBoxIcon msgBoxIcon);

    void setMainFrame(TGWindow* window);
    const TGWindow* getMainFrame();

    static TGCompositeFrame* getParentFrame(TGFrame* frame);
    static TGCompositeFrame* getFirstChildFrame(TGCompositeFrame* frame);
    static void setDarkBackground(TGFrame* frame);
    static void setDarkerBackground(TGFrame* frame);
    static void setLightBackground(TGFrame* frame);
    static void removeFrame(TGCompositeFrame* &frame);
//    static void setSolidBorder(TGFrame* frame);
    static void setHeight(TGFrame* frame, int height);

private:
    UiHelper();
    static UiHelper* instance;
    const TGWindow* mainFrame = nullptr;
};

#endif /* UIHELPER_H */

