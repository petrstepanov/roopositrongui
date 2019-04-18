/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   MyMainFrame.h
 * Author: petrstepanov
 *
 * Created on October 15, 2017, 1:47 AM
 */

#ifndef MYMAINFRAME_H
#define MYMAINFRAME_H

#include <TGFrame.h>
#include "project/ProjectView.h"

class MyMainFrame : public TGMainFrame {

public:
    MyMainFrame();
    virtual ~MyMainFrame();

    void exit();
    void show();

    // Slots for Model signals
    void handleProjectCreated();
    void handleProjectClosed();

    ClassDef(MyMainFrame, 0);

private:
    TGCompositeFrame* projectContainer;
    TGCompositeFrame* projectView;
};

#endif /* MyMainFrameW_H */
