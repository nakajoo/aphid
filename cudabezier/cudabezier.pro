CONFIG -= app_bundle
CONFIG += release
message(QMAKE with CUDA)
INCLUDEPATH += ./ ../shared
HEADERS       = glWidget.h \
                window.h \
                BezierProgram.h \
                bezier_implement.h \
                ../shared/CudaBase.h \
                ../shared/Base3DView.h \
                ../shared/GLHUD.h \
                ../shared/BaseBuffer.h \
                ../shared/CUDABuffer.h \
                ../shared/CUDAProgram.h
SOURCES       = main.cpp \
                glWidget.cpp \
                window.cpp \
                BezierProgram.cpp \
                ../shared/CudaBase.cpp \
                ../shared/Base3DView.cpp \
                ../shared/GLHUD.cpp \
                ../shared/BaseBuffer.cpp \
                ../shared/CUDABuffer.cpp \
                ../shared/CUDAProgram.cpp

win32 {
    HEADERS += ../shared/gExtension.h
    SOURCES += ../shared/gExtension.cpp
    INCLUDEPATH += D:/usr/boost_1_51_0 /usr/local/include/OpenEXR
    QMAKE_LIBDIR += D:/usr/boost_1_51_0/stage/lib D:/usr/local/openEXR/lib
    CONFIG += console
}
macx {
    INCLUDEPATH += ../../Library/boost_1_55_0
        LIBS += -L../../Library/boost_1_55_0/stage/lib -lboost_date_time -lboost_system -lboost_thread -lboost_filesystem
}
QT           += opengl
LIBS += -L../lib -laphid -lIlmImf -lHalf

CUSOURCES = bezier.cu
macx {
CUDA_CC = /usr/local/cuda/bin/nvcc
CUDA_DIR = /usr/local/cuda
CUDA_DEV = "/Developer/GPU Computing/C"
CUDA_COMMON = $$CUDA_DEV/common
CUDA_INC_PATH = $$CUDA_DIR/include
CUDA_SHARED = "/Developer/GPU Computing/shared"
message("nvcc resides in :" $$CUDA_CC)
INCLUDEPATH += $$CUDA_INC_PATH \
    $$CUDA_COMMON/inc \
    $$CUDA_SHARED/inc
LIBS += -lcuda \
    -lcudart \
    -lcutil_i386 \
    -lshrutil_i386
QMAKE_LIBDIR += $$CUDA_DIR/lib \
    $$CUDA_COMMON/lib/darwin \
    $$CUDA_DEV/lib \
    $$CUDA_SHARED/lib
}
win32 {
CUDA_CC =D:/usr/cuda4/v4.0/bin/nvcc.exe
CUDA_DIR = D:/usr/cuda4/v4.0
CUDA_DEV = "D:/usr/cuda4_sdk/C"
CUDA_COMMON = $$CUDA_DEV/common
CUDA_INC_PATH = $$CUDA_DIR/include
message("nvcc resides in :" $$CUDA_CC)
INCLUDEPATH += $$CUDA_INC_PATH \
                $$CUDA_COMMON/inc

QMAKE_LIBDIR += $$CUDA_DIR/lib/x64 \
                $$CUDA_COMMON/lib/x64
QMAKE_LFLAGS_RELEASE += /NODEFAULTLIB:libcmt  /NODEFAULTLIB:libcpmt
LIBS += -lcuda -lcudart
}

cuda.name = CUDA
cuda.input = CUSOURCES
cuda.dependency_type = TYPE_C
cuda.variable_out = OBJECTS
cuda.output = ${QMAKE_FILE_IN}$$QMAKE_EXT_OBJ
cuda.commands = $$CUDA_CC \
    -c \
    -m64 \
    -arch sm_11 \
    $$join(INCLUDEPATH,'" -I "','-I "','"') \
    ${QMAKE_FILE_IN} \
    -o \
    ${QMAKE_FILE_OUT} # Note the -O0
QMAKE_EXTRA_COMPILERS += cuda
DESTDIR = ./

