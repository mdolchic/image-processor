//
// Created by Максим Долганов on 20.10.25.
//

#ifndef BMPIMAGE_H
#define BMPIMAGE_H

#include <vector>
#include <stdexcept>

struct Pixel {
    uint8_t b, g, r;
    Pixel() noexcept;
    Pixel(uint8_t bb, uint8_t gg, uint8_t rr) noexcept;
};

class BMPImage {
public:
    BMPImage() noexcept;
    BMPImage(int width, int height);

    int Width() const noexcept;
    int Height() const noexcept;
    bool Empty() const noexcept;
    size_t Size() const noexcept;

    const std::vector<Pixel>& GetPixels() const noexcept;
    std::vector<Pixel>& GetPixels() noexcept;

    const Pixel* RowPtr(int y) const;
    Pixel* RowPtr(int y);

    Pixel GetPixel(int x, int y) const;
    void SetPixel(int x, int y, Pixel pixel);

    void Clear();

    void Resize(int w, int h);
private:
    int width_{0};
    int height_{0};
    std::vector<Pixel> pixels_;
    void CheckXY(int x, int y) const {
        if (x < 0 || y < 0 || x >= width_ || y >= height_) {
            throw std::out_of_range("BMPImage::index out of range");
        }
    }
    void CheckY(int y) const {
        if (y < 0 || y >= height_) {
            throw std::out_of_range("BMPImage::index out of range");
        }
    }
};

#endif  // BMPIMAGE_H
