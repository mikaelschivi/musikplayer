#pragma once

#include <iostream>
#include <ostream>
#include <filesystem>
#include <vector>

#define PATH_TO_MUSIC_FILE "./music_sample"

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
    static std::vector<Media> mediaList;
    static int mediaListSize;

    static bool CheckByNameIfInMediaList(std::string &name);
    static void AddIntoMediaList(Media media);

public:
    static const char* path;

    static void FetchNewMediaFiles();
    static void PrintMediaListItemsInfo();
};