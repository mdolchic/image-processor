//
// Created by Максим Долганов on 24.10.25.
//

#include "EmbossFilter.h"

void EmbossFilter::Apply(BMPImage& img) {
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

    auto get = [&](int x, int y) -> Pixel {
        if (x < 0 || x >= w || y < 0 || y >= h) {
            return Pixel{0,0,0};
        }
        return im.GetPixel(x, y);
    };

    for (int y = 0; y < h; ++y) {
        Pixel* out = img.RowPtr(y);
        for (int x = 0; x < w; ++x) {
            Pixel p00 = get(x - 1, y - 1);
            Pixel p10 = get(x, y - 1);
            Pixel p20 = get(x + 1, y - 1);
            Pixel p01 = get(x - 1, y);
            Pixel p11 = get(x, y);
            Pixel p21 = get(x + 1, y);
            Pixel p02 = get(x - 1, y + 1);
            Pixel p12 = get(x, y + 1);
            Pixel p22 = get(x + 1, y + 1);
            auto apply = [&](int ch00,int ch10,int ch20, int ch01,int ch11,int ch21, int ch02,int ch12,int ch22) -> uint8_t {
                int v = -2 * ch00 - 1 * ch10 + 0 * ch20 - 1 * ch01 + 1 * ch11 + 1 * ch21 + 0 * ch02 + 1 * ch12 + 2 * ch22;
                v += MID;
                return Clamp(v);
            };

            out[x] = Pixel{apply(p00.b,p10.b,p20.b, p01.b,p11.b,p21.b, p02.b,p12.b,p22.b),apply(p00.g,p10.g,p20.g, p01.g,p11.g,p21.g, p02.g,p12.g,p22.g),apply(p00.r,p10.r,p20.r, p01.r,p11.r,p21.r, p02.r,p12.r,p22.r)};
        }
    }
}
