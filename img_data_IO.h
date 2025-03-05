#ifndef IMG_DATA_IO
#define IMG_DATA_IO

#include <iostream>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

struct img_colors{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
    unsigned char alpha;
};

struct image
{
    img_colors* colors;
    int length;
    int height;
    int channels;
};

image getImage(fs::path);
void saveImage(image, fs::path);

#endif