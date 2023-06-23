CXX = g++
CXXFLAGS1 = -Os -Wall 
CXXFLAGS2 = -mthreads -DHAVE_W32API_H -D__WXMSW__ -DNDEBUG -D_UNICODE
OPT = -pedantic
ADD1 = -I fmt-master/include fmt-master/src/format.cc
ADD2 = -IC:/MesLogiciels/wxWidgets/lib/gcc_dll/mswu -IC:/MesLogiciels/wxWidgets/include -IC:\MesLogiciels\msys64\mingw64\include\c++\12.2.0 -IC:\MesLogiciels\msys64\mingw64\include\c++\12.2.0\x86_64-w64-mingw32 -IC:\MesLogiciels\msys64\mingw64\include\c++\12.2.0\backward -IC:\MesLogiciels\msys64\mingw64\lib\gcc\x86_64-w64-mingw32\12.2.0\include -IC:\MesLogiciels\msys64\mingw64\include -IC:\MesLogiciels\msys64\mingw64\lib\gcc\x86_64-w64-mingw32\12.2.0\include-fixed
ADD3 = -DWXUSINGDLL -std=c++20 -mthreads
ADD4 = -LC:/MesLogiciels/wxWidgets/lib/gcc_dll -mthreads -LC:/MesLogiciels/wxWidgets/lib/gcc_dll
ADD5 =  -lwxmsw32u_richtext -lwxmsw32u_xrc -lwxmsw32u_aui -lwxmsw32u_html -lwxmsw32u_adv -lwxmsw32u_core -lwxbase32u_xml -lwxbase32u_net -lwxbase32u -lwxscintilla -lwxtiff -lwxjpeg -lwxpng -lwxzlib -lwxregexu -lwxexpat -lkernel32 -luser32 -lgdi32 -lcomdlg32 -lwxregexu -lwinspool -lwinmm -lshell32 -lcomctl32 -lversion -lshlwapi -lole32 -loleaut32 -luuid -lrpcrt4 -ladvapi32 -lwsock32 -luxtheme -loleacc
programme = TP3
objets = View.cpp data_controller.cpp data.cpp
ifeq ($(OS), Windows_NT)
programme = TP3.exe
endif

$(programme): $(objets)
	echo "programme: $(programme) ==> objets: $(objets)"
	$(CXX) -o $@ $^ $(CXXFLAGS2) $(ADD1) $(ADD2) $(ADD3) $(ADD4) $(ADD5) 

clean:
	rm $(programme)
