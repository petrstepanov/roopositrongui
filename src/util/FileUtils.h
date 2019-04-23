/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FileUtils.h
 * Author: petrstepanov
 *
 * Created on November 9, 2016, 11:41 PM
 */

#ifndef MY_FILEUTILS
#define MY_FILEUTILS

#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <TH1F.h>

class FileUtils {
public:
    static TH1F* importTH1F(const char* filename, int skipLines, int readLines);
    
private:
    std::string getCurrentPath();
    const char kPathSeparator =
#ifdef _WIN32
    '\\';
#else
    '/';
#endif
};

#endif /* MY_FILEUTILS */

