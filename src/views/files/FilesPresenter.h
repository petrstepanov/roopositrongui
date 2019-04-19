/*
 * FilesPresenter.h
 *
 *  Created on: Apr 18, 2019
 *      Author: petrstepanov
 */

#ifndef SRC_VIEWS_FILES_FILESPRESENTER_H_
#define SRC_VIEWS_FILES_FILESPRESENTER_H_

#include "./../AbstractPresenter.h"
#include "../../model/Model.h"

class FilesView;

class FilesPresenter : public AbstractPresenter<Model, FilesView> {
public:
    FilesPresenter(FilesView* view);
    virtual ~FilesPresenter();

    // Override base class virtual methods
    Model* instantinateModel();

    // Signals from model
    void onInitModel();

    // Slots from the view
    void onAddFilesClicked();
    void onRemoveFilesClicked();
};

#endif /* SRC_VIEWS_FILES_FILESPRESENTER_H_ */
