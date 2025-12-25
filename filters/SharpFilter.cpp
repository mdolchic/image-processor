//
// Created by Максим Долганов on 24.10.25.
//

#include "SharpFilter.h"

void SharpFilter::Apply(BMPImage& img) {
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
        x = std::max(0, x);
        x = std::min(x, w - 1);
        y = std::max(0, y);
        y = std::min(y, h - 1);
        return im.GetPixel(x, y);
    };

    for (int y = 0; y < h; ++y) {
        Pixel* out = img.RowPtr(y);
        for (int x = 0; x < w; ++x) {
            Pixel c = get(x, y);
            Pixel u = get(x, y - 1);
            Pixel d = get(x, y + 1);
            Pixel l = get(x - 1, y);
            Pixel r = get(x + 1, y);

            int nb = C * c.b - u.b - d.b - l.b - r.b;
            int ng = C * c.g - u.g - d.g - l.g - r.g;
            int nr = C * c.r - u.r - d.r - l.r - r.r;

            out[x] = Pixel{Clamp(nb), Clamp(ng), Clamp(nr)};
        }
    }
}
