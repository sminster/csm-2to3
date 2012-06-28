
HEADERS=csm2to3plugin.h csm2to3model.h

OBJS=csm2to3plugin.o csm2to3model.o

CSMHOME=/programs/origin/users/sminster/csm-reform
TSMHOME=/programs/ipl/gots/csm/tsm-2A

INCLUDES=-I$(CSMHOME)/$(ARCH)/include -I$(TSMHOME)/$(ARCH)/include

LINK_LIB_CSM=-L$(CSMHOME)/$(ARCH)/lib -lcsmapi
LINK_LIB_TSM=-L$(TSMHOME)/$(ARCH)/lib -ltsmapi

LIBNAME=libcsm2to3
LIBVERSION=1.0

LIBRARY=$(LIBNAME).so.$(LIBVERSION)
LIBS=$(LINK_LIB_CSM) $(LINK_LIB_TSM) -lm -ldl

INSTDIR=$(PWD)/linux64

MKDIR=mkdir
CP=cp -f
LN=ln -s
TAR=tar

LD=$(CC)

%.o: %.cpp
	$(CC) -c $(COPTS) $(INCLUDES) $< -o $@

%.o: %.cc
	$(CC) -c $(COPTS) $(INCLUDES) $< -o $@

$(LIBRARY): $(OBJS)
	$(LD) $(COPTS) $(LDOPTS) $^ $(LIBS) -o $@

all: $(LIBRARY)

install::
	$(MKDIR) -p $(INSTDIR)/lib
	$(CP) $(LIBRARY) $(INSTDIR)/lib
	$(RM) $(INSTDIR)/lib/$(LIBNAME).so && $(LN) $(LIBRARY) $(INSTDIR)/lib/$(LIBNAME).so
	$(MKDIR) -p $(INSTDIR)/include/csm
	$(CP) $(HEADERS) $(INSTDIR)/include/csm

clean::
	$(RM) $(OBJS) $(LIBRARY) *~

package::
	$(TAR) -czvf csm-2to3.$(shell date '+%Y%m%d').tar.gz Makefile* *.cc *.h
