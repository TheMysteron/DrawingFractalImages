#pragma once
#ifndef BITMAPFILEHEADER_H_
#define BITMAPFILEHEADER_H_

#include <cstdint>

#pragma pack(push, 2)

namespace jcs {
	struct BitmapFileHeader {
		char header[2]{ 'B','M' };
		std::int32_t filesize;
		std::int32_t reserved{ 0 };
		std::int32_t dataOffset;
	};
}

#pragma pack(pop)

#endif // !BITMAPFILEHEADER_H_