//
// Created by Максим Долганов on 24.10.25.
//

#ifndef EDGEFILTER_H
#define EDGEFILTER_H

#include "BaseFilter.h"

class EdgeFilter : public BaseFilter {
public:
    explicit EdgeFilter(float threshold) : thr_(static_cast<uint8_t>(threshold * static_cast<float>(MAXVALUE))) {}
    void Apply(BMPImage& img) override;
    ~EdgeFilter() override = default;
private:
    uint8_t thr_;
};



#endif //EDGEFILTER_H
