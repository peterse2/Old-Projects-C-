//
//  main.cpp
//  MazeSolver
//
//  Created by Emily Peterson on 4/11/15.
//  Copyright (c) 2015 Emily Peterson. All rights reserved.
//

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <stack>

using namespace std;

int bruteForceMazeSolver(int i, int j);
int backtrackingMazeSolver(int i, int j);
int greedyMazeSolver(int i, int j);
int divideAndConquerMazeSolver(int i, int j);
int dynamicProgrammingMazeSolver(int i, int j);
int randomizedMazeSolver(int i, int j);
int openPaths(int x, int y);

struct maze
{
	int rows;
	int cols;
	char matrix [100][100];
};

maze myMaze;

int main()
{
    using namespace std;
	//required variables
	ifstream in;
	in.open("sample_mazes/maze.txt");
	char line;
	if(!in.is_open()){
        cout << "Could not open file." << endl;
    }
	//read the matrix using plain c code, character by character
	in >> myMaze.rows;
	in >> line;
	in >> myMaze.cols;
	cout << "Reading a " << myMaze.rows << " by " << myMaze.cols << " matrix." << endl;
	//Burn the end of line character
	in.ignore(200,'\n');
	for(int i=0; i<myMaze.rows; i++){
		for(int j=0; j<myMaze.cols; j++)
		{
			in.get( myMaze.matrix[i][j] );
		}
		//Burn the end of line character
		in.ignore(200,'\n');
	}
	
	//Print the empty maze
	for(int i=0; i<myMaze.rows; i++){
		for(int j=0; j<myMaze.cols; j++)
			cout << myMaze.matrix[i][j];
		cout << endl;
	}
	int x=1,y=1;
	
	//Find starting coordinates
	for(int i=0; i<myMaze.rows; i++)
		for(int j=0; j<myMaze.cols; j++)
			if( myMaze.matrix[i][j] == 'S' ){
				x=i;
				y=j;
			}
	
	//Call a recursive mazeSolver
    int bfDistance = bruteForceMazeSolver(x,y);     //brute force? dnc?
    int btDistance = backtrackingMazeSolver(x,y);     //brute force? dnc?
    int gDistance = greedyMazeSolver(x,y);
    int dncDistance = divideAndConquerMazeSolver(x,y);
    int dpDistance = dynamicProgrammingMazeSolver(x,y);
    int rDistance = randomizedMazeSolver(x,y);
    
    cout << "Brute force distance: " << bfDistance << " units away!" << endl;
    cout << "Backtracking distance: " << btDistance << " units away!" << endl;
    cout << "Greedy distance: " << gDistance << " units away!" << endl;
    cout << "Divide and conquer distance: " << dncDistance << " units away!" << endl;
    cout << "Dynamic programming distance: " << dpDistance << " units away!" << endl;
    cout << "Randomized distance: " << rDistance << " units away!" << endl;
    
	//Print solved maze
	for(int i=0; i<myMaze.rows; i++){
		for(int j=0; j<myMaze.cols; j++)
			cout << myMaze.matrix[i][j];
		cout << endl;
	}
    return 0;
}

int bruteForceMazeSolver(int i, int j)
{
    int x = 0;
    int y = 0;
    for(int i=0; i<myMaze.rows; i++){
		for(int j=0; j<myMaze.cols; j++)
			cout << myMaze.matrix[i][j];
		cout << endl;
	}
    
    //Check for a path not taken
 	if(myMaze.matrix[i][j+1] == 'F' || myMaze.matrix[i][j-1] == 'F' ||
       myMaze.matrix[i+1][j] == 'F' || myMaze.matrix[i-1][j] == 'F' ||
       myMaze.matrix[i][j] == 'F'){
		return 0;
	}else if(myMaze.matrix[i][j+1] == ' '){
		myMaze.matrix[i][j+1] = 'x';
		return 1 + bruteForceMazeSolver(i, j+1);
	}else if(myMaze.matrix[i+1][j] == ' '){
		myMaze.matrix[i+1][j] = 'x';
		return 1 + bruteForceMazeSolver(i+1, j);
	}else if(myMaze.matrix[i-1][j] == ' '){
		myMaze.matrix[i-1][j] = 'x';
		return 1 + bruteForceMazeSolver(i-1, j);
    }else if(myMaze.matrix[i][j-1] == ' '){
		myMaze.matrix[i][j-1] = 'x';
		return 1 + bruteForceMazeSolver(i, j-1);
	}
    
    if(myMaze.matrix[i][j+1] == 'F' || myMaze.matrix[i][j-1] == 'F' ||
       myMaze.matrix[i+1][j] == 'F' || myMaze.matrix[i-1][j] == 'F'){
		return 0;
	}

        
    //Check for a path already taken
	else if(myMaze.matrix[i][j+1] == 'x' && myMaze.matrix[i][j+2] != '*'){
 		myMaze.matrix[i][j+1] = 'x';
		return 1 + bruteForceMazeSolver(i, j+1);
	}else if(myMaze.matrix[i][j-1] == 'x'&& myMaze.matrix[i][j-2] != '*'){
 		myMaze.matrix[i][j-1] = 'x';
		return 1 + bruteForceMazeSolver(i, j-1);
	}else if(myMaze.matrix[i+1][j] == 'x' && myMaze.matrix[i+2][j] != '*'){
 		myMaze.matrix[i+1][j] = 'x';
		return 1 + bruteForceMazeSolver(i+1, j);
	}else if(myMaze.matrix[i-1][j] == 'x' && myMaze.matrix[i-2][j] != '*'){
 		myMaze.matrix[i-1][j] = 'x';
		return 1 + bruteForceMazeSolver(i-1, j);
    }else{
        for(int i=0; i<myMaze.rows; i++)
            for(int j=0; j<myMaze.cols; j++)
                if( myMaze.matrix[i][j] == 'S' ){
                    x=i;
                    y=j;
                }
		//myMaze.matrix[x][y] = 'x';
 		return bruteForceMazeSolver(x,y);
	}
    for(int i=0; i<myMaze.rows; i++){
		for(int j=0; j<myMaze.cols; j++)
			cout << myMaze.matrix[i][j];
		cout << endl;
	}
    //return 0;
}

