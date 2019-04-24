/*
 * FilesView.h
 *
 *  Created on: Apr 18, 2019
 *      Author: petrstepanov
 */

#ifndef SRC_VIEWS_FILES_FILESVIEW_H_
#define SRC_VIEWS_FILES_FILESVIEW_H_

#include "./../AbstractView.h"
#include "FilesPresenter.h"
#include <TGListBox.h>
#include <TGButton.h>
#include <TGNumberEntry.h>

class FilesPresenter;

class FilesView : public AbstractView<FilesPresenter> {
  protected:
    void initUI();

  public:
    FilesView(const TGWindow *w = 0);
    virtual ~FilesView();

    // Override base class virtual functions
    FilesPresenter* instantinatePresenter();

    TGListBox* filesListBox;
    TGNumberEntry* skipLinesNumberEntry;
    TGNumberEntry* readChannelsNumberEntry;
	TGButton* removeFilesButton;

    void onFileSelected(Int_t selectedNumber);
//    void onFileSelectionChanged();

//    void HandleConfigure(Event_t *event);
};

#endif /* SRC_VIEWS_FILES_FILESVIEW_H_ */
