MIDIFILE = ../midifile

CXX = g++
CXXFLAGS = -g -Wall -I$(MIDIFILE)/include

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $*.o

midiconvert : midiconvert.o ../midifile/lib/libmidifile.a
	$(CXX) -o $@ midiconvert.o -L$(MIDIFILE)/lib -lmidifile -lm

../midifile/lib/libmidifile.a :
	cd ../midifile && make library

clean :
	rm -f midiconvert *.o
