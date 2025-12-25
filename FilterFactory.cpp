//
// Created by Максим Долганов on 23.10.25.
//

#include "FilterFactory.h"

#include "filters/CropFilter.h"
#include "filters/GSFilter.h"
#include "filters/NegFilter.h"
#include "filters/SharpFilter.h"
#include "filters/EdgeFilter.h"
#include "filters/GaussianFilter.h"
#include "filters/EmbossFilter.h"

static bool ToInt(const std::string& s, int& out) {
    try {
        size_t pos = 0;
        int v = std::stoi(s, &pos);
        if (pos != s.size()) {
            return false;
        }
        out = v;
        return true;
    } catch (...) {
        return false;
    }
}

static bool ToFloat(const std::string& s, float& out) {
    try {
        size_t pos = 0;
        float v = std::stof(s, &pos);
        if (pos != s.size()) {
            return false;
        }
        out = v;
        return true;
    } catch (...) {
        return false;
    }
}

bool FilterFactory::Build(const std::vector<FilterDescriptor>& filters, Pipeline& out) {
    for (const auto& d : filters) {
        const std::string& name = d.name;

        if (name == "-gs") {
            if (!d.args.empty()) {
                last_error_ = "invalid count of -gs arguments";
                return false;
            }
            out.Add(std::make_unique<GSFilter>());
        } else if (name == "-neg") {
            if (!d.args.empty()) {
                last_error_ = "invalid count of -neg arguments";
                return false;
            }
            out.Add(std::make_unique<NegFilter>());
        } else if (name == "-sharp") {
            if (!d.args.empty()) {
                last_error_ = "invalid count of -sharp arguments";
                return false;
            }
            out.Add(std::make_unique<SharpFilter>());
        } else if (name == "-edge") {
            if (d.args.size() != 1) {
                last_error_ = "invalid count of -edge arguments";
                return false;
            }
            float f = 0.0f;
            if (!ToFloat(d.args[0], f) || !(0 <= f && f <= 1)) {
                last_error_= "bad -edge argument";
                return false;
            }
            out.Add(std::make_unique<EdgeFilter>(f));
        } else if (name == "-blur") {
            if (d.args.size() != 1) {
                last_error_ = "invalid count of -blur arguments";
                return false;
            }
            float sigma = 0.0f;
            if (!ToFloat(d.args[0], sigma) || !(sigma > 0.0f)) {
                last_error_ = "bad -blur argument";
                return false;
            }
            out.Add(std::make_unique<GaussianFilter>(sigma));
        } else if (name == "-crop") {
            if (d.args.size() != 2) {
                last_error_ = "invalid count of -crop arguments";
                return false;
            }
            int w = 0;
            int h = 0;
            if (!ToInt(d.args[0], w) || !ToInt(d.args[1], h) || w <= 0 || h <= 0) {
                last_error_ = "bad -crop args (width and height must be positive ints)";
                return false;
            }
            out.Add(std::make_unique<CropFilter>(w, h));
        } else if (name == "-emboss") {
            if (!d.args.empty()) {
                last_error_ = "invalid count of -emboss arguments";
                return false;
            }
            out.Add(std::make_unique<EmbossFilter>());
        }
    }

    return true;
}
