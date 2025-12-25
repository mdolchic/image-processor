//
// Created by Максим Долганов on 24.10.25.
//

#ifndef SIMPLEPIXELFILTER_H
#define SIMPLEPIXELFILTER_H

#include "BaseFilter.h"

class SimplePixelFilter : public BaseFilter {
public:
    void Apply(BMPImage& img) override;
protected:
    virtual Pixel Transform(Pixel p) const = 0;
};


#endif //SIMPLEPIXELFILTER_H
