//
// Created by Максим Долганов on 24.10.25.
//

#ifndef NEGFILTER_H
#define NEGFILTER_H

#include "SimplePixelFilter.h"

class NegFilter : public SimplePixelFilter {
public:
    const int MAXVALUE = 255;
    Pixel Transform(Pixel p) const override;
};



#endif //NEGFILTER_H
