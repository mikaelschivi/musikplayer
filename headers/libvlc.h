#pragma once

#include <vlc/vlc.h>

class Audio
{
private:

public:
    static bool is_trackLoaded;
    int play(const char* filename);
    int stop();
    int pause();
    int get_time();
    int get_duration();
    int get_name();
    int update_time(int newTime);
    void cleanup();
};