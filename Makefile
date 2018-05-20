CXX = g++-5
CXXFLAGS = -std=c++14 -Werror=vla
EXEC = chess
OBJECTS = cell.o main.o board.o textdisplay.o graphicsdisplay.o window.o king.o queen.o pawn.o knight.o rook.o bishop.o player.o computer.o emptycell.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
