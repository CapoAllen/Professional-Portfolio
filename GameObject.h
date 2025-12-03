#pragma once
#include <iostream>
#include <vector>

class GameObject {
protected:
	char symbol;

public: 
	
	void setSymbol(char s) {
		symbol = s;
	}

	char getSymbol() {
		return symbol;
	}
};


class UserPlayer : public GameObject {

private:
	int x;
	int y;


public:

	UserPlayer(int x_ = 0, int y_ = 0, char s = 'X') {
		x = x_;
		y = y_;
		symbol = s;
	}


	void setX(int x) {
		x = x;
	}
	
	void setY(int y) {
		y = y;
	}



	int getX() {
		return x;
	}

	int getY() {
		return y;
	}


	bool move(char direction, int maxWidth, int maxHeight) {

		int oldX = x;
		int oldY = y;

		switch (direction) {
		case 'w':
			y--;
			break;
		case 's':
			y++;
			break;
		case 'a':
			x--;
			break;
		case 'd':
			x++;
			break;
		default:
			std::cout << "INVALID INPUUT ";
		}

		if (x < 0) x = 0;
		if (y < 0) y = 0;

		if (x > maxWidth) x = maxWidth;
		if (y > maxHeight) y = maxHeight;

		return (x != oldX || y != oldY);
	}


};