/*
 * LayoutPresenter.h
 *
 *  Created on: Apr 26, 2019
 *      Author: petrstepanov
 */

#ifndef SRC_VIEWS_LAYOUT_LAYOUTPRESENTER_H_
#define SRC_VIEWS_LAYOUT_LAYOUTPRESENTER_H_

#include "./../AbstractPresenter.h"
#include "../../model/Model.h"

class LayoutView;

class LayoutPresenter : public AbstractPresenter<Model, LayoutView> {
public:
    LayoutPresenter(LayoutView* view);
    virtual ~LayoutPresenter();

    // Override base class virtual methods
    Model* instantinateModel();
    void onInitModel();

    // Slots for Model signals
    void handleProjectCreated();
    void handleProjectClosed();
    void handleModelErrorSignal(const char*);


    // Slots from the view
    ClassDef(LayoutPresenter, 0)
};

#endif /* SRC_VIEWS_LAYOUT_LAYOUTPRESENTER_H_ */
