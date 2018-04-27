#include "Bitmap.h"
#include "BitmapInfoHeader.h"
#include "BitmapFileHeader.h"
#include <fstream>

using namespace std;
using namespace jcs;

namespace jcs {
	Bitmap::Bitmap(int width, int height) : m_width(width), m_height(height), m_pPixels(new uint8_t[width * height * 3]{}) {}

	Bitmap::~Bitmap() {}

	bool Bitmap::write(string filename) {
		BitmapFileHeader bfh;
		BitmapInfoHeader bih;

		bfh.filesize = sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader) + (m_width * m_height * 3);
		bfh.dataOffset = sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader);

		bih.width = m_width;
		bih.height = m_height;

		ofstream file;

		file.open(filename, ios::out | ios::binary);
		if (!file) {
			return false;
		}

		file.write((char *)&bfh, sizeof(bfh));
		file.write((char *)&bih, sizeof(bih));
		file.write((char *)m_pPixels.get(), m_width * m_height * 3);

		file.close();
		if (!file) {
			return false;
		}

		return true;
	}

	void Bitmap::setPixel(int x, int y, std::uint8_t red, std::uint8_t green, std::uint8_t blue) {
		uint8_t *pPixel = m_pPixels.get();

		pPixel += 3 * ((m_width * y) + x);

		pPixel[0] = blue;
		pPixel[1] = green;
		pPixel[2] = red;
	}
}