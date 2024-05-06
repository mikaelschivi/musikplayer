#include "./headers/gui.h"
#include "./headers/file.h"
#include <cmath>

using namespace std;

const char* Gui::selectedFile = 0;

ImVec4 GenerateRandomColor()
{
    // ImVec4 color = {0.25f, 0.1f, 0.25f, 0.4f};
    ImVec4 color = {(float) (rand()%100) / 100.0f, 
                    (float) (rand()%100) / 100.0f,
                    (float) (rand()%100) / 100.0f,
                    1.0f};
    return color;
}

int Gui::run()
{   
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER ) != 0) {
        fprintf( stderr, "Video initialization failed: %s\n",
             SDL_GetError( ) );
        return -1;
    }

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_WindowFlags window_flags = (SDL_WindowFlags)
                    (SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI
                    | SDL_WINDOW_MAXIMIZED);
    
    SDL_Window* window = SDL_CreateWindow("musikplayer", 
                            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                            WINDOW_W, WINDOW_H, window_flags);
    if (window == nullptr) {
        printf("Error: SDL_CreateWindow(): %s\n", SDL_GetError());
        return -1;
    }
    printf("SDL Setup: ok\n");
    
    SDL_GLContext gl_context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, gl_context);
    SDL_GL_SetSwapInterval(1);
    
    printf("SDL_GL Setup: ok\n");
    printf("\nOpenGL Version: "); std::cout << glGetString(GL_VERSION) << std::endl;
    printf("OpenGL Vendor: "); std::cout << glGetString(GL_VENDOR) << std::endl;
    printf("OpenGL Renderer: "); std::cout << glGetString(GL_RENDERER) << std::endl;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
    ImFont* font = io.Fonts->AddFontFromFileTTF("font/Roboto-Regular.ttf", 16.0f, nullptr);
    IM_ASSERT(font != nullptr);
    
    ImGui::StyleColorsDark();
    
    ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
    printf("\nImGui_ImplSDL: ok\n");
    ImGui_ImplOpenGL3_Init();
    printf("ImGui_ImplOpenGL3: ok\n");
    
    printf("ImGui: ok\n");

    ImGuiWindowFlags w = ImGuiWindowFlags_NoTitleBar;
    w = w | ImGuiWindowFlags_NoCollapse;
    w = w | ImGuiWindowFlags_NoDocking;

    bool statsWindow = false;
    bool soundVisualizer = true;
    ImVec4 clear_color = GenerateRandomColor();

    // main loop
    bool done = false;
    while (!done)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {   
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT)
                done = true;
            if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window))
                done = true;
        }

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();
        {
            ImGui::Begin("file", NULL, w | ImGuiWindowFlags_NoResize);
                File::FetchNewMediaFiles();
                
                ImGui::PushID("set1");
                ImGui::PushStyleColor(ImGuiCol_FrameBg, (ImVec4)ImColor::HSV(0.0f, 0.0f, 63.0f, (0.83/255.0)*10 ));

                static int listSize = File::GetMediaListSize();
                ImGui::Text("Files in ./music_sample");

                ImGui::SetNextWindowSizeConstraints(ImVec2(0.0f, ImGui::GetTextLineHeightWithSpacing() * 10),
                                                    ImVec2(FLT_MAX, ImGui::GetTextLineHeightWithSpacing() * 10));

                ImGui::BeginChild("##Files", ImVec2(0, 0), ImGuiChildFlags_Border);
                {
                    ImGui::BeginListBox("##Fetched files listing", ImVec2(-FLT_MIN, 5.25 * ImGui::GetTextLineHeightWithSpacing()));
                    
                    for (int i = 0; i < listSize; i++) {
                        const char* filename = File::mediaList[i].filename.c_str();
                        static int selected = -1;
                        
                        if (ImGui::Selectable(filename, selected == i)) {
                            selected = i;
                            assert(listSize > 0);
                        
                            if (Gui::selectedFile != filename) {
                                Gui::selectedFile = filename;
                                ImGui::SetItemDefaultFocus();
                            } 
                        }
                    }
                    ImGui::EndListBox();
                }
                ImGui::EndChild();

                if (statsWindow) {
                    int duration = 0;
                    
                    if (Audio::is_trackLoaded) {
                        duration = Audio::GetMediaDurationMs();
                    
                        ImGui::BeginChild("##item metadata", ImVec2(0,0), ImGuiChildFlags_Border);
                            ImGui::Text("name: %s", Audio::GetMediaName().c_str());
                            ImGui::Text("duration: %im%is", Audio::MinFromMilli(duration),Audio::SecFromMilli(duration));
                            ImGui::Text("state: %s", Audio::GetMediaLoadStateChar());
                            ImGui::Text("output device: %s", Audio::GetAudioDeviceInfo());
                            ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
                        ImGui::EndChild();
                    }
                }
                ImGui::PopStyleColor();
                ImGui::PopID();
            ImGui::End();
        }

        int time = 0;
        int old_time = time;
        int length = 0;
        std::string filePath = "./music_sample/";
        {   
            ImGui::Begin("media", NULL, w);
            ImGui::Text("song: %s", Gui::selectedFile);
            if (ImGui::Button("play")) {   
                if(selectedFile)
                    Audio::Play( (filePath + (std::string) Gui::selectedFile).c_str() );
            }

            ImGui::SameLine();
            if (ImGui::Button("pause"))
                Audio::Pause();

            ImGui::SameLine();
            if (ImGui::Button("stop")) {
                Audio::Stop();
                Gui::selectedFile = 0;
            }

            if (Audio::is_trackLoaded) {
                time = Audio::GetMediaTimeMs();
                old_time = time;
                length = Audio::GetMediaDurationMs();
            }
            
            ImGui::SliderInt("track", &time, 0, length);
            
            if (length > 0) {   
                int volume = Audio::GetVolume();
                int old_volume = volume;
                ImGui::SliderInt("volume", &volume, 0, 100);
                ImGui::SameLine();
                if (ImGui::Button("Mute")) {
                    volume = 0;
                }
                ImGui::Checkbox("Item metadata", &statsWindow);
                if (old_volume != volume) 
                    Audio::SetVolume(volume);
            }
            
            if (old_time != time) 
                Audio::SetMediaTimeMs(time);

            ImGui::End();
        }

        if (soundVisualizer) {
            ImGuiWindowFlags svWindow = w | ImGuiWindowFlags_NoDecoration;
            ImGui::Begin("## sound shit", NULL, svWindow);
            {
                ImGui::BeginChild("##GameRender");
                    // // Projection Matrix
                    // glMatrixMode( GL_PROJECTION );
                    // glLoadIdentity();    
                    // // Modelview Matrix
                    // glMatrixMode( GL_MODELVIEW );
                    // glLoadIdentity();
     
                    // glClearColor( 0.f, 0.f, 0.f, 1.f );
                    // glClear( GL_COLOR_BUFFER_BIT );
                    // glBegin( GL_QUADS );
                    //     glVertex2f( -0.5f, -0.5f );
                    //     glVertex2f( 0.5f, -0.5f );
                    //     glVertex2f( 0.5f, 0.5f );
                    //     glVertex2f( -0.5f, 0.5f );
                    // glEnd();
                    // SDL_GL_SwapWindow( window );
                ImGui::EndChild();
                ImGui::End();
            }
        }

        // glWindow background color
        // ImVec4 clear_color = ImVec4 (0.12f, 0.12f, 0.12f, 1.00f);

        // Rendering
        ImGui::Render();

        glViewport(0, 0, WINDOW_W, WINDOW_H);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(window);
    }
    Cleanup(window, gl_context);

    return 0;
}

void Gui::Cleanup(SDL_Window* w, SDL_GLContext gl)
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    printf("\n\nDestroy ImGuiContext\n");

    SDL_GL_DeleteContext(gl);
    printf("Destroy GlContext\n");
    SDL_DestroyWindow(w);
    SDL_Quit();
    printf("Destroy SDL window\n\n");
}