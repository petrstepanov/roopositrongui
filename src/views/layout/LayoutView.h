/*
 * LayoutView.h
 *
 *  Created on: Apr 26, 2019
 *      Author: petrstepanov
 */

#ifndef SRC_VIEWS_LAYOUT_LAYOUTVIEW_H_
#define SRC_VIEWS_LAYOUT_LAYOUTVIEW_H_

#include "./../AbstractView.h"
#include "LayoutPresenter.h"

class LayoutPresenter;

class LayoutView : public AbstractView<LayoutPresenter> {
  public:
    LayoutView(const TGWindow *w = 0);
    virtual ~LayoutView();

    // Override base class virtual functions
    LayoutPresenter* instantinatePresenter();

	// Declare UI elements
    TGCompositeFrame* projectContainer;

    // Calls from presenter
    void createNewProjectView();
    void removeProjectView();

  protected:
    void initUI();
    void connectSignalsToPresenter();
};

#endif /* SRC_VIEWS_LAYOUT_LAYOUTVIEW_H_ */
