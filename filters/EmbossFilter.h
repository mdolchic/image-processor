//
// Created by Максим Долганов on 24.10.25.
//

#ifndef EMBOSSFILTER_H
#define EMBOSSFILTER_H

#include "BaseFilter.h"

class EmbossFilter : public BaseFilter {
public:
    void Apply(BMPImage& img) override;
    ~EmbossFilter() override = default;
    const int MID = 128;
};



#endif //EMBOSSFILTER_H
