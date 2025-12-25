//
// Created by Максим Долганов on 23.10.25.
//

#ifndef PIPELINE_H
#define PIPELINE_H
#include "filters/BaseFilter.h"

class Pipeline {
public:
    void Add(std::unique_ptr<BaseFilter> f);
    void Apply(BMPImage& img) const;
    size_t Size() const;
    void Clear() noexcept;
private:
    std::vector<std::unique_ptr<BaseFilter>> filters_;
};


#endif //PIPELINE_H
