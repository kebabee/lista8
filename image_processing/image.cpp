#include "image.h"

#include <fstream>
#include <filesystem>
#include <iostream>
#include <stdexcept>
#include <cmath>
#include <algorithm>

void Image::load(const std::string& filename) {
    constexpr auto MAGIC = "P6";

    this->filename = filename;

    std::ifstream in(filename, std::ios::binary);
    if (!in) throw std::invalid_argument("failed to open \"" + filename + "\"");

    in >> magic;
    if (magic != MAGIC) throw std::logic_error("unknown magic number " + magic);

    in >> my_width >> my_height >> color_depth;

    if (!in || my_width < 0 || my_width > 10000 || my_height < 0 || my_height > 10000 || color_depth <= 0 ||
        color_depth > 255)
        throw std::logic_error("invalid image parameter(s): " + std::to_string(my_width) + " " + std::to_string(my_height) + " " + std::to_string(color_depth));
    in.ignore(1);
    pixels.resize(my_height);
    for (auto& line : pixels)
    {
        line.resize(my_width);
        in.read(reinterpret_cast<char*>(&line[0]), my_width * sizeof(RGB));
        if (!in) throw std::logic_error("failed to read binary pixel data from file " + filename);
    }
}

void Image::save_as(const std::string& filename) {
    constexpr auto MAGIC = "P6";

    this->filename = filename;

    std::ofstream out(filename, std::ios::binary);
    if (!out) throw std::invalid_argument("failed to open \"" + filename + "\" for writing");

    out << MAGIC;
    if (magic != MAGIC) throw std::logic_error("unknown magic number " + magic);

    out <<"\n"  << my_width << " " << my_height << "\n" << color_depth << "\n";

    if (!out || my_width < 0 || my_width > 10000 || my_height < 0 || my_height > 10000 || color_depth <= 0 ||
        color_depth > 255)
        throw std::logic_error("invalid image parameter(s): " + std::to_string(my_width) + " " + std::to_string(my_height) + " " + std::to_string(color_depth));

    pixels.resize(my_height);
    for (auto& line : pixels)
    {
        line.resize(my_width);
        out.write(reinterpret_cast<char*>(&line[0]), my_width * sizeof(RGB));
        if (!out) throw std::logic_error("failed to write binary pixel data to file " + filename);
    }
}

void Image::to_grayscale() {
    for (int i = 0; i < my_height; i++) {
        for (int j = 0; j < my_width; j++) {

            int avr = (pixels[i][j].red + pixels[i][j].green + pixels[i][j].blue) / 3;
            pixels[i][j].red = avr;
            pixels[i][j].green = avr;
            pixels[i][j].blue = avr;
        }
    }
}

void Image::sepia() {
    for (int i = 0; i < my_height; i++) {
        for (int j = 0; j < my_width; j++) {

            int avr = (pixels[i][j].red + pixels[i][j].green + pixels[i][j].blue) / 3;
            pixels[i][j].red = avr;
            pixels[i][j].green = avr;
            pixels[i][j].blue = avr;

            // wartości używane w gimpie do tworzenia sepii, znalezione w internecie 
            double newRed = avr*1.07;
            double newGreen = avr*0.74;
            double newBlue = avr*0.43;

            pixels[i][j].red = std::min(newRed, 255.0);
            pixels[i][j].green = newGreen;
            pixels[i][j].blue = newBlue;
        }
    }
}

void Image::negative() {
    for (int i = 0; i < my_height; i++) {
        for (int j = 0; j < my_width; j++) {
            pixels[i][j].red = 255 - pixels[i][j].red;
            pixels[i][j].green = 255 - pixels[i][j].green;
            pixels[i][j].blue = 255 - pixels[i][j].blue;
        }
    }
}

void Image::extract_layer(ColorLayer layer) {
    for (int i = 0; i < my_height; i++) {
        for (int j = 0; j < my_width; j++) {
            if (layer == ColorLayer::Red)
            {
                pixels[i][j].green = 0;
                pixels[i][j].blue = 0;
            }
            else if (layer == ColorLayer::Green)
            {
                pixels[i][j].red = 0;
                pixels[i][j].blue = 0;
            }
            else // Blue
            {
                pixels[i][j].red = 0;
                pixels[i][j].green = 0;
            }
        }
    }
}

