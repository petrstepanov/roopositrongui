/*
 * Images.h
 *
 *  Created on: Apr 16, 2019
 *      Author: petrstepanov
 */

#ifndef SRC_RESOURCES_IMAGES_H_
#define SRC_RESOURCES_IMAGES_H_

#include <TGPicture.h>

class Images {
public:

	static char* applicationIcon[];

	static char* projectNewXpm[];
	static char* projectOpenXpm[];
	static char* projectSaveXpm[];
	static char* projectSaveAsXpm[];
	static char* projectCloseXpm[];

	static const TGPicture* makeTGPicture(char**);
};

#endif /* SRC_RESOURCES_IMAGES_H_ */
