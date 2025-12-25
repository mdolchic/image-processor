//
// Created by Максим Долганов on 24.10.25.
//

#include "CropFilter.h"

void CropFilter::Apply(BMPImage& img) {
    const int w = img.Width();
    const int h = img.Height();
    const int wn = std::max(0, std::min(w_, w));
    const int hn = std::max(0, std::min(h_, h));
    if (wn == w && hn == h) {
        return;
    }

    BMPImage out(wn, hn);
    for (int y = 0; y < hn; ++y) {
        const Pixel* src = img.RowPtr(y);
        Pixel* dst = out.RowPtr(y);
        std::copy(src, src + wn, dst);
    }
    img = std::move(out);
}