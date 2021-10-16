CXX = g++
CXXFLAGS = -g -std=c++2a -w -P
INCLUDE = -Iinclude -I/usr/local/include -I/usr/include
LDFLAGS =
LDLIBS = -lopencv4
CFLAGS = `pkg-config --cflags opencv4`
LIBS = `pkg-config --libs opencv4`
PROJECT = TP2

info: 
	clear && echo "$(PROJECT) Make\n- build\n- run\n- clean\n- clean\n- doc\n- py"

build: 
	clear && echo "🛠  Build of $(PROJECT)" && $(CXX) $(INCLUDE) $(LDFLAGS) $(CXXFLAGS) $(CFLAGS) $(LIBS)  src/main.cpp -o main && mv main bin/main && echo "✅  Done successfuly"

run: 
	clear && echo "🚀  Run of $(PROJECT)" && ./bin/main "$(IMG_PATH)"

clean : 
	clear && cd bin && rm bin/*

docs: 
	clear && cd doc && eval "$(/usr/libexec/path_helper)" && pandoc rapport-tp2.md --pdf-engine=xelatex -o rapport-tp2.pdf && open rapport-tp2.pdf && cd ..

py: 
	clear && python3.9 src/main.py