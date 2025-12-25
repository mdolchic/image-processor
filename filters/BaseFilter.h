//
// Created by Максим Долганов on 23.10.25.
//

#ifndef BASEFILTER_H
#define BASEFILTER_H

#include "../BMPImage.h"

class BaseFilter {
public:
    const int MAXVALUE = 255;
    const int MINVALUE = 0;
    inline uint8_t Clamp(int v) const {
        return v < MINVALUE ? MINVALUE : (v > MAXVALUE ? MAXVALUE : static_cast<uint8_t>(v));
    }
    virtual ~BaseFilter() = default;
    virtual void Apply(BMPImage& img) {}
};


#endif //BASEFILTER_H
