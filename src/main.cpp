#include "iomanip"
#include "./headers/gui.h"
#include "./headers/filehandle.h"
#include <vlc/vlc.h>
#include <chrono>
#include <thread>

using namespace std;

int main()
{   
    std::string inputName = "ex/Paranoid";

    libvlc_instance_t* pEngine;
    std::cout << "\n\nlibVLC version: " << libvlc_get_version() << std::endl;
    std::cout << "instance type: " << typeid(pEngine).name() << std::endl;
    
    pEngine = libvlc_new (0, NULL);
    libvlc_media_t* m;
    libvlc_media_player_t* mp;
    
    // std::cout << "\npath for file: ";
    // std::getline(std::cin, inputName);
    
    std::cout << "\npEngine: " << pEngine << std::endl;

    m = libvlc_media_new_path(pEngine, inputName.c_str());
    std::cout << "media loaded: " << m << std::endl;
    
    mp = libvlc_media_player_new_from_media (m);
    std::cout << "mediaplayer: " << mp << std::endl;
    
    int playStatus = true;    
    std::cout << "playback: " << playStatus << std::endl;
    
    std::cout << "\nplaying..." << std::endl;
    while ( !playStatus )
    {
        int curr = libvlc_media_player_get_time(mp);
        int full = libvlc_media_player_get_length(mp);
        if ( (curr >= full*0.98f) && full != 0)
        { 
            break;
        }
    }
    std::cout << "done fuck you\n" << std::endl;
    
    libvlc_release(pEngine);
    std::cout << "free: " << pEngine << " -> " << &pEngine << std::endl;
    libvlc_media_release(m);
    std::cout << "free: " << m << " -> " << &m << std::endl;
    libvlc_media_player_release (mp);
    std::cout << "free: " << mp << " -> " << &mp << std::endl;

    Imgui Imgui;
    Imgui.fuck_you = 35;
    Imgui.runImgui();

    std::cout << "ok" << std::endl;
    return 0;
}