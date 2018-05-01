#pragma once
#ifndef FRACTALCREATOR_H_
#define FRACTALCREATOR_H_

#include <string>
#include <memory>
#include <vector>
#include "Bitmap.h"
#include "Mandelbrot.h"
#include "ZoomList.h"
#include "RGB.h"

namespace jcs {
	class FractalCreator {
	private:
		int const m_width;
		int const m_height;
		std::unique_ptr<int[]> m_histogram;
		std::unique_ptr<int[]> m_fractal;
		Bitmap m_bitmap;
		ZoomList m_zoomList;
		int m_total{ 0 };
		std::vector<int> m_ranges;
		std::vector<RGB> m_colours;
		std::vector<int> m_rangeTotals;
		bool m_bGotFirstRange{ false };

	private:
		void calculateIteraton();
		void calcualteTotalIterations();
		void calculateRangeTotals();
		void drawFractal();
		void writeBitmap(std::string fileName);
		int getRange(int iterations) const;

	public:
		FractalCreator(int width, int height);
		virtual ~FractalCreator();

	public:
		void run(std::string filename);
		void addZoom(const Zoom &zoom);
		void addRange(double rangeEnd, const RGB &rgb);
	};
}

#endif // !FRACTALCREATOR_H_