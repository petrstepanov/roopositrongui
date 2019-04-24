/*
 * PlotsPresenter.h
 *
 *  Created on: Apr 23, 2019
 *      Author: petrstepanov
 */

#ifndef SRC_VIEWS_PLOTS_PLOTSPRESENTER_H_
#define SRC_VIEWS_PLOTS_PLOTSPRESENTER_H_

#include "./../AbstractPresenter.h"
#include "../../model/Model.h"

class PlotsView;

class PlotsPresenter : public AbstractPresenter<Model, PlotsView> {
public:
    PlotsPresenter(PlotsView* view);
    virtual ~PlotsPresenter();

    // Override base class virtual methods
    Model* instantinateModel();

    // Signals from model
    void onInitModel();

    // Slots from the view
};

#endif /* SRC_VIEWS_PLOTS_PLOTSPRESENTER_H_ */
