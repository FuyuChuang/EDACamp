EXE := checker
CXX := g++
CXXFLAGS := -std=c++11 -Wall -O3
SRCDIR := src
HPPS := $(wildcard $(SRCDIR)/*.hpp)
CPPS := $(wildcard $(SRCDIR)/*.cpp)
OBJS := $(addprefix obj/, $(notdir $(CPPS:.cpp=.o)))

.PHONY: all release clean

release: CXXFLAGS += -DNDEBUG -static

all release: obj $(EXE)

obj:
	mkdir $@

$(EXE): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

obj/%.o: $(SRCDIR)/%.cpp $(HPPS)
	$(CXX) $(CXXFLAGS) -o $@ -c $<

clean:
	rm $(EXE) $(OBJS)
