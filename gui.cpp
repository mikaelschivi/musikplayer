#include "./headers/gui.h"
#include <cmath>

using namespace std;

Audio audio;

int Imgui::run()
{   
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
    {
        printf("Error: %s\n", SDL_GetError());
        return -1;
    }
    if (window == nullptr) 
    {
        printf("Error: SDL_CreateWindow(): %s\n", SDL_GetError());
        return -1;
    }
    printf("SDL Setup: ok\n");

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_WindowFlags window_flags = (SDL_WindowFlags)
                                   (SDL_WINDOW_OPENGL | 
                                   SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Window* window = SDL_CreateWindow("musikplayer", 
                            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                            WINDOW_W, WINDOW_H, window_flags);
    if (window == nullptr)
    {
        printf("Error: SDL_CreateWindow(): %s\n", SDL_GetError());
        return -1;
    }
    SDL_GLContext gl_context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, gl_context);
    SDL_GL_SetSwapInterval(1); // Enable vsync
    printf("SDL_GL Setup: ok\n");

    // IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    ImGui::StyleColorsDark();
    
    ImFont* font = io.Fonts->AddFontFromFileTTF("font/Roboto-Regular.ttf", 16.0f, nullptr);
    IM_ASSERT(font != nullptr);
    printf("ImGui: ok\n");

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
    ImGui_ImplOpenGL2_Init();
    printf("ImGui_Impl: ok\n");

    bool statsWindow = false;
    
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

        ImGui_ImplOpenGL2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();
        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
        int time = 0;
        int old_time = time;
        int length = 0;
        const char* song = "music_sample/techno.mp3";
        {   
            ImGui::Begin("1");
            
            // if (ImGui::Button("test")) ImVec4 clear_color = ImVec4( 0.f, 0.f, 0.f, 1.00f);

            if (ImGui::Button("play"))
                audio.play(song);
            if (ImGui::Button("stop"))
                audio.stop();
            
            if (Audio::is_trackLoaded)
            {
                time = audio.get_time();
                old_time = time;
                length = audio.get_duration();
            }

            ImGui::SliderInt("track", &time, 0, length);
            if (length > 0)
            {
                ImGui::Checkbox("Item metadata", &statsWindow);
            }
            
            if (old_time != time) audio.update_time(time);
        
            ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
            ImGui::End();
        }
        
        if (statsWindow)
        {
            ImGui::Begin("Stats", &statsWindow);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("name: %c", audio.get_name());
            ImGui::Text("duration: %im%i", audio.minFromMilli(length),audio.secFromMilli(length));

            if (ImGui::Button("Close"))
                statsWindow = false;
            ImGui::End();
        }

        // glWindow background color
        ImVec4 clear_color = ImVec4 (0.12f, 0.12f, 0.12f, 1.00f);
        // Rendering
        ImGui::Render();
        glViewport(0, 0, WINDOW_W, WINDOW_H);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(window);
    }
    Cleanup(window, GL_TERMINATE_SEQUENCE_COMMAND_NV);

    return 0;
}

void Imgui::Cleanup(SDL_Window* w, SDL_GLContext gl)
{
    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_GL_DeleteContext(gl);
    SDL_DestroyWindow(w);
    SDL_Quit();
}