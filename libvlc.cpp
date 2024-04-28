#include "./headers/libvlc.h"

using namespace std;

libvlc_instance_t* pEngine = libvlc_new (0, NULL);
libvlc_media_t* m;
libvlc_media_player_t* mp;
libvlc_event_manager_t* e;

bool Audio::is_trackLoaded = false;

int Audio::secFromMilli(libvlc_time_t milliseconds)
{
    return (milliseconds / 1000) % 60;
}

int Audio::minFromMilli(libvlc_time_t milliseconds)
{
    return (milliseconds / (1000 * 60)) % 60;
}

int Audio::play(const char* filename)
{
    if (is_trackLoaded && libvlc_media_player_is_playing (mp)) {
        printf("media already loaded.\n");
        return -1;
    }
    m = libvlc_media_new_path(pEngine, filename);
    mp = libvlc_media_player_new_from_media (m);
    is_trackLoaded = true;
    printf("load media: ");
    printf("%s", (const char*)filename);
    printf("\nplaying\n");

    return libvlc_media_player_play(mp);
}

int Audio::stop()
{
    is_trackLoaded = false;
    if (!libvlc_media_player_is_playing(mp))
    {
        printf("no media playing in mediaplayer\n");
        return 0;
    }
    libvlc_media_player_stop (mp);
    libvlc_media_player_release (mp);
    return 0;
}

int Audio::pause()
{
    if(!libvlc_media_player_can_pause (mp)) {
        return 1;
    }
    libvlc_media_player_pause (mp);
    return 0;
}

int Audio::get_time()
{
    if (is_trackLoaded)
        return libvlc_media_player_get_time (mp);
    return 0;
}

int Audio::get_duration()
{
    if (is_trackLoaded)
        return libvlc_media_player_get_length (mp);
    if (libvlc_media_player_get_length (mp) > -1)
        is_trackLoaded = true;
    return 0;
}

int Audio::update_time(int newTime)
{   if(get_duration() == -1)
        return 0;

    int oldtime = libvlc_media_player_get_time (mp);

    if (newTime != oldtime && oldtime != -1)
    {
        libvlc_media_player_set_time (mp, newTime);
    }
    return oldtime;
}

int Audio::get_name()
{
    return 'a';
}

int Audio::get_volume()
{
    return libvlc_audio_get_volume(mp);
}

int Audio::set_volume(int value)
{
    return libvlc_audio_set_volume(mp, value);
}


void Audio::cleanup()
{
    libvlc_release(pEngine);
    libvlc_media_release(m);
    libvlc_media_player_release (mp);
}