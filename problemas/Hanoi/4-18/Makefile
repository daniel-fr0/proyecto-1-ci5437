CC = gcc
CXX = g++
OPT = -Wall -O3 -Wno-unused-function -Wno-unused-variable
PSVNOPT = --state_map --backwards_moves --history_len=0
# PSVNOPT = --state_map --backwards_moves --fwd_history_len=1 --bwd_history_len=0
ROOT_DIR = ../../../

psvn2c_core.c:
	@cp $(ROOT_DIR)src/psvn2c_core.c ./psvn2c_core.c

psvn2c_state_map.c:
	@cp $(ROOT_DIR)src/psvn2c_state_map.c ./psvn2c_state_map.c

psvn2c_abstraction.c:
	@cp $(ROOT_DIR)src/psvn2c_abstraction.c ./psvn2c_abstraction.c

%.c: %.psvn psvn2c_core.c psvn2c_state_map.c psvn2c_abstraction.c
	@echo "**** Constructing $@ ..."
	@$(ROOT_DIR)bin/psvn2c $(PSVNOPT) --name=$(*F) < $< > $@
	@rm -f ./psvn2c_core.c ./psvn2c_state_map.c ./psvn2c_abstraction.c

.PRECIOUS: %.c

%.succ: %.c $(ROOT_DIR)global/succ.c
	@echo "**** Constructing $@ ..."
	@$(CC) $(OPT) $(ROOT_DIR)global/succ.c -include $< -o $@
	@rm -f $*.c

%.dist: %.c $(ROOT_DIR)global/dist.cpp
	@echo "**** Constructing $@ ..."
	@$(CXX) $(OPT) $(ROOT_DIR)global/dist.cpp -include $< -o $@
	@rm -f $*.c

%.distSummary: %.c $(ROOT_DIR)global/distSummary.cpp
	@echo "**** Constructing $@ ..."
	@$(CXX) $(OPT) $(ROOT_DIR)global/distSummary.cpp -include $< -o $@
	@rm -f $*.c

%.distSummaryPP: %.c $(ROOT_DIR)global/distSummaryPP.cpp
	@echo "**** Constructing $@ ..."
	@$(CXX) $(OPT) $(ROOT_DIR)global/distSummaryPP.cpp -include $< -o $@
	@rm -f $*.c

%.dist: %.c $(ROOT_DIR)global/dist.cpp
	@echo "**** Constructing $@ ..."
	@$(CXX) $(OPT) $(ROOT_DIR)global/dist.cpp -include $< -o $@
	@rm -f $*.c

%.generator: %.c $(ROOT_DIR)global/generator.cpp
	@echo "**** Constructing $@ ..."
	@$(CXX) $(OPT) $(ROOT_DIR)global/generator.cpp -include $< -o $@
	@rm -f $*.c

abstractor:
	@echo "**** Constructing abstractor ..."
	@$(CXX) $(OPT) $(ROOT_DIR)src/abstractor.cpp $(ROOT_DIR)src/psvn.cpp -o $@

%.pdb: abstractor
	@rm -f `basename $*`.abst `basename $*`.pdb `basename $*`.psvn
	@echo "**** Running abstractor on `dirname $*`.psvn with `basename $*`.txt ..."
	@./abstractor `dirname $*`.psvn `basename $*` < `basename $*`.txt > /dev/null
	@make `basename $*`.distSummaryPP
	@echo "**** Constructing PDB `basename $*`.pdb ..."
	@./`basename $*`.distSummaryPP `basename $*`.pdb
	@rm -f abstractor `basename $*`.distSummaryPP

pdb: part1.pdb part2.pdb

part1.pdb:
	make hanoi4-18/part1.pdb
	rm -f abstractor part1.psvn part1.distSummaryPP
	
part2.pdb:
	make hanoi4-18/part2.pdb
	rm -f abstractor part2.psvn part2.distSummaryPP

%.dist_pdb: %.c $(ROOT_DIR)global/dist_pdb.cpp
	@echo "**** Constructing $@ ..."
	@$(CXX) $(OPT) $(ROOT_DIR)global/dist_pdb.cpp -include $< -o $@
	@rm -f $*.c

%.A: %.c $(ROOT_DIR)global/A-estrella.cpp
	@echo "**** Constructing $@ ..."
	@$(CXX) $(OPT) $(ROOT_DIR)global/A-estrella.cpp -include $< -include ../heuristicaHanoi.cpp -o $@
	@rm -f $*.c

%.IDA: %.c $(ROOT_DIR)global/IDA-estrella.cpp
	@echo "**** Constructing $@ ..."
	@$(CXX) $(OPT) $(ROOT_DIR)global/IDA-estrella.cpp -include $< -include ../heuristicaHanoi.cpp -o $@
	@rm -f $*.c
	
.PHONY: clean
clean:
	rm -fr *.A *.succ *.dist *.distSummary *.distSummaryPP *.generator *.dist_pdb psvn2c_core.c psvn2c_state_map.c psvn2c_abstraction.c abstractor *.dSYM *.o *~ *.c
	find . -name "*.psvn" ! -name "hanoi4-18.psvn" -type f -exec rm -f {} +

clean_pdb:
	rm -fr *.pdb *.abst
