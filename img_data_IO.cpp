#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION

#include "stb_image_write.h"
#include "stb_image.h"
#include "img_data_IO.h"

Image::Image(fs::path path){
    _from_stbi = true;
    _file_path = path;
    stbi_uc* raw_load = stbi_load(path.string().c_str(), &_length, &_height, &_channels, 0);
    _colors = (unsigned char*) raw_load; //stbi_uc is unsinged char on the backend.
}

Image::Image(fs::path path, int h, int l, int channels, unsigned char* color_data){
    _from_stbi = false;
    _height = h;
    _length = l;
    _channels = channels;
    copy_color_data(color_data);
}

unsigned char* Image::copy_color_data(unsigned char* to_copy){
    size_t color_size =  _height * _length * _channels;
    _colors = new unsigned char[color_size];
    for(size_t i = 0; i < color_size; i++){
        _colors[i] = to_copy[i];
    }
}

unsigned char* Image::get_data(){
    return _colors;
}

int Image::get_channels(){
    return _channels;
}

int Image::get_height(){
    return _height;
}

int Image::get_length(){
    return _length;
}

void Image::save_image(){
    stbi_write_png(_file_path.string().c_str(), _length, _height, _channels, _colors, 100);
}

Image::~Image(){
    // Free and MALLOC cannot mix, and thus they must be kept seprate.
    if(_from_stbi){
        stbi_image_free(_colors);
    } else {
        delete [] _colors;
    }
}