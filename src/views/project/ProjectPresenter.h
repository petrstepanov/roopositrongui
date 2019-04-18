/*
 * ProjectPresenter.h
 *
 *  Created on: Apr 17, 2019
 *      Author: petrstepanov
 */

#ifndef SRC_VIEWS_PROJECT_PROJECTPRESENTER_H_
#define SRC_VIEWS_PROJECT_PROJECTPRESENTER_H_

#include "./../AbstractPresenter.h"
#include "../../model/Model.h"

class ProjectView;

class ProjectPresenter : public AbstractPresenter<ProjectModel, ProjectView> {
public:
    ProjectPresenter(ProjectView* view);
    virtual ~ProjectPresenter();

    // Override base class virtual methods
    ProjectModel* instantinateModel();

    // Signals from model
    void onInitModel();

    // Slots from the view
};

#endif /* SRC_VIEWS_PROJECT_PROJECTPRESENTER_H_ */
