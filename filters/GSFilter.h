//
// Created by Максим Долганов on 24.10.25.
//

#ifndef GSFILTER_H
#define GSFILTER_H

#include "SimplePixelFilter.h"

class GSFilter : public SimplePixelFilter {
public:
    const float C1 = 0.114f;
    const float C2 = 0.587f;
    const float C3 = 0.299f;
protected:
    Pixel Transform(Pixel p) const override;
};



#endif //GSFILTER_H
