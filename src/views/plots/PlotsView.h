/*
 * PlotsView.h
 *
 *  Created on: Apr 23, 2019
 *      Author: petrstepanov
 */

#ifndef SRC_VIEWS_PLOTS_PLOTSVIEW_H_
#define SRC_VIEWS_PLOTS_PLOTSVIEW_H_

#include "./../AbstractView.h"
#include "PlotsPresenter.h"

class PlotsPresenter;

class PlotsView : public AbstractView<PlotsPresenter> {
  protected:
    void initUI();

  private:
	// Declare UI elements

  public:
    PlotsView(const TGWindow *w = 0);
    virtual ~PlotsView();

    // Override base class virtual functions
    PlotsPresenter* instantinatePresenter();
};

#endif /* SRC_VIEWS_PLOTS_PLOTSVIEW_H_ */
