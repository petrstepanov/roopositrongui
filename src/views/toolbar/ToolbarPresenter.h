/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TOOLBRPRESENTER.h
 * Author: petrstepanov
 *
 * Created on October 6, 2017, 6:31 PM
 */

#ifndef TOOLBARPRESENTER_H
#define TOOLBARPRESENTER_H

#include "./../AbstractPresenter.h"
#include "../../model/Model.h"

class ToolbarView;

class ToolbarPresenter : public AbstractPresenter<Model, ToolbarView> {
public:
    ToolbarPresenter(ToolbarView* view);
    virtual ~ToolbarPresenter(){};

    // Override base class virtual methods
    Model* instantinateModel();
    
    void onInitModel();

    // Slots from the view
    void onNewButtonClicked();
    void onOpenButtonClicked();
    void onSaveButtonClicked();
    void onSaveAsButtonClicked();
    void onCloseButtonClicked();

    // Slots from the model
    void handleProjectClosed();
    void handleProjectCreated();
    void handleTempSignal();
};

#endif /* TOOLBARPRESENTER_H */

