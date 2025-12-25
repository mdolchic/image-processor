//
// Created by Максим Долганов on 24.10.25.
//

#include "NegFilter.h"

Pixel NegFilter::Transform(Pixel p) const {
    return Pixel{static_cast<uint8_t>(MAXVALUE - p.b), static_cast<uint8_t>(MAXVALUE - p.g), static_cast<uint8_t>(MAXVALUE - p.r)};
}
