#include "./headers/libvlc.h"

using namespace std;

libvlc_instance_t* pEngine = libvlc_new (0, NULL);
libvlc_media_t* m;
libvlc_media_player_t* mp;
libvlc_event_manager_t* e;

bool Audio::is_trackLoaded = false;
std::string Audio::title = "";

int Audio::SecFromMilli(libvlc_time_t milliseconds)
{
    return (milliseconds / 1000) % 60;
}

int Audio::MinFromMilli(libvlc_time_t milliseconds)
{
    return (milliseconds / (1000 * 60)) % 60;
}

int Audio::Play(const char* filename)
{
    if (is_trackLoaded && libvlc_media_player_is_playing (mp)) {
        if (filename != title) {
            CleanMediaFromMediaPlayer();

            m = libvlc_media_new_path(pEngine, filename);
            mp = libvlc_media_player_new_from_media (m);
            title = filename;
            return libvlc_media_player_play(mp);
        }
        printf("media already loaded.\n");
        return -1;
    }
    
    m = libvlc_media_new_path(pEngine, filename);
    mp = libvlc_media_player_new_from_media (m);
    is_trackLoaded = true;
    title = filename;

    return libvlc_media_player_play(mp);
}

void Audio::Stop()
{
    if (!is_trackLoaded)
        return;
    CleanMediaFromMediaPlayer();
    is_trackLoaded = false;
}

void Audio::CleanMediaFromMediaPlayer()
{
    libvlc_media_release(m);
    libvlc_media_player_release (mp);
}

int Audio::GetMediaLoadState()
{
    if(!is_trackLoaded) 
        return -1;
    return libvlc_media_player_get_state(mp);
}

const char* Audio::GetMediaLoadStateChar()
{
    int state = Audio::GetMediaLoadState();
    const char* St[] = {"libvlc_NothingSpecial", "libvlc_Opening", "libvlc_Buffering", "libvlc_Playing", "libvlc_Paused",
                    "libvlc_Stopped", "libvlc_Ended", "libvlc_Error"};
    if (state > -1)
        return St[state];
    return "No track loaded";
}

void Audio::Pause()
{
    libvlc_media_player_pause (mp);
}

int Audio::GetMediaTimeMs()
{
    if (is_trackLoaded)
        return libvlc_media_player_get_time (mp);
    return 0;
}

int Audio::GetMediaDurationMs()
{
    if (is_trackLoaded)
        return libvlc_media_player_get_length (mp);
    if (libvlc_media_player_get_length (mp) > -1)
        is_trackLoaded = true;
    return 0;
}

int Audio::SetMediaTimeMs(int newTime)
{
    if(GetMediaDurationMs() == -1)
        return 0;

    int oldtime = libvlc_media_player_get_time (mp);

    if (newTime != oldtime && oldtime != -1) {
        libvlc_media_player_set_time (mp, newTime);
    }
    return oldtime;
}

std::string Audio::GetMediaName()
{
    return title;
}

int Audio::GetVolume()
{
    return libvlc_audio_get_volume(mp);
}

int Audio::SetVolume(int value)
{
    return libvlc_audio_set_volume(mp, value);
}

char* Audio::GetAudioDeviceInfo()
{
    return libvlc_audio_output_device_get(mp);
}

void Audio::Cleanup()
{
    libvlc_release(pEngine);
 
    if(!is_trackLoaded)
        return;
 
    libvlc_media_release(m);
    libvlc_media_player_release (mp);
}