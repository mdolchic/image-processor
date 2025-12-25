//
// Created by Максим Долганов on 20.10.25.
//

#ifndef BMPWRITER_H
#define BMPWRITER_H

#include "BMPImage.h"

class BMPWriter {
public:
    bool Write(const std::string& path, const BMPImage& image);
    const std::string& LastError() const noexcept;
    const int ShiftByte1 = 8;
    const int ShiftByte2 = 16;
    const int ShiftByte3 = 24;
    const int Full8Bits = 0xFF;
    static constexpr int BMPFileHeaderSize = 14;
    static constexpr int BMPInfoHeaderSize = 40;
    const int BfType = 0x4D42;
    const uint32_t NeedBiSize = 40u;
    const int NeedBiBitCnt = 24;
private:
    void PutU16(unsigned char* p, uint16_t x) const {
        p[0] = static_cast<unsigned char>(x & Full8Bits);
        p[1] = static_cast<unsigned char>((x >> ShiftByte1) & Full8Bits);
    }
    void PutU32(unsigned char* p, uint32_t x) const {
        p[0] = static_cast<unsigned char>(x & Full8Bits);
        p[1] = static_cast<unsigned char>((x >> ShiftByte1) & Full8Bits);
        p[2] = static_cast<unsigned char>((x >> ShiftByte2) & Full8Bits);
        p[3] = static_cast<unsigned char>((x >> ShiftByte3) & Full8Bits);
    }
    void Put32(unsigned char* p, int32_t x) const {
        PutU32(p, static_cast<uint32_t>(x));
    }
    static uint32_t RowStrideBytes24(int width) {
        const uint32_t raw = static_cast<uint32_t>(width) * 3u;
        return (raw + 3u) & ~3u;
    }
    void SetError(std::string msg) {
        last_error_ = std::move(msg);
    }
    std::string last_error_;
};



#endif //BMPWRITER_H
