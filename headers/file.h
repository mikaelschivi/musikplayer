#pragma once

#include <iostream>
#include <ostream>
#include <filesystem>
#include <vector>

#define PATH_TO_MUSIC_FILE "./music_sample"

namespace fs = std::filesystem;

typedef struct Media
{
    std::string filename;
    std::string filepath;
    std::string fileType;
    uint32_t    fileSize;
} Media;

class File
{
private:
    static int mediaListSize;
    static bool CheckByNameIfInMediaList(std::string &name);
    static void AddIntoMediaList(Media media);

public:
    static std::vector<Media> mediaList;
    static const char* path;

    static int GetMediaListSize();
    static void FetchNewMediaFiles();
    static void PrintMediaListItemsInfo();
};