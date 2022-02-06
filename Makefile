






# The libraries for pythia, fastjet, and root ( "LIB_TRI" )
# ccflg=-I${PYTHIA8}/include `${FASTJET3}/fastjet-config --cxxflags` `root-config --cflags`
# ldflg=-L${PYTHIA8}/lib -lpythia8 `${FASTJET3}/fastjet-config --libs` `root-config --glibs`
 
# ccflg= `root-config --cflags`
ccflg=`${FASTJET3}/fastjet-config --cxxflags` `root-config --cflags`
# ldflg= `root-config --glibs`
ldflg=`${FASTJET3}/fastjet-config --libs` `root-config --glibs`

# LIB_PYTH=-I${PYTHIA8}/include -L${PYTHIA8}/lib -lpythia8
LIB_FASTJET=`${FASTJET3}/fastjet-config --cxxflags --libs`
LIB_ROOT=`root-config --cflags --glibs`
LIB_DUO= ${LIB_ROOT} ${LIB_FASTJET}
# LIB_TRI=${LIB_PYTH} ${LIB_FASTJET} ${LIB_ROOT}

# compilation option
CC=g++
CFLAGS=-std=c++11 -O3 -Wno-deprecated
CFLAGS_CHECK=-std=c++11 -O0 -Wno-deprecated -g

bin/main: obj/events.o \
          obj/main.o   \
          obj/MemTimeProgression.o \
          obj/test_loop.o \
          obj/random_trk.o \
          obj/loc_funcs.o \
          obj/common_funcs.o \
          obj/eff_phi.o
	${CC} ${CFLAGS} -o $@ $^ ${LIB_DUO} 

obj/events.o: src/events.cxx src/events.h src/lists.h
	${CC} ${CFLAGS} ${ccflg} -c $< -o $@

obj/main.o: src/main.cxx src/events.h src/MemTimeProgression.h
	${CC} ${CFLAGS} ${ccflg} -c $< -o $@

obj/MemTimeProgression.o: src/MemTimeProgression.cxx src/MemTimeProgression.h
	${CC} ${CFLAGS} ${ccflg} -c $< -o $@

obj/test_loop.o: src/test_loop.cxx src/events.h
	${CC} ${CFLAGS} ${ccflg} -c $< -o $@

obj/random_trk.o: src/random_trk.cxx src/events.h src/loc_funcs.h src/common_funcs.h
	${CC} ${CFLAGS} ${ccflg} -c $< -o $@

obj/loc_funcs.o: src/loc_funcs.cxx src/loc_funcs.h
	${CC} ${CFLAGS} ${ccflg} -c $< -o $@

obj/common_funcs.o: src/common_funcs.cxx src/common_funcs.h
	${CC} ${CFLAGS} ${ccflg} -c $< -o $@

obj/eff_phi.o: src/eff_phi.cxx src/events.h
	${CC} ${CFLAGS} ${ccflg} -c $< -o $@
