/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   RootHelper.h
 * Author: petrstepanov
 *
 * Created on October 11, 2017, 1:31 AM
 */

#ifndef ROOTHELPER_H
#define ROOTHELPER_H

#include <TRandom.h>

class RootHelper {
public:
    static RootHelper* getInstance();
    Int_t getRandomInt();
    const char* getUUID();
    UInt_t getHash();

private:
    RootHelper();
    static RootHelper* instance;
    TRandom myRandom;
};

#endif /* ROOTHELPER_H */

