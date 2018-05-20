#ifndef _OBSERVER_H_
#define _OBSERVER_H_
class Cell;

enum class Colour { None = -1, White, Black };
enum class PieceType { Empty = 0, Pawn, Bishop, Knight, Rook, Queen, King };

class Observer {
	public:
	virtual void notify(Cell &c) = 0;  // c is the Cell that called the notify method
	virtual ~Observer() = default;
};
#endif
