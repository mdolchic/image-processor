//
// Created by Максим Долганов on 24.10.25.
//

#include "SimplePixelFilter.h"

void SimplePixelFilter::Apply(BMPImage& img) {
    auto& v = img.GetPixels();
    for (auto& px : v) {
        px = Transform(px);
    }
}