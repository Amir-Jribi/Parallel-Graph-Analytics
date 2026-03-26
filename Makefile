# 

ifeq ($(OS),Windows_NT)
    include win_gnu.def
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        include linux_gnu.def
    else
        $(error Unsupported OS: $(UNAME_S))
    endif
endif

EXES=main$(EXE) 

all: $(EXES)

main$(EXE): main.$(OBJ) bfs_serial.$(OBJ) bfs_parallel_schedule.$(OBJ) graph.$(OBJ)
     $(CLINKER) $(OPTFLAGS) -o $@ main.$(OBJ) bfs_serial.$(OBJ) bfs_parallel_schedule.$(OBJ) graph.$(OBJ) $(LIBS)


clean:
     $(RM) $(EXES) *.$(OBJ)

# pattern rule
%.o: %.cpp
     $(CC) $(CFLAGS) $(INCLUDES) -c $<


# g++ main.cpp bfs_serial.cpp bfs_parallel_schedule.cpp graph.cpp -g -std=c++17 -fopenmp -I. -o a.exe
