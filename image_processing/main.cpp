#include "image.h"
#include <iostream>
#include "image.cpp"

int main()
{
    Image image;

    //przykłądowe testy
    image.load("obrazek.ppm");
    image.to_grayscale();
    image.save_as("greyscale.ppm");
    
    image.load("obrazek.ppm");
    image.sepia();
    image.save_as("sepia.ppm");

    image.load("tree.ppm");
    image.sepia();
    image.save_as("sepia1.ppm");

    image.load("obrazek.ppm");
    image.negative();
    image.save_as("negative.ppm");

    image.load("obrazek.ppm");
    image.extract_layer(ColorLayer::Red);
    image.save_as("redLayer.ppm");

    image.load("obrazek.ppm");
    image.extract_layer(ColorLayer::Blue);
    image.save_as("blueLayer.ppm");

    image.load("obrazek.ppm");
    image.add_watermark();
    image.save_as("watermark.ppm");

    image.load("obrazek.ppm");
    image.flip_horizontally();
    image.save_as("flipHor.ppm");

    image.load("obrazek.ppm");
    image.flip_vertically();
    image.save_as("flipVer.ppm");

    image.load("tree.ppm");
    image.filter();
    image.save_as("filter.ppm");

    image.load("tree.ppm");
    for(int i = 0; i < 30; i++) {
        image.blurr();
    }
    image.save_as("blurr.ppm");

    image.load("obrazek.ppm");
    std::cout << "Wymiary bazowe: " << image.height() << " x " << image.width();
    image.inflate();
    std::cout << ", po .inflate(): " << image.height() << " x " << image.width() << std::endl;
    image.save_as("scaleUp.ppm");

    image.load("obrazek.ppm");
    std::cout << "Wymiary bazowe: " << image.height() << " x " << image.width();
    image.shrink();
    std::cout << ", po .shrink(): " << image.height() << " x " << image.width() << std::endl;
    image.save_as("scaleDown.ppm");

    image.load("obrazek.ppm");
    std::cout << "Wymiary bazowe: " << image.height() << " x " << image.width();
    image.rotate_clockwise_90();
    std::cout << ", po .rotate_clockwise_90(): " << image.height() << " x " << image.width() << std::endl;
    image.save_as("rotate90.ppm");

    return 0;
}
