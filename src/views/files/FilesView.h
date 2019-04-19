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

class FilesPresenter;

class FilesView : public AbstractView<FilesPresenter> {
  protected:
    void initUI();

  private:
	// Declare UI elements

  public:
    FilesView(const TGWindow *w = 0);
    virtual ~FilesView();

    // Override base class virtual functions
    FilesPresenter* instantinatePresenter();
};

#endif /* SRC_VIEWS_FILES_FILESVIEW_H_ */
