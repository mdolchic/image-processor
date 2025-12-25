//
// Created by Максим Долганов on 19.10.25.
//

#include "BMPReader.h"
#include <fstream>

const std::string& BMPReader::LastError() const noexcept {
    return last_error_;
}

bool BMPReader::Read(const std::string& path, BMPImage& out) {
    last_error_.clear();
    out.Clear();
    std::ifstream f(path, std::ios::binary);
    if (!f) {
        SetError("cannot open file");
        return false;
    }

    unsigned char fh[BMPFileHeaderSize];
    if (!f.read(reinterpret_cast<char*>(fh), BMPFileHeaderSize)) {
        SetError("short read: file header");
        return false;
    }
    if (GetU16(fh + 0) != BfType) {
        SetError("not a BMP");
        return false;
    }
    const uint32_t bf_off_bits = GetU32(fh + 10);

    unsigned char info[BMPInfoHeaderSize];
    if (!f.read(reinterpret_cast<char*>(info), BMPInfoHeaderSize)) {
        SetError("short read: info header");
        return false;
    }
    const uint32_t bi_size = GetU32(info + 0);
    if (bi_size < NeedBiSize) {
        SetError("unsupported DIB header (<40)");
        return false;
    }
    const int32_t bi_width   = Get32(info + 4);
    const int32_t  bi_height  = Get32(info + 8);
    const uint16_t bi_planes  = GetU16(info + 12);
    const uint16_t bi_bit_cnt  = GetU16(info + 14);
    const uint32_t bi_compr   = GetU32(info + 16);
    if (bi_planes != 1) {
        SetError("unsupported: only planes = 1");
        return false;
    }
    if (bi_bit_cnt != NeedBiBitCnt) {
        SetError("unsupported: only 24-bit BMP");
        return false;
    }
    if (bi_compr) {
        SetError("unsupported: only uncompressed BMP");
        return false;
    }
    if (bi_width <= 0) {
        SetError("unsupported: only width > 0");
        return false;
    }
    if (bi_height == 0) {
        SetError("unsupported: only height != 0");
        return false;
    }
    if (bi_size > NeedBiSize) {
        const uint32_t extra = bi_size - NeedBiSize;
        std::vector<char> skip(extra);
        if (!f.read(skip.data(), static_cast<std::streamsize>(extra))) {
            SetError("short read: extended DIB");
            return false;
        }
    }

    f.seekg(static_cast<std::streamoff>(bf_off_bits), std::ios::beg);
    if (!f) {
        SetError("bad bf_off_bits");
        return false;
    }

    out.Resize(bi_width, bi_height);
    const uint32_t stride = RowStrideBytes24(bi_width);
    std::vector<unsigned char> row(stride);

    for (int32_t y = 0; y < bi_height; ++y) {
        if (!f.read(reinterpret_cast<char*>(row.data()), stride)) {
            SetError("short read: row");
            return false;
        }
        int real_y = bi_height - y - 1;
        Pixel* cur = out.RowPtr(real_y);
        const unsigned char* p = row.data();
        for (int x = 0; x < bi_width; ++x) {
            Pixel px;
            px.b = *p++;
            px.g = *p++;
            px.r = *p++;
            cur[x] = px;
        }
    }
    return true;
}