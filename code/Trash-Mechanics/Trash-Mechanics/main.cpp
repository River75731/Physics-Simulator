#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <iostream>
#include <vector>
#include "Common.h"
#include "View-Polygon.h"

int main(int argc, char *argv[])
{
	Fl_Window  *window;
	Fl_Box  *box;
	window = new  Fl_Window(450, 330, "First App!");
	box = new Fl_Box(20, 40, 360, 200, "Hello World");
	box->box(FL_FLAT_BOX);
	box->labelsize(36);
	box->labelfont(FL_BOLD + FL_ITALIC);

	std::vector<Vec> v;
	v.push_back(Vec(50, 50));
	v.push_back(Vec(100, 200));
	v.push_back(Vec(150, 50));
	Fl_Poly* p1 = new Fl_Poly(v);

	std::vector<Vec> v2;
	v2.push_back(Vec(250, 150));
	v2.push_back(Vec(300, 200));
	v2.push_back(Vec(350, 150));
	v2.push_back(Vec(300, 50));
	Fl_Poly* p2 = new Fl_Poly(v2,FL_RED);

	free(p1);

	box->labeltype(FL_SHADOW_LABEL);
	window->end();
	window->show(argc, argv);
	return  Fl::run();
}