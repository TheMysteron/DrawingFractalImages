#include <iostream>
#include <cstdint>
#include <memory>
#include <math.h>
#include "Bitmap.h"
#include "Mandelbrot.h"
#include "ZoomList.h"
#include "FractalCreator.h"


using namespace jcs;
using namespace std;

int main() {

	int const WIDTH = 1600;
	int const HEIGHT = 900;

	Bitmap bitmap(WIDTH, HEIGHT);
	double min = 999999;
	double max = -999999;

	ZoomList zoomList(WIDTH, HEIGHT);
	zoomList.add(Zoom(WIDTH / 2, HEIGHT / 2, 1));

	FractalCreator fractalCreator(WIDTH, HEIGHT);


	unique_ptr<int[]> histogram(new int[Mandelbrot::MAX_ITERATIONS]{});
	unique_ptr<int[]> fractal(new int[WIDTH * HEIGHT]{});

	for (int x = 0; x < WIDTH; x++) {
		for (int y = 0; y < HEIGHT; y++) {

			pair<double, double> coords = zoomList.doZoom(x, y);

			int iterations = Mandelbrot::getIterations(coords.first, coords.second);

			fractal[(y * WIDTH) + x] = iterations;

			if (iterations != Mandelbrot::MAX_ITERATIONS) {
				histogram[iterations]++;
			}
		}
	}

	int total = 0;
	for (int i = 0; i < Mandelbrot::MAX_ITERATIONS; i++) {
		total += histogram[i];
	}

	for (int x = 0; x < WIDTH; x++) {
		for (int y = 0; y < HEIGHT; y++) {

			uint8_t red = 0;
			uint8_t green = 0;
			uint8_t blue = 0;

			int iterations = fractal[(y * WIDTH) + x];

			if (iterations != Mandelbrot::MAX_ITERATIONS) {

				double hue = 0.0;
				for (int i = 0; i <= iterations; i++) {
					hue += (double)histogram[i] / total;
				}

				red = 0;
				green = (uint8_t)pow(255, hue);
				blue = 0;
			}

			bitmap.setPixel(x, y, red, green, blue);
		}
	}

	bitmap.write("test.bmp");

	cout << "finished" << endl;
	return 0;
}