#ifndef IMG_DATA_IO
#define IMG_DATA_IO

#include <iostream>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

class Image{
    public:
        Image(fs::path);
        Image(fs::path, int, int, int, unsigned char*);
        unsigned char* get_data();
        int get_channels();
        int get_height();
        int get_length();
        void save_image();
        ~Image();
    private:
        unsigned char* copy_color_data(unsigned char*);
        fs::path _file_path;
        bool _from_stbi;
        unsigned char* _colors;
        int _length;
        int _height;
        int _channels;
};

#endif