# Makefile
#

ROOTCFLAGS    = $(shell root-config --cflags)
ROOTLIBS      = $(shell root-config --libs) -lMinuit -lGeom
ROOTGLIBS     = $(shell root-config --glibs)


MYOS := $(subst -,,$(shell uname))
MYOSV := $(shell uname -r| cut -s -d'.' -f6)
ifeq ($(MYOS),Darwin)
MYOSV := $(shell uname -r| cut -s -d'.' -f1)
endif
ifeq ($(MYOSV),)
MYOSV := $(shell uname -r| cut -s -d'.' -f4)
endif


#MYDIR := $(MYOS)_$(MYOSV)
#MYSTEREODIR := $(STEREO_BUILD)
IFLAGS =
#dune
DUNELIB =

VPATH = .:..:$(MYDIR)

MYDIR = ./

#ifeq ($(MYOS),Darwin)
  CXX = g++ 
  CXXFLAGS = -O4 -Wall -fPIC -DEXE
  CXXFLAGS     += $(ROOTCFLAGS)
  CXXFLAGS     += $(MYSQLCFLAGS)
  OPTIM=  -O4 -fexpensive-optimizations -funroll-loops
#  CLHEPLIBS := $(subst CLHEP-1,CLHEP.1,$(CLHEPLIBS))
  LIBS          = $(DUNELIB) $(ROOTLIBS)
  GLIBS         = $(ROOTGLIBS)
  LDFLAGS = -O4
#  LDFLAGS = -bind_at_load
#endif


IFLAGS += -I$(CANVAS_INC) -I$(CANVAS_ROOT_IO_INC)
IFLAGS += -I$(GALLERY_INC)
IFLAGS += -I$(CETLIB_EXCEPT_INC) -I$(CETLIB_INC)
IFLAGS += -I$(FHICLCPP_INC)
IFLAGS += -I$(LARDATAOBJ_INC) -I$(LARCOREOBJ_INC) -I$(LARCOREALG_INC)

DUNELIB += -L$(CANVAS_LIB) -lcanvas -L$(CANVAS_ROOT_IO_LIB) -lcanvas_root_io
DUNELIB += -L$(GALLERY_LIB) -lgallery
DUNELIB += -L$(CETLIB_EXCEPT_LIB) -lcetlib_except -L$(CETLIB_LIB) -lcetlib
DUNELIB += -L$(FHICLCPP_LIB) -lfhiclcpp
DUNELIB += -L$(LARDATAOBJ_LIB) -llardataobj_RawData -llardataobj_RecoBase


EXECS = $(MYDIR)/cnrStudy.exe

#all .cc files w/ main()
MSRCS = $(MYDIR)/cnrStudy.cc

#all supporting .cc files
#SSRCS  = $(MYDIR)/ROI.cc
#OBJS   = $(patsubst %.cc, %.o, $(SSRCS))

#-include $(MYDIR).o
#$(MYDIR).o:
#	@mkdir -p $(MYDIR)

all: $(EXECS)

# implicit rule to make .o
$(MYDIR)/%.o: $(MYDIR)/%.cc
	$(CXX) -c $(CXXFLAGS) $(IFLAGS) $(OPTIM) -o $@ $<

# implicit rule to make .exe
%.exe: $(MYDIR)/%.cc $(OBJS) 
	$(CXX) $(LDFLAGS) $(CXXFLAGS) $< ${OBJS} -o $@ $(LIBS) $(GLIBS) $(MYSQLLIBS) $(IFLAGS)
#-include $(MYDIR)/.cnrStudy.d

clean:
	@rm -f *~  .*.d *.o *.exe core 
