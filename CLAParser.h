//
// Created by Максим Долганов on 23.10.25.
//

#ifndef CLAPARSER_H
#define CLAPARSER_H

#include <string>
#include <vector>

struct FilterDescriptor {
    std::string name;
    std::vector<std::string> args;
};

class CLAParser {
public:
    enum class Code {
        ok = 0,
        NotEnoughArgs,
        BadFilter,
        DuplicateIO,
        Unknown,
    };

    Code Parse(int argc, char** argv);

    const std::string& Input() const noexcept {
        return input_;
    }
    const std::string& Output() const noexcept {
        return output_;
    }
    const std::vector<FilterDescriptor>& Filters() const noexcept {
        return filters_;
    }
    const std::string& LastError() const noexcept {
        return last_error_;
    }

private:
    void SetError(std::string error) {
        last_error_ = std::move(error);
    }
    static inline bool IsFlag(const char* s) {
        return s && s[0] == '-' && s[1] != '\0';
    }
    std::string input_;
    std::string output_;
    std::vector<FilterDescriptor> filters_;
    std::string last_error_;
};



#endif //CLAPARSER_H
