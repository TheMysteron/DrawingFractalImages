#pragma once
#ifndef ZOOMLIST_H_
#define ZOOMLIST_H

#include <vector>
#include <utility>
#include "Zoom.h"

namespace jcs {
	class ZoomList {
	private:
		double m_xCentre{ 0 };
		double m_yCentre{ 0 };
		double m_scale{ 1.0 };
		int m_width{ 0 };
		int m_height{ 0 };
		std::vector<Zoom> zooms;

	public:
		ZoomList(int width, int height);

	public:
		void add(const Zoom &zoom);
		std::pair<double, double> doZoom(int x, int y);
	};

}
#endif // !ZOOMLIST_H_