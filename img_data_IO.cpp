#include "stb_image_write.h"
#include "stb_image.h"
#include "img_data_IO.h"

image getImage(fs::path file){
    image return_val;
    stbi_uc* raw_image = stbi_load(file.string().c_str(), &return_val.length, &return_val.height, &return_val.channels, 0);
    return_val.colors = new img_colors[return_val.length * return_val.height];
    
}

void saveImage(image img, fs::path file){
    stbi_write_png()
}