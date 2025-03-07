#include "img_data_IO.h"

namespace fs = std::filesystem;

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