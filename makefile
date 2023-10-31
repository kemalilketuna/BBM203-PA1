# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -std=c++11

# List of source files
SRCS = Convolution.cpp \
       DecodeMessage.cpp \
       EdgeDetector.cpp \
       EncodeMessage.cpp \
       ImageLoader.cpp \
       ImageMatrix.cpp \
       ImageProcessor.cpp \
       ImageSharpening.cpp \
       main.cpp

# List of object files
OBJS = $(SRCS:.cpp=.o)

# Output executable name
TARGET = my_program

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
