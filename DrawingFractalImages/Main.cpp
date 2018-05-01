#include <iostream>
#include "FractalCreator.h"


using namespace jcs;
using namespace std;

int main() {


	int const width = 1600;
	int const height = 900;

	FractalCreator fractalCreator(width, height);

	fractalCreator.addRange(0.0, RGB(0, 0, 0));
	//fractalCreator.addRange(0.5, RGB(14, 128, 255));
	fractalCreator.addRange(1.0, RGB(255, 128, 14));

	// Zoom(X from left, Y from bottom, scale)
	fractalCreator.addZoom(Zoom(587, 212, 0.1));
	fractalCreator.addZoom(Zoom(769, 381, 0.1));

	fractalCreator.run("test.bmp");

	cout << "finished" << endl;
	return 0;
}