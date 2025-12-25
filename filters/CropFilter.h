//
// Created by Максим Долганов on 24.10.25.
//

#ifndef CROPFILTER_H
#define CROPFILTER_H

#include "BaseFilter.h"

class CropFilter : public BaseFilter {
public:
    CropFilter(int w, int h) : w_(w), h_(h) {}
    void Apply(BMPImage& img) override;
private:
    int w_, h_;
};



#endif //CROPFILTER_H
