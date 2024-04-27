#include "./headers/libvlc.h"

using namespace std;

libvlc_instance_t* pEngine = libvlc_new (0, NULL);
libvlc_media_t* m;
libvlc_media_player_t* mp;
libvlc_event_manager_t* e;

bool is_trackLoaded = false;

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
    // return 0;
    return  libvlc_media_player_get_length (mp);
}

int Audio::get_duration()
{
    return libvlc_media_get_duration (m);
}

void Audio::cleanup()
{
    libvlc_release(pEngine);
    libvlc_media_release(m);
    libvlc_media_player_release (mp);
}