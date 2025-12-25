//
// Created by Максим Долганов on 24.10.25.
//

#ifndef SHARPFILTER_H
#define SHARPFILTER_H

#include "BaseFilter.h"

class SharpFilter : public BaseFilter {
public:
    void Apply(BMPImage& img) override;
    ~SharpFilter() override = default;
    const int C = 5;
};



#endif //SHARPFILTER_H
