#ifndef IMG_DATA_IO
#define IMG_DATA_IO

#include <iostream>
#include <filesystem>
#include <string>

using namespace std;
namespace fs = std::filesystem;

class Image{
    public:
        Image(fs::path);
        Image(fs::path, int x, int y, int c);
        Image(fs::path, int x, int y, int c, unsigned char* raw_data);
        // Gets the number of channels in the image
        int get_channels();
        // Gets the image height or y
        int get_height();
        // Gets the image width or x
        int get_width();
        // Saves the image to the set file path
        void save_image();
        // Gets the pixel value at a set x, y and c (channel)
        double at(int x, int y, int c);
        // Gets the gray scale value of a given pixel at a x and y
        double at_grey(int x, int y);
        // Sets the double value of a given pixel at x and y
        void set(double value, int x, int y, int c);
        std::string get_file_path();
        ~Image();
    private:
        double* u_eight_to_double(unsigned char*, int);
        unsigned char* double_to_u_eight(double*, int);
        fs::path _file_path;
        double* _colors_d;
        int _total_elements;
        int _width;
        int _height;
        int _channels;
};

#endif