#include "./headers/file.h"

using namespace std;

const char* File::path = PATH_TO_MUSIC_FILE;
int File::mediaListSize = 0;
std::vector<Media> File::mediaList;

bool File:: CheckByNameIfInMediaList(std::string &name)
{   
    if (mediaListSize == 0) return false;

    for (auto& item : mediaList) {
        if (!item.filename.empty() && name == item.filename){
            return true;
        }
    }
    return false;
}

void File::AddIntoMediaList(Media media)
{
    mediaList.push_back(media);
    mediaListSize++;
}

void File::FetchNewMediaFiles()
{
    if (mediaList.empty())
        mediaListSize = 0;

    for (const auto &entry : fs::directory_iterator(path)) {   
        std::string name = entry.path().filename().string();
        
        if (!CheckByNameIfInMediaList(name)) {
            std::string fPath = entry.path().string();
            std::string typeByExtension = entry.path().extension().string();
            uint32_t size = entry.file_size();

            Media newMedia;
            newMedia.filename = name;
            newMedia.filepath = fPath;
            newMedia.fileType = typeByExtension;
            newMedia.fileSize = size;
            AddIntoMediaList(newMedia);
        }
    }
}

int File::GetMediaListSize()
{
    return mediaListSize;
}

void File::PrintMediaListItemsInfo()
{
    if (!mediaList.empty()) {
        for (const auto& media : mediaList) {
            std::cout << media.filename << endl;
            std::cout << media.filepath << endl;
            std::cout << media.fileType << endl;
            std::cout << media.fileSize << endl;
            std::cout << endl;
        }
    }
}