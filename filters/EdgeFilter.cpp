//
// Created by Максим Долганов on 24.10.25.
//

#include "EdgeFilter.h"

void EdgeFilter::Apply(BMPImage& img) {
    int w = img.Width();
    int h = img.Height();
    BMPImage im(w, h);
    for (int y = 0; y < h; ++y) {
        const Pixel* s = img.RowPtr(y);
        Pixel* d = im.RowPtr(y);
        for (int x = 0; x < w; ++x) {
            d[x] = s[x];
        }
    }

    auto get = [&](int x, int y) -> int {
        x = std::max(x, 0);
        x = std::min(x, w - 1);
        y = std::max(y, 0);
        y = std::min(y, h - 1);
        const Pixel p = im.GetPixel(x, y);
        const int v = static_cast<int>(0.114f * static_cast<float>(p.b) + 0.587f * static_cast<float>(p.g) + 0.299f * static_cast<float>(p.r) + 0.5f);
        return v;
    };

    for (int y = 0; y < h; ++y) {
        Pixel* out = img.RowPtr(y);
        for (int x = 0; x < w; ++x) {
            const int yc = get(x, y);
            const int yu = get(x, y - 1);
            const int yd = get(x, y + 1);
            const int yl = get(x - 1, y);
            const int yr = get(x + 1, y);
            int nw = 4 * yc - yu - yd - yl - yr;
            const uint8_t v = (nw > thr_) ? MAXVALUE : MINVALUE;
            out[x] = Pixel{v, v, v};
        }
    }
}
