/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   SWCalculatorFrame.h
 * Author: petrstepanov
 *
 * Created on August 1, 2017, 5:02 PM
 */

#ifndef TOOLBARVIEW_H
#define TOOLBARVIEW_H

#include "./../AbstractView.h"
#include "./ToolbarPresenter.h"
#include <TGButton.h>
#include <TGLabel.h>

class ToolbarPresenter;

class ToolbarView : public AbstractView<ToolbarPresenter> {
  protected:
    void initUI();
    void connectSlots();

  public:
    ToolbarView(const TGWindow *w = 0);
    virtual ~ToolbarView(){};

    TGPictureButton* newButton;
    TGPictureButton* openButton;
    TGPictureButton* saveButton;
    TGPictureButton* saveAsButton;
    TGPictureButton* closeButton;
    TGLabel* filenameLabel;

    // Override base class virtual functions
    ToolbarPresenter* instantinatePresenter();

    // Global slot for the uiReady event
    void handleUiReady();
};

#endif /* TOOLBARVIEW_H */
