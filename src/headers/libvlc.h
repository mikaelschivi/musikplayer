#pragma once

#include <vlc/vlc.h>

class Audio
{
private:

public:
    int play(const char* filename);
    int stop();
    int pause();
    int get_time();
    int get_duration();
    void cleanup();
};