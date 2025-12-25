//
// Created by Максим Долганов on 23.10.25.
//

#ifndef FILTERFACTORY_H
#define FILTERFACTORY_H

#include "Pipeline.h"
#include "CLAParser.h"
#include <functional>

class FilterFactory {
public:
    bool Build(const std::vector<FilterDescriptor>& filters, Pipeline& out);
    const std::string& LastError() const noexcept {
        return last_error_;
    }
private:
    using Maker = std::function<bool(std::vector<std::string>&, Pipeline&)>;
    std::unordered_map<std::string, Maker> makers_;
    std::string last_error_;

};



#endif //FILTERFACTORY_H
