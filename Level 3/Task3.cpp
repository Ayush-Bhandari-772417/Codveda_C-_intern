#include <graphics.h>
#include <iostream>
#include <cstring>
#include <map>
#include <tuple>

using namespace std;

map<int, tuple<int, int, int, int>> gridInfo(int size) {
	map<int, tuple<int, int, int, int>> dictionary;
	int c=1, r=size/2;
	for(int i=(size+r); i<=3*size+r; i=i+size)
		for(int j=(size+r); j<=3*size+r; j=j+size){
			dictionary[c++] = make_tuple(j-r,i-r,j+r,i+r);
		}
	return dictionary;
}

map<int, tuple<int, int, int>> winningsituation() {
	map<int, tuple<int, int, int>> dictionary;
	dictionary[1] = make_tuple(1, 2, 3);
	dictionary[2] = make_tuple(1, 5, 9);
	dictionary[3] = make_tuple(1, 4, 7);
	dictionary[4] = make_tuple(2, 5, 8);
	dictionary[5] = make_tuple(3, 6, 9);
	dictionary[6] = make_tuple(3, 5, 7);
	dictionary[7] = make_tuple(4, 5, 6);
	dictionary[8] = make_tuple(7, 8, 9);
	return dictionary;
}

bool checkWin(map<int, char> &board, char symbol) {
	map<int, tuple<int, int, int>> win = winningsituation();
	for (auto &situation : win) {
		int a, b, c;
		tie(a, b, c) = situation.second;
		if (board[a] == symbol && board[b] == symbol && board[c] == symbol)
			return true;
	}
	return false;
}

void makegrid(int size){
	int p1, p2, p3, p4;
	p1 = size;
	p2 = 2*size;
	p3 = 3*size;
	p4 = 4*size;
	line(p1, p2, p4, p2);
	line(p1, p3, p4, p3);
	line(p2, p1, p2, p4);
	line(p3, p1, p3, p4);
}

void fillcircle(int size){
	int r=size/2;
	for(int i=(size+r); i<=3*size+r; i=i+size)
		for(int j=(size+r); j<=3*size+r; j=j+size)
			circle(i,j,r);
}

void fillcross(int size){
	int r=size/2;
	for(int i=(size+r); i<=3*size+r; i=i+size)
		for(int j=(size+r); j<=3*size+r; j=j+size){
			line(i,j,i+r,j+r);
			line(i,j,i+r,j-r);
			line(i,j,i-r,j+r);
			line(i,j,i-r,j-r);
		}
}

void drawX(int x1, int y1, int x2, int y2) {
	line(x1, y1, x2, y2);
	line(x1, y2, x2, y1);
}

void drawO(int x1, int y1, int x2, int y2) {
	int radius = (x2 - x1) / 2;
	int centerX = (x1 + x2) / 2;
	int centerY = (y1 + y2) / 2;
	circle(centerX, centerY, radius);
}

int main() {
	const int SIZE=80;
	char player1[30], player2[30], player1Symbol, player2Symbol;
	int flag=0, currentPlayer=1,x,y,ch,i=0,moves = 0,x1,x2,y1,y2;
	map<int, tuple<int, int, int>> win = winningsituation();
	map<int, tuple<int, int, int, int>> grid = gridInfo(SIZE);
	map<int, char> board;
	bool player1Turn = true, running = true, win_flag=false;
	for (int i = 1; i <= 9; ++i) {
		board[i] = ' ';
	}
	cout << "\n\t\t Welcome to Tic-Tac-Toe" << endl;
	cout << "Enter name of the first player : ";
	cin.getline(player1,30);
	cout << "Enter name of the second player : ";
	cin.getline(player2,30);
	while(true){
		cout << player1 << "'s choice selection" << endl;
		cout << "\t\t1. Noughts" << endl;
		cout << "\t\t2. Crosses" << endl;
		cout << "Enter your choice : ";
		cin >> ch;
		switch (ch) {
			case 1:{
				player1Symbol = 'O';
				player2Symbol = 'X';
				flag=1;
				break;
			}
			case 2:{
				player1Symbol = 'X';
				player2Symbol = 'O';
				flag=1;
				break;
			}
			default:{
				cout << "Wrong choice" << endl;
				break;
			}
		}
		if(flag==1)
			break;
	}

    cout << "Instructions:" << endl;
    cout << "You should click inside box area in your turn. " << endl << endl;

    cout << "Switch to another window to play the game. \n\t Press any key to switvh ...";
	
	int gd = DETECT, gm;
	initgraph(&gd, &gm, NULL);
	
	// Display prompt
	outtextxy(200, 10, "Welcome to the Board !!!");
	makegrid(SIZE);
	while (running) {
		if (moves == 9) {
			outtextxy(150, 400, "It's a draw!");
			break;
		}
        if(win_flag){
            outtextxy(150, 400, "Game Over!");
            break;
        }
		outtextxy(10, 30, (char*)&(player1Turn ? player1Symbol : player2Symbol));
		outtextxy(20, 30, "'s turn : ");
        outtextxy(10, 45, "Player : ");
        outtextxy(85, 45, "                                                     ");
        outtextxy(85, 45, (player1Turn ? player1 : player2));
		while (true){
			if (ismouseclick(WM_LBUTTONDOWN)) { // Check for left mouse button click
				getmouseclick(WM_LBUTTONDOWN, x, y); // Get the coordinates
				clearmouseclick(WM_LBUTTONDOWN); // Clear the click event
				
				for (map<int, tuple<int, int, int, int>>::iterator it = grid.begin(); it != grid.end(); ++it) {
					tie(x1, y1, x2, y2) = it->second; // Access the tuple in the map's value
					if (x >= x1 && x <= x2 && y >= y1 && y <= y2 && board[it->first] == ' ') {
						board[it->first] = player1Turn ? player1Symbol : player2Symbol;
						if (player1Turn)
							if(ch==1)
                                drawO(x1, y1, x2, y2);
                            else
                                drawX(x1, y1, x2, y2);
						else
                            if(ch==1)
                                drawX(x1, y1, x2, y2);
                            else
                                drawO(x1, y1, x2, y2);
						moves++;
                        if (checkWin(board, player1Turn ? player1Symbol : player2Symbol)) {
                            outtextxy(100, 360, "Congratulations ");
                            outtextxy(250, 360, (player1Turn ? player1 : player2));
                            outtextxy(170, 380, "You won the game !!!");
                            win_flag = true;
                            break;
                        }
                        player1Turn = !player1Turn;
						break;
					}
				}
                break;
			}
			if (kbhit()) { // Exit the loop if a key is pressed
				cout << "Exiting program." << endl;
				running = false;
				break;
			}
		}
		delay(50); // Small delay to avoid CPU overload
	}
	getch(); // Keep the graphics window open
	closegraph();
	return 0;
}