IMGUI_DIR = ./imgui
HEADERS_DIR = ./headers
SOURCES = main.cpp gui.cpp libvlc.cpp file.cpp
SOURCES += $(HEADERS_DIR)/file.h $(HEADERS_DIR)/gui.h $(HEADERS_DIR)/libvlc.h
SOURCES += $(IMGUI_DIR)/imgui.cpp $(IMGUI_DIR)/imgui_demo.cpp $(IMGUI_DIR)/imgui_draw.cpp $(IMGUI_DIR)/imgui_tables.cpp $(IMGUI_DIR)/imgui_widgets.cpp
SOURCES += $(IMGUI_DIR)/backends/imgui_impl_sdl2.cpp $(IMGUI_DIR)/backends/imgui_impl_opengl2.cpp

EXE = cool
OBJS = $(addsuffix .o, $(basename $(notdir $(SOURCES))))

CXXFLAGS = -std=c++17 -I$(IMGUI_DIR) -I$(IMGUI_DIR)/backends
CXXFLAGS += -g -Wall -Wformat -lvlc
LIBS = 
ECHO_UNAME =
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Linux) #LINUX
	ECHO_UNAME = Linux
	LIBS += -lGL -ldl `sdl2-config --libs`

	CXXFLAGS += `sdl2-config --cflags`
endif

BUILT_MESSAGE =
ifeq ($(DEBUG), 1)
	BUILT_MESSAGE = "[DEBUG]"
	CXXFLAGS += -g -O0
else
	BUILT_MESSAGE = "[RELEASE]"
	CXXFLAGS += -O2
endif

final: $(EXE)
	@echo "$(BUILT_MESSAGE) build complete for $(ECHO_UNAME)."

%.o:%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o:$(IMGUI_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o:$(IMGUI_DIR)/backends/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(EXE): $(OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

clean:
	@echo "cleaning binaries..."
	rm -f $(EXE) $(OBJS)