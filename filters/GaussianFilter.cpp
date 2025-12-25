//
// Created by Максим Долганов on 24.10.25.
//

#include "GaussianFilter.h"

void GaussianFilter::Apply(BMPImage& img) {
    int w = img.Width();
    int h = img.Height();

    BMPImage src = img;
    const int r = static_cast<int>(std::ceil(3.f * sigma_));
    const float s2 = 2.f * sigma_ * sigma_;

    for (int y = 0; y < h; ++y) {
        Pixel* dst = img.RowPtr(y);
        for (int x = 0; x < w; ++x) {
            float sb = 0.f;
            float sg = 0.f;
            float sr = 0.f;
            float t_sum = 0.f;
            for (int dy = -r; dy <= r; ++dy) {
                for (int dx = -r; dx <= r; ++dx) {
                    int yy = y + dy;
                    int xx = x + dx;
                    if (yy < 0 || yy >= h || xx < 0 || xx >= w) {
                        continue;
                    }
                    float t = std::exp(static_cast<float>(-(dx * dx + dy * dy)) / s2);
                    const Pixel p = src.GetPixel(xx, yy);

                    sb += t * static_cast<float>(p.b);
                    sg += t * static_cast<float>(p.g);
                    sr += t * static_cast<float>(p.r);
                    t_sum += t;
                }
            }

            const float inv = (t_sum > 0.f) ? (1.f / t_sum) : 1.f;
            dst[x] = Pixel{Clamp(static_cast<int>(sb * inv + HALF)),Clamp(static_cast<int>(sg * inv + HALF)),Clamp(static_cast<int>(sr * inv + HALF))};
        }
    }
}
