//
// Created by Максим Долганов on 20.10.25.
//

#include "BMPWriter.h"
#include <fstream>

bool BMPWriter::Write(const std::string& path, const BMPImage& img) {
    last_error_.clear();
    const int width = img.Width();
    const int height = img.Height();
    if (width <= 0 || height <= 0) {
        SetError("empty image");
        return false;
    }
    if (img.Size() != static_cast<size_t>(width) * static_cast<size_t>(height)) {
        SetError("data size mismatch");
        return false;
    }

    const uint32_t stride = RowStrideBytes24(width);
    const uint32_t pixel_bytes = stride * height;
    constexpr uint32_t OFFBITS = BMPFileHeaderSize + BMPInfoHeaderSize;
    const uint32_t file_size = pixel_bytes + OFFBITS;

    unsigned char fh[BMPFileHeaderSize] = {};
    fh[0] = 'B';
    fh[1] = 'M';
    PutU32(&fh[2], file_size);
    PutU32(&fh[2+ShiftByte1], OFFBITS);

    unsigned char info[BMPInfoHeaderSize] = {};
    PutU32(&info[0], NeedBiSize);
    Put32(&info[4], width);
    Put32(&info[ShiftByte1], height);
    PutU16(&info[4+ShiftByte1], 1u);
    PutU16(&info[2*ShiftByte1-2], static_cast<uint16_t>(NeedBiBitCnt));
    PutU32(&info[2*ShiftByte1], 0u);
    PutU32(&info[2*ShiftByte1+4], pixel_bytes);
    Put32 (&info[3*ShiftByte1], 0);
    Put32 (&info[3*ShiftByte1+4], 0);
    PutU32(&info[4*ShiftByte1], 0);
    PutU32(&info[4*ShiftByte1+4], 0);

    std::ofstream f(path, std::ios::binary);
    if (!f) {
        SetError("cannot open for write");
        return false;
    }

    if (!f.write(reinterpret_cast<const char*>(fh), static_cast<std::streamsize>(BMPFileHeaderSize))) {
        SetError("write file header");
        return false;
    }
    if (!f.write(reinterpret_cast<const char*>(info), static_cast<std::streamsize>(BMPInfoHeaderSize))) {
        SetError("write info header");
        return false;
    }
    const auto& px = img.GetPixels();
    const uint32_t row_bytes = static_cast<uint32_t>(width) * 3u;
    const uint32_t pad_bytes = stride - row_bytes;
    constexpr unsigned char ZERO[3] = {0, 0, 0};

    for (int y = height - 1; y >= 0; --y) {
        const size_t base = static_cast<size_t>(y) * static_cast<size_t>(width);
        for (int x = 0; x < width; ++x) {
            const Pixel& p = px[base + static_cast<size_t>(x)];
            unsigned char bgr[3] = {static_cast<unsigned char>(p.b), static_cast<unsigned char>(p.g), static_cast<unsigned char>(p.r)};
            if (!f.write(reinterpret_cast<const char*>(bgr), 3)) {
                SetError("write pixel data");
                return false;
            }
        }
        if (pad_bytes) {
            if (!f.write(reinterpret_cast<const char*>(ZERO), static_cast<std::streamsize>(pad_bytes))) {
                SetError("write row padding");
                return false;
            }
        }
    }
    return true;
}

const std::string& BMPWriter::LastError() const noexcept {
    return last_error_;
}
