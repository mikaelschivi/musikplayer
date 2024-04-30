#pragma once

#include <vlc/vlc.h>
#include <iostream>
#include <ostream>

// class Media
// {
// public:
//     const char* GetMediaName();
// };

class Audio
{
public:
    static bool is_trackLoaded;

    static int SecFromMilli(libvlc_time_t milliseconds);
    static int MinFromMilli(libvlc_time_t milliseconds);

    static int Play(const char* filename);
    static void Pause();

    static int GetMediaLoadState();
    static int GetMediaTimeMs();
    static int GetMediaDurationMs();
    static const char* GetMediaName();
    static char* GetAudioDeviceInfo();
    static int GetVolume();
    
    static int SetMediaTimeMs(int newTime);
    static int SetVolume(int value);

    static void Cleanup();
private:
    static const char* title;

};