#include "App.h"

App::App():view(new View), model(new Model), viewmodel(new ViewModel), windows(new Windows)
{
	viewmodel->bind(model);
	viewmodel->bind(view);
	viewmodel->bind(windows);

	windows->setUpdateRigidBodyDataCommand(viewmodel->getUpdateRigidBodyDataCommand()); // bind the view & viewmodel command
	windows->setSimulateTimeFlyDataCommand(viewmodel->getSimulateTimeFlyDataCommand());
	model->setUpdatePolyViewCommand(viewmodel->getUpdatePolyViewCommand()); // bind the view & viewmodel command
}

void App::StartWorld()
{
	return;
}

void App::test()
{
	//View view;
	view->createViewWindow();
	view->m_system.getWINDOW()->show();
	//view->createViewPolygon(1, Poly(std::vector<Vec>{Vec(10, 10), Vec(100, 100), Vec(200, 50)}));
	windows->test();
	Fl::check();
	Fl::redraw();	//windows->test();
	//getchar();
	//while (1) {}
	//model->test();
}

