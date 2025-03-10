#include "img_data_IO.h"
#include <iostream>

namespace fs = std::filesystem;

main(){
    fs::path working_dir = fs::current_path();
    fs::path test_img = working_dir / "test.png";
    Image img = Image(test_img);
    int test_l = img.get_width();
    int test_h = img.get_height();
    int test_c = img.get_channels();
    std::cout << test_l << " | " << test_h << " | " << test_c << endl;
    for (int x = 0; x < test_l; x++){
        for (int y = 0; y < test_h; y++){
            for (int c = 0; c < test_c; c++){
                if(x == y){
                    img.set(1.0, x, y, c);
                }
            }
        }
    }
    img.save_image();
}