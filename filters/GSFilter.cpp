//
// Created by Максим Долганов on 24.10.25.
//

#include "GSFilter.h"

Pixel GSFilter::Transform(Pixel p) const {
    float y = C1 * static_cast<float>(p.b) + C2 * static_cast<float>(p.g) + C3 * static_cast<float>(p.r);
    return Pixel{static_cast<uint8_t>(y), static_cast<uint8_t>(y), static_cast<uint8_t>(y)};
}

