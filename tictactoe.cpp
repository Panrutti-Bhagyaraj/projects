#include<bits/stdc++.h>
using namespace std;
char board[3][3]={{'-','-','-'},{'-','-','-'},{'-','-','-'}};
char resultBoard[3][3]={{'-','-','-'},{'-','-','-'},{'-','-','-'}};
int turns=9;
//printing the board
void printBoard()
{
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
			cout<<board[i][j]<<" ";
		cout<<"\n";
	}
}

//checking for match
char isMatch(char board[3][3])
{
	for(int i=0;i<3;i++)
	{
		
		if(board[i][0] == board[i][1] && board[i][1]==board[i][2] && board[i][1]!='-')
			return board[i][0];	
	}
	
	for(int i=0;i<3;i++)
	{
		if(board[0][i] == board[1][i] && board[1][i]==board[2][i] && board[2][i]!='-')
			return board[0][i];	
	}
	
	if(board[0][0]==board[1][1] && board[2][2]==board[1][1] && board[2][2]!='-')
		return board[0][0];
	if(board[0][2]==board[1][1] && board[1][1]==board[2][0] && board[1][1]!='-')
		return board[1][1];

	return 'N';//NONE
}
//Game is ended if there are no further moves 
bool isGameEnd()
{
	if(turns==0)
		return true;
	else if(turns==1)//If only left 1move there will be no chance for neither X nor O to win
	{
		cout<<"Game has been tied...\n";
		return true;
	}
	return false;
}

//inserting X in board
char insert(int pos)
{
	if(pos==1)
	{
		board[0][0]='X';
		resultBoard[0][0]='X';
	}
	else if(pos==2)
	{
		board[0][1]='X';
		resultBoard[0][1]='X';
	}
	else if(pos==3)
	{
		board[0][2]='X';
		resultBoard[0][2]='X';
	}
	else if(pos==4)
	{
		board[1][0]='X';
		resultBoard[1][0]='X';

	}
	else if(pos==5)
	{
		board[1][1]='X';
		resultBoard[1][1]='X';
	}
	else if(pos==6)
	{
		board[1][2]='X';
		resultBoard[1][2]='X';
	}
	else if(pos==7)
	{
		board[2][0]='X';
		resultBoard[2][0]='X';
	}
	else if(pos==8)
	{
		board[2][1]='X';
		resultBoard[2][1]='X';
	}
	else if(pos==9)
	{
		board[2][2]='X';
		resultBoard[2][2]='X';
	}
	return isMatch(board);
}
//checking intial position which was entered by user is empty or not
bool checkBoard(int pos)
{
	if(pos==1)
	{
		return board[0][0]=='X' || board[0][0]=='O';
	}
	else if(pos==2)
	{
		return board[0][1]=='X' || board[0][1]=='O';
	}
	else if(pos==3)
	{
		return board[0][2]=='X' || board[0][2]=='O';
	}
	else if(pos==4)
	{
		return board[1][0]=='X' || board[1][0]=='O';
	}
	else if(pos==5)
	{
		return board[1][1]=='X' || board[1][1]=='O';
	}
	else if(pos==6)
	{
		return board[1][2]=='X' || board[1][2]=='O';
	}
	else if(pos==7)
	{
		return board[2][0]=='X' || board[2][0]=='O';
	}
	else if(pos==8)
	{
		return board[2][1]=='X' || board[2][1]=='O';
	}
	else if(pos==9)
	{
		return board[2][2]=='X' || board[2][2]=='O';
	}
	return true;
}
//generating random move for PC
void random()
{
	srand(time(0));
		int i= rand()%3, j=rand()%3;
		while(board[i][j]=='X' || board[i][j]=='O')
		{
			i= rand()%3; j=rand()%3;	
		} 
		board[i][j]='O';
		turns--;	
}
//computer checking the winner by playing against itself
bool checkWin(char c)
{
	
		for(int i=0;i<3;i++)
		{
			for(int j=0;j<3;j++)
			{
				if(board[i][j]=='-')
				{
					char temp = resultBoard[i][j],res;
					resultBoard[i][j]=c;
					res = isMatch(resultBoard);
					if(res == c)
					{
						board[i][j]='O';
						if(c=='X')
						{
							resultBoard[i][j]='O';
						}
						turns--;
						return true;
					}
					else
					{
						resultBoard[i][j]=temp;
					}
				}
			}
		}
	return false;
}

//PC move
void computer()
{
	if(turns==8)
	{
		random();
	}
	else
	{
		bool br = checkWin('O');
		if(br)
			return;

		br = checkWin('X');
		
		if(br)
			return;
		random();
	}
}

//Player X move
bool insertInBoard(int pos)
{
	if(!checkBoard(pos))
	{
		char res = insert(pos);
		if(res!='N')
		{
			cout<<"Player "<<res<<" has won the game:)\n";
			return true;
		}
		turns--;
		computer();
	}
	return false;
}


int main()
{
	
	while(!isGameEnd())
	{
		char res = isMatch(board);
		if(res!='N')
		{
			cout<<"Player "<<res<<" has won the game:)\n";
			break;
		}
		printBoard();
		cout<<"\n";
		int pos;
		cout<<"Enter the position to insert X   (1-9):\t";
		cin>>pos;
		bool end = insertInBoard(pos);
		if(end)
			break;
	}
	printBoard();
	return 0;
}
