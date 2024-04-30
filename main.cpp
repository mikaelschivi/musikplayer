#include "./headers/gui.h"
#include "./headers/file.h"

using namespace std;

int main()
{   
    // Imgui::run();
    File::FetchNewMediaFiles();
    File::PrintMediaListItemsInfo();
    printf("done\n");
    return 0;
}