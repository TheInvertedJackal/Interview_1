#include "img_data_IO.h"

namespace fs = std::filesystem;

const int MAX_APLHA_VALUE = 255;

//Bounds values from 0 (inclusive) to max (exlcusive)
int bounded_value(int value, int max);

//Convolution operation
Image* conv_op(Image* image, Image* kernal, fs::path output_loc);

//Convolution operation with Fast Forier Transform
Image* conv_op_fft(Image* image, Image* kernal, fs::path output_loc);


int main(int argc, char** argv){
    // Set up Directoires
    fs::path working_dir = fs::current_path();
    fs::path imgs_dir = working_dir / "images";

    //Loading Tests
    fs::path tests_text = working_dir / "tests.txt";
    if(!fs::exists(tests_text)){
        cerr << "There should be a file \'tests.txt\' in the working directory, please add it." << endl;
        return 0;
    }

    cout << "Imgs dir is: " << imgs_dir.string() << endl;
    return 0;
}

int bounded_value(int value, int max){
    if(value < 0) return 0;
    if(value >= max) return max - 1;
    return value; 
}


Image* conv_op(Image* image, Image* kernal, fs::path output_loc){
    if(image.get_channels() != kernal.get_channels()) 
        throw "Image (" + image.get_file_path() + ") / Kernal (" + kernal.get_file_path() + ") do not have the same number of channels!";
    if(image.get_height() < kernal.get_height() || image.get_width() < kernal.get_width())
        throw "Image (" + image.get_file_path() + ") is smaller than Kernal (" + kernal.get_file_path() + ")";

    //Calculate output
    int output_h = image.get_height() - kernal.get_height() + 1;
    int output_l = image.get_width() - kernal.get_width() + 1;
    int output_c = image.get_channels();
    Image* output = new Image(output_loc, output_l, output_h, image->get_channels());
    float normaize_value = kernal.get_width() * kernal.get_height() * 255;

    int channels = output_c;    
    // Too many for loops x_x
    for (int y = 0; y < output_l; y++){
        for (int x = 0; x < output_h; x++){
            for (int c = 0; c < output_c; c++){
                //The Alpha channel should be at 100 percent by default
                if(c == 4){
                    output[y * output_l + x + c] = MAX_APLHA_VALUE;
                    continue;
                }

                float total = 0;
                for (int k_l = 0; k_l < kernal.get_width(); k_l++){
                    for(int k_h = 0; k_h < kernal.get_height(); k_h++){
                        int image_x = x + k_h;
                        int image_y = y + k_l;
                        //int i_v = image_cd[image_y * image.get_height() + image_x + c];
                        //int k_v = kernal_cd[k_h * kernal.get_height() + k_h + c];
                        //total += (i_v * k_v) / normaize_value;
                    }
                }
                //output[y * output_l + x + c] = static_cast<unsigned char>(round(total));
            }
        }
    }
}