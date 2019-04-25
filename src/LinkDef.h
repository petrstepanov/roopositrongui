#ifdef __CINT__
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link C++ nestedclasses;

// Classes with slots
#pragma link C++ class MyMainFrame;
#pragma link C++ class ToolbarPresenter;
#pragma link C++ class Model;
#pragma link C++ class Spectrum;

// Model classes to be saved to hard drive
#pragma link C++ class ProjectModel;

// PDFs inherited from RooAbsPdf
// #pragma link C++ class DampLorentzPdf;
// #pragma link C++ class GaussianPdf;
// #pragma link C++ class LorentzianPdf;
// #pragma link C++ class OrthogonalPdf;
// #pragma link C++ class ParabolaPdf;
#endif
