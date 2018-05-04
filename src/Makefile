EXE = testOpencvDnn
# testMxnet 

FLAGS = -I/usr/local/include
LDFLAGS = -L/usr/local/lib -lopencv_core -lopencv_imgcodecs -lopencv_dnn

.PHONY: all clean

all: $(EXE)

$(EXE): % : %.cpp Timer.cpp Timer.h
	$(CXX) -std=c++0x $(FLAGS) -o $@ $(filter %.cpp %.a, $^) $(LDFLAGS)

clean: rm -f $(EXE)