int backtrackingMazeSolver(int i, int j){
    int x=1,y=1;
    stack<int> mem;
	
	//Find starting coordinates
	for(int i=0; i<myMaze.rows; i++)
		for(int j=0; j<myMaze.cols; j++)
			if( myMaze.matrix[i][j] == 'S' ){
				x=i;
				y=j;
                mem.push(y);
                mem.push(x);
			}
    
    //Tracing through the maze
    int c=y, r=x;
    int counter = 0;
    
    //continue going untill surrounded by "bread"
    while(myMaze.matrix[r][c+1] != '!' || myMaze.matrix[r][c-1] != '!' ||
          myMaze.matrix[r-1][c] != '!' || myMaze.matrix[r+1][c] != '!') {
        
        //if at finish
        if(myMaze.matrix[r][c+1] == 'F' || myMaze.matrix[r][c-1] == 'F' ||
           myMaze.matrix[r-1][c] == 'F' || myMaze.matrix[r+1][c] == 'F'){
            //Find starting coordinates
            for(int i=0; i<myMaze.rows; i++)
                for(int j=0; j<myMaze.cols; j++)
                    if( myMaze.matrix[i][j] == '!' ){
                        counter++;
                    }
            return counter;
        }
        else if(myMaze.matrix[r][c+1] == ' '){
            
            //add to mem if split
            if (openPaths(r, c) > 1) {
                mem.push(c);
                mem.push(r);
            }
            c++;
            myMaze.matrix[r][c] = '!';
        }else if(myMaze.matrix[r+1][c] == ' '){
            
            //add to mem if split
            if (openPaths(r, c) > 1) {
                mem.push(c);
                mem.push(r);
            }
            r++;
            myMaze.matrix[r][c] = '!';
        }else if(myMaze.matrix[r][c-1] == ' '){
            
            //add to mem if split
            if (openPaths(r, c) > 1) {
                mem.push(c);
                mem.push(r);
            }
            c--;
            myMaze.matrix[r][c] = '!';
        }else if(myMaze.matrix[r-1][c] == ' '){
            
            //add to mem if split
            if (openPaths(r, c) > 1) {
                mem.push(c);
                mem.push(r);
            }
            r--;
            myMaze.matrix[r][c] = '!';
        }else{
            r = mem.top();
            mem.pop();
            c = mem.top();
            mem.pop();
            //myMaze.matrix[r][c] = '!';
        }
    }
    return -1;
}
int greedyMazeSolver(int i, int j){
    //algorithm goes here
    return -1;
}
int divideAndConquerMazeSolver(int i, int j){
    //algorithm goes here
    return -1;
}
int dynamicProgrammingMazeSolver(int i, int j){
    //algorithm goes here
    return -1;
}
int randomizedMazeSolver(int i, int j){
    //algorithm goes here
    return -1;
}

int openPaths(int x, int y){
    int count = 0;
    if(myMaze.matrix[x+1][y] == ' ')
        count++;
    if(myMaze.matrix[x][y+1] == ' ')
        count++;
    if(myMaze.matrix[x-1][y] == ' ')
        count++;
    if(myMaze.matrix[x][y-1] == ' ')
        count++;
    return count;
}


