#include <utility>
#include <assert.h>
#include "FractalCreator.h"

using namespace std;

namespace jcs {
	void FractalCreator::run(string fileName) {
		calculateIteraton();
		calcualteTotalIterations();
		calculateRangeTotals();
		drawFractal();
		writeBitmap(fileName);
	}

	void FractalCreator::addZoom(const Zoom & zoom) {
		m_zoomList.add(zoom);
	}

	void FractalCreator::addRange(double rangeEnd, const RGB &rgb) {
		m_ranges.push_back((int)(rangeEnd * Mandelbrot::MAX_ITERATIONS));
		m_colours.push_back(rgb);

		if (m_bGotFirstRange) {
			m_rangeTotals.push_back(0);
		}
		m_bGotFirstRange = true;
	}

	FractalCreator::FractalCreator(int width, int height) :
		m_width(width), m_height(height),
		m_histogram(new int[Mandelbrot::MAX_ITERATIONS]()),
		m_fractal(new int[m_width * m_height]()),
		m_bitmap(m_width, m_height),
		m_zoomList(m_width, m_height) {

		addZoom(Zoom(m_width / 2, m_height / 2, 4.0 / m_width));
	}

	FractalCreator::~FractalCreator() {}

	void FractalCreator::calculateIteraton() {
		for (int x = 0; x < m_width; x++) {
			for (int y = 0; y < m_height; y++) {

				pair<double, double> coords = m_zoomList.doZoom(x, y);
				int iterations = Mandelbrot::getIterations(coords.first, coords.second);
				m_fractal[(y * m_width) + x] = iterations;

				if (iterations != Mandelbrot::MAX_ITERATIONS) {
					m_histogram[iterations]++;
				}
			}
		}
	}

	void FractalCreator::calcualteTotalIterations() {
		for (int i = 0; i < Mandelbrot::MAX_ITERATIONS; i++) {
			m_total += m_histogram[i];
		}
	}

	void FractalCreator::drawFractal() {
		for (int x = 0; x < m_width; x++) {
			for (int y = 0; y < m_height; y++) {

				uint8_t red = 0;
				uint8_t green = 0;
				uint8_t blue = 0;

				int iterations = m_fractal[(y * m_width) + x];

				int range = getRange(iterations);
				int rangeTotal = m_rangeTotals[range];
				int rangeStart = m_ranges[range];

				RGB &startColour = m_colours[range];
				RGB &endColour = m_colours[range + 1];
				RGB colourDiff = endColour - startColour;

				if (iterations != Mandelbrot::MAX_ITERATIONS) {

					int totalPixels = 0;

					for (int i = rangeStart; i <= iterations; i++) {
						totalPixels += m_histogram[i];
					}

					red = (uint8_t)(pow(colourDiff.r, (double)totalPixels / rangeTotal) + startColour.r);
					green = (uint8_t)(pow(colourDiff.g, (double)totalPixels / rangeTotal) + startColour.g);
					blue = (uint8_t)(pow(colourDiff.b, (double)totalPixels / rangeTotal) + startColour.b);
				}

				m_bitmap.setPixel(x, y, red, green, blue);
			}
		}
	}

	void FractalCreator::writeBitmap(string fileName) {
		m_bitmap.write(fileName);
	}

	int FractalCreator::getRange(int iterations) const {
		int range = 0;

		for (int i = 1; i < m_ranges.size(); i++) {
			range = i;

			if (m_ranges[i] > iterations) {
				break;
			}
		}

		range--;

		assert(range > -1);
		assert(range < m_ranges.size());

		return range;
	}

	void FractalCreator::calculateRangeTotals() {
		int rangeIndex = 0;

		for (int i = 0; i < Mandelbrot::MAX_ITERATIONS; i++) {
			int pixels = m_histogram[i];

			if (i >= m_ranges[rangeIndex + 1]) {
				rangeIndex++;
			}

			m_rangeTotals[rangeIndex] += pixels;
		}
	}
}