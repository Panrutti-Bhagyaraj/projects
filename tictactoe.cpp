#include<bits/stdc++.h>
using namespace std;
char board[9]={'-','-','-','-','-','-','-','-','-'};
char resultBoard[9]={'-','-','-','-','-','-','-','-','-'};
int turns=9;
//printing the board
void printBoard()
{
	for(int i=0;i<9;i++)
	{
			cout<<board[i]<<" ";
		if((i+1)%3==0)
			cout<<"\n";
	}
}

//checking for match
char isMatch(char board[9])
{
	for(int i=0;i<3;i++)
	{
		if(board[3*i]==board[3*i+1] && board[3*i+1]==board[3*i+2] && board[3*i]!='-')
			return board[3*i];	
	}
	
	for(int i=0;i<3;i++)
	{
		if(board[i] == board[i+3] && board[i+3]==board[i+6] && board[i+3]!='-')
			return board[i+3];	
	}
	
	if(board[0]==board[4] && board[4]==board[8] && board[4]!='-')
		return board[4];
	if(board[2]==board[4] && board[4]==board[6] && board[4]!='-')
		return board[4];

	return 'N';//NONE
}
//Game is ended if there are no further moves 
bool isGameEnd()
{
	if(turns==0)
		return true;
	else if(turns==1 && 'O'!=isMatch(board))//If only left 1move there will be no chance for neither X nor O to win
	{
		cout<<"Game has been tied...\n";
		return true;
	}
	return false;
}

//inserting X in board
char insert(int pos)
{
	
	board[pos-1]='X';
	resultBoard[pos-1]='X';
	return isMatch(board);
}
//checking intial position which was entered by user is empty or not
bool checkBoard(int pos)
{
	
	return board[pos-1]=='X' || board[pos-1]=='O';
}
//generating random move for PC
void random()
{
	srand(time(0));
		int i= rand()%3;
		while(board[i]=='X' || board[i]=='O')
		{
			i= rand()%3;	
		} 
		board[i]='O';
		resultBoard[i]='O';
		turns--;	
}
//PC checking the winner by playing against itself
bool checkWin(char c)
{
		for(int i=0;i<9;i++)
		{
			if(board[i]=='-')
				{
					char temp = resultBoard[i],res;
					resultBoard[i]=c;
					res = isMatch(resultBoard);
					if(res == c)
					{
						board[i]='O';
						if(c=='X')
						{
							resultBoard[i]='O';
						}
						turns--;
						return true;
					}
					else
					{
						resultBoard[i]=temp;
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
		bool br = checkWin('O');//Chech if there is a chance to WIN for PC
		if(br)
			return;

		br = checkWin('X');//If no chance of having win for PC then tackle the Player X
		
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
