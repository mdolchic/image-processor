//
// Created by Максим Долганов on 23.10.25.
//

#include "Pipeline.h"

void Pipeline::Add(std::unique_ptr<BaseFilter> f) {
    filters_.push_back(std::move(f));
}

void Pipeline::Apply(BMPImage& img) const {
    for (auto& f : filters_) {
        f->Apply(img);
    }
}


size_t Pipeline::Size() const {
    return filters_.size();
}

void Pipeline::Clear() noexcept {
    filters_.clear();
}



