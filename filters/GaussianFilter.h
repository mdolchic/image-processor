//
// Created by Максим Долганов on 24.10.25.
//

#ifndef GAUSSIANFILTER_H
#define GAUSSIANFILTER_H

#include "BaseFilter.h"

class GaussianFilter : public BaseFilter {
public:
    explicit GaussianFilter(float sigma) : sigma_(sigma) {}
    ~GaussianFilter() override = default;
    void Apply(BMPImage& img) override;
    const float HALF = 0.5f;
private:
    float sigma_;
};



#endif //GAUSSIANFILTER_H
