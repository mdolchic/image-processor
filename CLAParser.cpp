//
// Created by Максим Долганов on 23.10.25.
//

#include "CLAParser.h"

CLAParser::Code CLAParser::Parse(int argc, char** argv) {
    last_error_.clear();
    filters_.clear();
    input_.clear();
    output_.clear();

    if (argc == 0) {
        SetError("help");
        return Code::NotEnoughArgs;
    }

    if (argc < 2) {
        SetError("not enough args: usage: app input.bmp output.bmp [filters]");
        return Code::NotEnoughArgs;
    }

    input_  = argv[1] ? std::string(argv[1]) : std::string();
    output_ = argv[2] ? std::string(argv[2]) : std::string();
    if (input_.empty() || output_.empty()) {
        SetError("input/output empty");
        return Code::NotEnoughArgs;
    }

    int i = 3;
    while (i < argc) {
        const char* cur = argv[i];
        if (!IsFlag(cur)) {
            SetError(std::string("unexpected token: '") + cur + "'");
            return Code::Unknown;
        }

        std::string name = cur;
        ++i;
        std::vector<std::string> args;
        while (i < argc && argv[i] && !IsFlag(argv[i])) {
            args.emplace_back(argv[i]);
            ++i;
        }

        filters_.push_back({std::move(name), std::move(args)});
    }
    return Code::ok;
}
