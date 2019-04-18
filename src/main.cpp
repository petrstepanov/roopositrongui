#include <TROOT.h>
#include <TApplication.h>
#include <TGFrame.h>

#include "resources/Constants.h"
#include "views/MyMainFrame.h"

int main(int argc, char **argv) {
	TApplication* app = new TApplication(Constants::applicationName, &argc, argv);

	// MyMainFrame inherited from TGMainWindow. It sets icon, title, resizes, maps the window.
	MyMainFrame* myMainFrame = new MyMainFrame();
	// SWCalculatorView* swCalculatorView = new SWCalculatorView(myMainFrame);
	// myMainFrame->addChildFrame(swCalculatorView);
	myMainFrame->show();

	app->Run();
	return 0;
}