void Image::add_watermark() {
    for (int i = 1; i < 300; i++) {
        for (int j = 1; j < 300; j++) {
            pixels[i][j].red = 255;
            pixels[i][j].green = 0;
            pixels[i][j].blue = 0;
        }
    }
}

void Image::flip_vertically() {
  for (int i = 0; i < my_height; i++) {
    std::reverse(pixels[i].begin(), pixels[i].end());
  }
}

void Image::flip_horizontally() {
    for (int i = 0; i < std::floor(my_height / 2); i++) {
        for (int j = 0; j < my_width; j++) {
            std::swap(pixels[i][j], pixels[my_height - 1 - i][j]);
        }
    }
}

void Image::filter() {
    for (int i = 0; i < my_height - 1; i++) {
        for (int j = 0; j < my_width - 1; j++) {
            int redDif = abs(pixels[i][j].red - pixels[i+1][j+1].red);
            int greenDif = abs(pixels[i][j].green - pixels[i+1][j+1].green);
            int blueDif = abs(pixels[i][j].blue - pixels[i+1][j+1].blue);

            pixels[i][j].red = redDif;
            pixels[i][j].green = greenDif;
            pixels[i][j].blue = blueDif;
        }
    }
}

void Image::blurr() {
    for (int i = 0; i <= my_height; i++) {
        for (int j = 0; j <= my_width; j++) {
            int avrRed = 0;
            int avrGreen = 0;
            int avrBlue = 0;
            for (int k = std::abs(i - 1); k <= std::min(i + 1, my_height); k++){ //abs i min aby omijać piksele za brzegami obrazka
                for (int l = std::abs(j - 1); l <= std::min(j + 1, my_width); l++) {
                    avrRed += pixels[k][l].red;
                    avrGreen += pixels[k][l].green;
                    avrBlue += pixels[k][l].blue;
                }
            }
            pixels[i][j].red = avrRed/9;
            pixels[i][j].green = avrGreen/9;
            pixels[i][j].blue = avrBlue/9;
        }
    }
}

void Image::inflate() {
    int newWidth = my_width * 2;
    int newHeight = my_height * 2;
    std::vector<std::vector<RGB>> newPix(newHeight, std::vector<RGB>(newWidth)); 
    // ^^ wektor wektorów do przechowania nowych pikseli przed przypisaniem do obrazka

    for (int i = 0; i < my_height; i++) {
        for (int j = 0; j < my_width; j++) {
            newPix[2*i][2*j] = pixels[i][j];
            newPix[2*i][2*j+1] = pixels[i][j];
            newPix[2*i+1][2*j] = pixels[i][j];
            newPix[2*i+1][2*j+1] = pixels[i][j];
        }
    }
    my_width = newWidth;
    my_height = newHeight;
    pixels = newPix;
}

void Image::shrink() {
    int newWidth = my_width / 2;
    int newHeight = my_height / 2;
    std::vector<std::vector<RGB>> newPix(newHeight, std::vector<RGB>(newWidth)); 

    for (int i = 0; i < newHeight; i++) {
        for (int j = 0; j < newWidth; j++) {
            // średnie składowych kolorów z czterech sąsiadujących pikseli
            int avgRed = (pixels[2*i][2*j].red + pixels[2*i][2*j+1].red + pixels[2*i+1][2*j].red + pixels[2*i+1][2*j+1].red) / 4;
            int avgGreen = (pixels[2*i][2*j].green + pixels[2*i][2*j+1].green + pixels[2*i+1][2*j].green + pixels[2*i+1][2*j+1].green) / 4;
            int avgBlue = (pixels[2*i][2*j].blue + pixels[2*i][2*j+1].blue + pixels[2*i+1][2*j].blue + pixels[2*i+1][2*j+1].blue) / 4;

            newPix[i][j].red = avgRed;
            newPix[i][j].green = avgGreen;
            newPix[i][j].blue = avgBlue;
        }
    }
    pixels = newPix;
    my_height = newHeight;
    my_width = newWidth;
}

void Image::rotate_clockwise_90()
{
    std::vector<std::vector<RGB>> newPix(my_width, std::vector<RGB>(my_height));

    for (int i = 0; i < my_height; i++)
    {
        for (int j = 0; j < my_width; j++)
        {
            newPix[j][my_height-i-1] = pixels[i][j];
        }
    }
    pixels = newPix;
    int h = my_height;
    my_height = my_width;
    my_width = h;
}