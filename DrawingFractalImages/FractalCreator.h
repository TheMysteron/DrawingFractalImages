#pragma once
#ifndef FRACTALCREATOR_H_
#define FRACTALCREATOR_H_

#include <string>
#include "Zoom.h"

namespace jcs {
	class FractalCreator {
	public:
		FractalCreator(int width, int height);
		virtual ~FractalCreator();

	public:
		void calculateIteraton();
		void drawFractal();
		void writeBitmap(std::string fileName);
		void addZoom(const Zoom &zoom);
	};
}

#endif // !FRACTALCREATOR_H_