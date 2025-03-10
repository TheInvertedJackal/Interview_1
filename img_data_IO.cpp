#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION

#include "stb_image_write.h"
#include "stb_image.h"
#include "img_data_IO.h"
#include <iostream>

Image::Image(fs::path path){
    if(!fs::exists(path))
        throw "Image file not found!";
    _file_path = path;
    stbi_uc* raw_load = stbi_load(path.string().c_str(), &_width, &_height, &_channels, 0);
    if(raw_load == nullptr)
        throw "Error reading Image!";
    //_colors = (unsigned char*) raw_load; //stbi_uc is unsinged char on the backend.
    _total_elements = _width * _height * _channels;
    _colors_d = u_eight_to_double((unsigned char*) raw_load, _total_elements);
    stbi_image_free(raw_load);
}

Image::Image(fs::path path, int x, int y, int c){
    _width = x;
    _height = y;
    _channels = c;
    _total_elements = _width * _height * _channels;
    _colors_d = new double[x * y * c];
};


Image::Image(fs::path path, int x, int y, int channels, unsigned char* color_data){
    _height = y;
    _width = x;
    _channels = channels;
    //copy_color_data(color_data);
    _total_elements = _width * _height * _channels;
    _colors_d = u_eight_to_double(color_data, _total_elements);
}

std::string Image::get_file_path(){
    return _file_path.string();
}

// unsigned char* Image::copy_color_data(unsigned char* to_copy){
//     size_t color_size =  _height * _width * _channels;
//     _colors = new unsigned char[color_size];
//     for(size_t i = 0; i < color_size; i++){
//         _colors[i] = to_copy[i];
//     }
// }

double Image::at(int x, int y, int c){
    if(x < 0 || x >= _width)
        throw "Index out of range for Image x / Length";
    if(y < 0 || y >= _height)
        throw "Index out of range for Image y / Height";
    if(c < 0 || c >= _channels)
        throw "Index out of range for Image Channel";
    //return _colors_d[c + x + (y * _height)];
    return _colors_d[_channels * (y * _width + x) + c];

}

void Image::set(double d, int x, int y, int c){
    if(d > 1.0 || d < 0)
        throw "Value must be between 0 and 1!";
    if(x < 0 || x >= _width)
        throw "Index out of range for Image x / Length";
    if(y < 0 || y >= _height)
        throw "Index out of range for Image y / Height";
    if(c < 0 || c >= _channels)
        throw "Index out of range for Image Channel";
    //std::cout << "(" << x << " ," << y << " ," << c << ") - " << (c + x + (y * _height)) << endl;
    //_colors_d[c + x + (y * _height)] = d;
    _colors_d[_channels * (y * _width + x) + c] = d;
}

double* Image::u_eight_to_double(unsigned char* data, int len){
    double* ret_val = new double[len];
    for (int i = 0; i < len; i++){
        ret_val[i] = data[i] / 255.0;
        //std::cout << "U8: " << static_cast<unsigned>(data[i]) << " new Double:" << ret_val[i] << endl;
    }
    return ret_val;
}

unsigned char* Image::double_to_u_eight(double* data, int len){
    unsigned char* ret_val = new unsigned char[len];
    for (int i = 0; i < len; i++){
        double value = round(data[i] * 255);
        ret_val[i] = static_cast<unsigned char>(round(data[i] * 255));
        //std::cout << "Double:" << data[i] << " Rounded:" << value << " new u8:" << static_cast<unsigned>(ret_val[i]) << endl;
    }
    return ret_val;
}

// unsigned char* Image::get_data(){
//     return _colors;
// }

int Image::get_channels(){
    return _channels;
}

int Image::get_height(){
    return _height;
}

int Image::get_length(){
    return _width;
} 

void Image::save_image(){
    unsigned char* _colors = double_to_u_eight(_colors_d, _total_elements);
    stbi_write_png(_file_path.string().c_str(), _width, _height, _channels, _colors, _width * _channels);
    delete [] _colors;
}

Image::~Image(){
    // Free and MALLOC cannot mix, and thus they must be kept seprate
    delete [] _colors_d;
}