//
// Created by Максим Долганов on 19.10.25.
//

#ifndef BMPREADER_H
#define BMPREADER_H

#include <cstdint>

struct BMPFileHeader {
    uint16_t bfType;
    uint32_t bfSize;
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bfOffBits;
};

struct BMPInfoHeader {
    uint32_t biSize;
    int32_t  biWidth;
    int32_t  biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    int32_t  biXPelsPerMeter;
    int32_t  biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
};

#include <string>
#include "BMPImage.h"

class BMPReader {
public:
    bool Read(const std::string& path, BMPImage& out);
    const std::string& LastError() const noexcept;
    const int ShiftByte1 = 8;
    const int ShiftByte2 = 16;
    const int ShiftByte3 = 24;
    static constexpr int BMPFileHeaderSize = 14;
    static constexpr int BMPInfoHeaderSize = 40;
    const int BfType = 0x4D42;
    const uint32_t NeedBiSize = 40u;
    const int NeedBiBitCnt = 24;

private:
    inline uint16_t GetU16(const unsigned char* p) const {
        return static_cast<uint16_t>(p[0] | (p[1] << ShiftByte1));
    }
    inline uint32_t GetU32(const unsigned char* p) const {
        return static_cast<uint32_t>(p[0]) | (static_cast<uint32_t>(p[1]) << ShiftByte1) | (static_cast<uint32_t>(p[2]) << ShiftByte2) | (static_cast<uint32_t>(p[3]) << ShiftByte3);
    }
    inline int32_t Get32(const unsigned char* p) const {
        return static_cast<int32_t>(GetU32(p));
    }
    static inline uint32_t RowStrideBytes24(int width) {
        const uint32_t raw = static_cast<uint32_t>(width) * 3u;
        return (raw + 3u) & ~3u;
    }

    std::string last_error_;
    void SetError(std::string msg) {
        last_error_ = std::move(msg);
    }
};



#endif //BMPREADER_H
