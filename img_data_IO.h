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
        Image(fs::path, int, int, int);
        Image(fs::path, int, int, int, unsigned char*);
        //unsigned char* get_data();
        int get_channels();
        int get_height();
        int get_length();
        void save_image();
        double at(int x, int y, int c);
        void set(double value, int x, int y, int c);
        std::string get_file_path();
        ~Image();
    private:
        //unsigned char* copy_color_data(unsigned char*);
        double* u_eight_to_double(unsigned char*, int);
        unsigned char* double_to_u_eight(double*, int);
        fs::path _file_path;
        //bool _from_stbi;
        //unsigned char* _colors;
        double* _colors_d;
        int _total_elements;
        int _length;
        int _height;
        int _channels;
};

#endif