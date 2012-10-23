# add custom variables to this file

# OF_ROOT allows to move projects outside apps/* just set this variable to the
# absoulte path to the OF root folder

#OF_ROOT = /home/walter/openframeworks0071
OF_ROOT = ../../..
#OF_ROOT = ../openframeworks0071

# USER_CFLAGS allows to pass custom flags to the compiler
# for example search paths like:
# USER_CFLAGS = -I src/objects

USER_CFLAGS = -g -I ./include -I /usr/include/eigen3 -I /usr/local/cuda/include \
-I ~/NVIDIA_GPU_Computing_SDK/C/common/inc \
-I ~/NVIDIA-OptiX-SDK-3.0.0-linux64/include \


USER_CFLAGS_CUDA = -I ./include -I /home/walter/NVIDIA_GPU_Computing_SDK/C/common/inc \
-arch=sm_21

# USER_LDFLAGS allows to pass custom flags to the linker
# for example libraries like:
# USER_LD_FLAGS = libs/libawesomelib.a

USER_LDFLAGS =

# use this to add system libraries for example:
# USER_LIBS = -lpango

USER_LIBS = -lX11 -rdynamic -loptix -loptixu -Wl,-soname,libsutil.so -lcuda -L /usr/local/cuda/lib -L /usr/local/cuda/lib64 -lcudart -L ~/NVIDIA-OptiX-SDK-3.0.0-linux64/lib64 \



# change this to add different compiler optimizations to your project

USER_COMPILER_OPTIMIZATION = -march=native -mtune=native -O3 -msse4.1 -fPIC  -msse -msse2 -msse3 -mfpmath=sse

EXCLUDE_FROM_SOURCE="bin,.xcodeproj,obj,all_addons"
