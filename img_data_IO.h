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
        int get_channels();
        int get_height();
        int get_length();
        void save_image();
        double at(int x, int y, int c);
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