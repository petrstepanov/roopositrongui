/*
 * ProjectView.h
 *
 *  Created on: Apr 17, 2019
 *      Author: petrstepanov
 */

#ifndef SRC_VIEWS_PROJECT_PROJECTVIEW_H_
#define SRC_VIEWS_PROJECT_PROJECTVIEW_H_

#include "./../AbstractView.h"
#include "ProjectPresenter.h"

#include "../files/FilesView.h"
#include "../plots/PlotsView.h"
#include <TGSplitter.h>
#include <TGShutter.h>

class ProjectPresenter;

class ProjectView : public AbstractView<ProjectPresenter> {
  protected:
    void initUI();
    void connectSlots();

  private:
	// Declare UI elements
    TGHSplitter* splitter;
    TGShutter* shutter;
    FilesView* filesView;
    PlotsView* plotsView;

  public:
    ProjectView(const TGWindow *w = 0);
    virtual ~ProjectView();

    // Override base class virtual functions
    ProjectPresenter* instantinatePresenter();

    // Hack for resizing the TGCanvas
    void HandleConfigure(Event_t *event);
};

#endif /* SRC_VIEWS_PROJECT_PROJECTVIEW_H_ */
