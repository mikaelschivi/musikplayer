#include "iomanip"
#include "filehandle.cpp"
#include <vlc/vlc.h>
#include <chrono>
#include <thread>

using namespace std;
using namespace File;

#define METADATA 2048

int main()
{
    // std::string path = "data";   
    // int byteAmount = METADATA;
    // char* data = File::readBinaryFile(path, byteAmount);
    // if (data == nullptr){
    //     return 1;
    // }
    // // File::printBinaryFromData(data, byteAmount);
    // File::deleteData(data);
    // libvlc_release(engine);

    std:cout << std::endl;
    libvlc_instance_t* engine = libvlc_new (0, NULL);
    std::cout << "instance type: " << typeid(engine).name() << std::endl;
    std::cout << "libvlc version: " << libvlc_get_version() << std::endl;
    libvlc_media_player_t* mediaplayer;
    libvlc_media_t* m;

    std::this_thread::sleep_for(0.5s);

    std::cout << "ok" << std::endl;
    return 0;
}