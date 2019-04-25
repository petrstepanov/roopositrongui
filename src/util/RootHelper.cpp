/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   RootHelper.cpp
 * Author: petrstepanov
 *
 * Created on October 11, 2017, 1:31 AM
 */

#include "RootHelper.h"

RootHelper::RootHelper(){
	random = new TRandom();
}

RootHelper* RootHelper::instance = NULL;

RootHelper* RootHelper::getInstance() {
    if (!instance){
        instance = new RootHelper();
    }
    return instance;
}

Int_t RootHelper::getRandomInt(){
	return random->Rndm()*1E6;
}
