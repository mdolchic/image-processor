#include "BMPImage.h"
#include "BMPReader.h"
#include "BMPWriter.h"
#include "FilterFactory.h"
#include "CLAParser.h"
#include "filters/BaseFilter.h"
#include "Pipeline.h"
#include <iostream>

int main(int argc, char** argv) {
    CLAParser cla;
    auto code = cla.Parse(argc, argv);
    if (code != CLAParser::Code::ok) {
        std::cerr << cla.LastError() << std::endl;
        return 1;
    }

    BMPReader reader;
    BMPImage img;
    if (!reader.Read(cla.Input(), img)) {
        std::cerr << "read error: " << reader.LastError() << "\n";
        return 2;
    }

    Pipeline pipe;
    FilterFactory ff;
    if (!ff.Build(cla.Filters(), pipe)) {
        std::cerr << "failed to build filters" << ff.LastError() << "\n";
        return 3;
    }

    pipe.Apply(img);

    BMPWriter writer;
    if (!writer.Write(cla.Output(), img)) {
        std::cerr << "write error: " << writer.LastError() << "\n";
        return 4;
    }

    return 0;
}
