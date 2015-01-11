TYPE=release

CC=gcc
CFLAGS=-fPIC -Wall

ifeq ($(TYPE),debug)
	CFLAGS+=-g3 -pg -DDEBUG
else
	ifeq ($(TYPE),release)
		CFLAGS+=-O3
	else
		CFLAGS+=-g -O
	endif
endif

CXX=g++
CXXFLAGS=-fPIC -Wall

ifeq ($(TYPE),debug)
	CXXFLAGS+=-g3 -pg -DDEBUG
else
	ifeq ($(TYPE),release)
		CXXFLAGS+=-O3
	else
		CXXFLAGS+=-g -O
	endif
endif

LD=g++

AR=ar
ARFLAGS=rc

RM=rm
MV=mv

############Parameter Setting###########

#sub directory
SUBDIRS=

#source files directory, default is current directory
#be sure that your source files is under this directory
SRC_DIR=.

LDFLAGS=

#included header files directory, you can specify more than one directory
#names here seperated by whitespace, e.g. INCDIR=. ../inc1 ../inc2
INCDIR=-I../include -I../include/opencv -I../jni/EyeLocation_qh -I../jni/FaceDetection -I../jni/FaceGabor -I../jni/landmark_sdm -I../jni/mpeg7_feature/include -I../jni/FaceTaggingAPI
#vpath %.h ../../include/opencv ../../include ../GrabCut/maxflow/adjacency_list ../GrabCut

#specify the path of the library if needed
LIBS=-Wl,-rpath, -L../lib -lopencv_core -lopencv_imgproc -lopencv_highgui  -lopencv_features2d -lopencv_calib3d -lopencv_objdetect -lopencv_contrib   -lJNI_FaceTagInterface
#LIBS=-Wl,-rpath, ../lib/opencv2: ../lib -L../../lib -L../../lib/opencv2 -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_ml -lopencv_video -lopencv_features2d -lopencv_calib3d -lopencv_objdetect -lopencv_contrib -lopencv_legacy -lopencv_flann

#binary files name and path
MODULE_NAME=./test

#static library target
STATICLIB=

#dynamic library target
SHARELIB=

SRCS:=$(wildcard $(addsuffix /*.c,$(SRC_DIR)))\
      $(wildcard $(addsuffix /*.C,$(SRC_DIR)))\
      $(wildcard $(addsuffix /*.cpp,$(SRC_DIR)))\
      $(wildcard $(addsuffix /*.CPP,$(SRC_DIR)))

OBJS:=$(SRCS:%.c=%.o)
OBJS:=$(OBJS:%.cpp=%.o)
OBJS:=$(OBJS:%.CPP=%.o)
OBJS:=$(OBJS:%.C=%.o)

CLEANS:=$(wildcard $(addsuffix /*~,$(SRC_DIR)))

DEPS:=$(OBJS:%.o=%.d)

############Parameter Setting###########

.PHONY:

TARGET=$(MODULE_NAME) $(STATICLIB) $(SHARELIB)

all:
	@set -e;for dir in ${SUBDIRS};        \
		  do                          \
		    ${MAKE} all -C $${dir};   \
	done
	@set -e;for target in ${TARGET};      \
		  do                          \
		    ${MAKE} $${target};       \
	done

$(MODULE_NAME):$(OBJS)
	$(LD) $(LDFLAGS) $(LIBS) $^ -o $@
	@echo "  ^_^ LD $@"

static-lib:$(STATICLIB)

$(STATICLIB):$(OBJS)
	$(AR) $(ARFLAGS) $@ $^
	@echo "  ^_^ AR $@"

share-lib:$(SHARELIB)

$(SHARELIB):$(OBJS)
	$(LD) -fPIC -shared $(LDFLAGS) $(LIBS) $^ -o $@
	@echo "  ^_^ LD $@"

debug:
	$(MAKE) TYPE=debug

clean:
	@set -e;for dir in ${SUBDIRS};        \
		  do                          \
	            ${MAKE} clean -C $${dir}; \
	done
	@$(RM) -rf $(OBJS)
	@$(RM) -rf $(STATICLIB)
	@$(RM) -rf $(SHARELIB)
	@$(RM) -rf $(DEPS)
	@$(RM) -rf $(CLEANS)
	@echo "  ^_^ RM ALL"

.SUFFIXES: .o .c .C .cpp .CPP

-include $(DEPS)

%.o:%.c
	if $(CC) $(INCDIR) $(CFLAGS) -MT $@ -MD -MP -MF "$(@D)/$(@F:%.o=%.td)" -c -o $@ $<; then \
           $(MV) -f "$(@D)/$(@F:%.o=%.td)" "$(@D)/$(@F:%.o=%.d)"; \
	else \
	   $(RM) -f "$(@D)/$(@F:%.o=%.td)"; exit 1; \
	fi
	@echo "  ^_^ CC $@"
	   
%.o:%.C
	if $(CC) $(INCDIR) $(CFLAGS) -MT $@ -MD -MP -MF "$(@D)/$(@F:%.o=%.td)" -c -o $@ $<; then \
           $(MV) -f "$(@D)/$(@F:%.o=%.td)" "$(@D)/$(@F:%.o=%.d)"; \
	else \
	   $(RM) -f "$(@D)/$(@F:%.o=%.td)"; exit 1; \
	fi
	@echo "  ^_^ CC $@"

%.o:%.cpp
	if $(CXX) $(INCDIR) $(CXXFLAGS) -MT $@ -MD -MP -MF "$(@D)/$(@F:%.o=%.td)" -c -o $@ $<; then \
           $(MV) -f "$(@D)/$(@F:%.o=%.td)" "$(@D)/$(@F:%.o=%.d)"; \
	else \
	   $(RM) -f "$(@D)/$(@F:%.o=%.td)"; exit 1; \
	fi
	@echo "  ^_^ CXX $@"

%.o:%.CPP
	if $(CXX) $(INCDIR) $(CXXFLAGS) -MT $@ -MD -MP -MF "$(@D)/$(@F:%.o=%.td)" -c -o $@ $<; then \
           $(MV) -f "$(@D)/$(@F:%.o=%.td)" "$(@D)/$(@F:%.o=%.d)"; \
	else \
	   $(RM) -f "$(@D)/$(@F:%.o=%.td)"; exit 1; \
	fi
	@echo "  ^_^ CXX $@"
