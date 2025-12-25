//
// Created by Максим Долганов on 20.10.25.
//

#include "BMPImage.h"

Pixel::Pixel() noexcept : b(0), g(0), r(0) {}
Pixel::Pixel(uint8_t bb, uint8_t gg, uint8_t rr) noexcept : b(bb), g(gg), r(rr) {}

BMPImage::BMPImage() noexcept = default;
BMPImage::BMPImage(int width, int height) : width_(width), height_(height) {
    if (width < 0 || height < 0) {
        throw std::invalid_argument("Image::Resize: negative size");
    }
    pixels_.resize(width_ * height_);
};

int BMPImage::Width() const noexcept {
    return width_;
}
int BMPImage::Height() const noexcept {
    return height_;
}
bool BMPImage::Empty() const noexcept {
    return pixels_.empty();
}
size_t BMPImage::Size() const noexcept {
    return pixels_.size();
}

const std::vector<Pixel>& BMPImage::GetPixels() const noexcept {
    return pixels_;
}
std::vector<Pixel>& BMPImage::GetPixels() noexcept {
    return pixels_;
}

const Pixel* BMPImage::RowPtr(int y) const {
    CheckY(y);
    return pixels_.data() + static_cast<size_t>(y) * static_cast<size_t>(width_);
}
Pixel* BMPImage::RowPtr(int y) {
    CheckY(y);
    return pixels_.data() + static_cast<size_t>(y) * static_cast<size_t>(width_);
}

Pixel BMPImage::GetPixel(int x, int y) const {
    return pixels_[y * width_ + x];
}
void BMPImage::SetPixel(int x, int y, Pixel pixel) {
    pixels_[y * width_ + x] = pixel;
}

void BMPImage::Clear() {
    width_ = 0;
    height_ = 0;
    pixels_.clear();
}

void BMPImage::Resize(int w, int h) {
    if (w < 0 || h < 0) {
        throw std::invalid_argument("Image::Resize: negative size");
    }
    width_ = w;
    height_ = h;
    pixels_.assign(static_cast<size_t>(w) * static_cast<size_t>(h), Pixel{});
}