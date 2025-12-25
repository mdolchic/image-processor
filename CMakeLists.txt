cmake_minimum_required(VERSION 3.15)
project(image_processor LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_executable(
    image_processor
        image_processor.cpp
        BMPImage.h
        BMPImage.cpp
        BMPReader.cpp
        BMPReader.h
        BMPWriter.cpp
        BMPWriter.h
        CLAParser.cpp
        CLAParser.h
        filters/BaseFilter.cpp
        filters/BaseFilter.h
        Pipeline.cpp
        Pipeline.h
        FilterFactory.cpp
        FilterFactory.h
        filters/SimplePixelFilter.cpp
        filters/SimplePixelFilter.h
        filters/GSFilter.cpp
        filters/GSFilter.h
        filters/NegFilter.cpp
        filters/NegFilter.h
        filters/CropFilter.cpp
        filters/CropFilter.h
        filters/SharpFilter.cpp
        filters/SharpFilter.h
        filters/EdgeFilter.cpp
        filters/EdgeFilter.h
        filters/GaussianFilter.cpp
        filters/GaussianFilter.h
        filters/EmbossFilter.cpp
        filters/EmbossFilter.h
)
