#include "Bitmap.h"
#include "BitmapInfoHeader.h"
#include "BitmapFileHeader.h"

using namespace std;
using namespace jcs;

namespace jcs {
	Bitmap::Bitmap(int width, int height) : m_width(width), m_height(height), m_pPixels(new uint8_t[width * height * 3]{ 0 }) {}

	Bitmap::~Bitmap() {}

	bool Bitmap::write(string filename) {
		BitmapFileHeader bfh;
		BitmapInfoHeader bih;
	}

	void Bitmap::setPixel(int x, int y, std::uint8_t red, std::uint8_t green, std::uint8_t blue) {

	}
}