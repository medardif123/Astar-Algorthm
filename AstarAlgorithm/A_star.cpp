#include<bits/stdc++.h>
using namespace std;

#define ROWS 9
#define COLS 10

typedef pair<int, int> Pair;
typedef pair<double, pair<int, int>> pPair;
struct spot
{
    int previous_i, previous_j;
    double f, g, h;
};
spot spots[ROWS][COLS];
bool closedList[ROWS][COLS];
set<pPair> openList;
char grid[ROWS][COLS]=
{
     { '.', '#', '.', '.', '.', '.', '.', '.', '.', '.' },
     { '.', '.', '.', '#', '.', '.', '.', '#', '.', '.' },
     { '.', '.', '.', '#', '.', '.', '#', '.', '#', '.' },
     { '#', '#', '.', '#', '.', '#', '#', '#', '#', '.' },
     { '.', '.', '.', '#', '.', '.', '.', '#', '.', '#' },
     { '.', '#', '.', '.', '.', '.', '.', '.', '#', '#' },
     { '.', '#', '#', '#', '#', '.', '#', '.', '#', '.' },
     { '.', '#', '.', '.', '.', '.', '#', '.', '.', '.' },
     { '.', '.', '.', '#', '#', '#', '.', '#', '#', '.' }
};
void GREEN(char c,int d){
     if(d==0){
          printf("\033[32m%c\n",c);
          printf("\x1b[0m");
     }
     else{
          printf("\033[32m%c",c);
          printf("\x1b[0m");
          printf(",");
     }
}
bool isValid(int row, int col)
{
    return (row >= 0) && (row < ROWS) && (col >= 0) && (col < COLS);
}
bool notWall(char grid[ROWS][COLS], int row, int col)
{

     char diff ='#';
     if(grid[row][col]==diff){
          return false;
     }
     else{
          return true;
     }
}
bool isDestination(int row, int col, Pair dest)
{
    if (row == dest.first && col == dest.second)
        return true;
    else
        return false;
}
double heuristic(int row, int col, Pair dest)
{
    return ((double)sqrt ((row-dest.first)*(row-dest.first) + (col-dest.second)*(col-dest.second)));
}
bool exist(vector <Pair> path,int j,int k,int length){
     for(int l=0;l<length;l++){
          if(j==path[l].first && k==path[l].second){
               return true;
          }
     }
     return false;
}
void path(spot spots[ROWS][COLS], Pair dest)
{
    int row = dest.first;
    int col = dest.second;

    vector<Pair> Path;
    int i=0;
    while (!(spots[row][col].previous_i == row && spots[row][col].previous_j == col ))
    {
        Path.push_back(make_pair (row, col));
        int temp_ROWS = spots[row][col].previous_i;
        int temp_COLS = spots[row][col].previous_j;
        row = temp_ROWS;
        col = temp_COLS;
        i++;
    }
    Path.push_back(make_pair (row, col));
    for(int j=0;j<ROWS;j++){
         for(int k=0;k<COLS;k++){
              if(exist(Path,j,k,i+1) && k==COLS-1){
                   GREEN(grid[j][k],0);
              }
              else if(exist(Path,j,k,i+1)){
                   GREEN(grid[j][k],1);
              }
              else if(k==COLS-1){
                   cout<<grid[j][k]<<endl;
              }
              else{
                   cout<<grid[j][k]<<",";
              }
         }
    }
    return;
    }
bool addNeighbors(int i,int j,Pair dest){
     bool foundDest=false;
     double gNew, hNew, fNew;
     if (isValid(i-1, j) == true)
     {
         if (isDestination(i-1, j, dest) == true)
         {
             spots[i-1][j].previous_i = i;
             spots[i-1][j].previous_j = j;
             foundDest = true;
             return foundDest;
         }
         else if (closedList[i-1][j] == false && notWall(grid, i-1, j) == true)
         {
             gNew = spots[i][j].g + 1.0;
             hNew = heuristic (i-1, j, dest);
             fNew = gNew + hNew;
             if (spots[i-1][j].f == FLT_MAX || spots[i-1][j].f > fNew)
             {
                 openList.insert( make_pair(fNew,make_pair(i-1, j)));

                 spots[i-1][j].f = fNew;
                 spots[i-1][j].g = gNew;
                 spots[i-1][j].h = hNew;
                 spots[i-1][j].previous_i = i;
                 spots[i-1][j].previous_j = j;
             }
         }
     }
     if (isValid(i+1, j) == true)
     {
         if (isDestination(i+1, j, dest) == true)
         {
             spots[i+1][j].previous_i = i;
             spots[i+1][j].previous_j = j;
             foundDest = true;
             return foundDest;
         }
         else if (closedList[i+1][j] == false &&  notWall(grid, i+1, j) == true)
         {
             gNew = spots[i][j].g + 1.0;
             hNew = heuristic(i+1, j, dest);
             fNew = gNew + hNew;
             if (spots[i+1][j].f == FLT_MAX || spots[i+1][j].f > fNew)
             {
                 openList.insert( make_pair (fNew, make_pair (i+1, j)));
                 spots[i+1][j].f = fNew;
                 spots[i+1][j].g = gNew;
                 spots[i+1][j].h = hNew;
                 spots[i+1][j].previous_i = i;
                 spots[i+1][j].previous_j = j;
             }
         }
     }
     if (isValid (i, j+1) == true)
     {
         if (isDestination(i, j+1, dest) == true)
         {
             spots[i][j+1].previous_i = i;
             spots[i][j+1].previous_j = j;
             foundDest = true;
             return foundDest;
         }
         else if (closedList[i][j+1] == false && notWall (grid, i, j+1) == true)
         {
             gNew = spots[i][j].g + 1.0;
             hNew = heuristic (i, j+1, dest);
             fNew = gNew + hNew;
             if (spots[i][j+1].f == FLT_MAX ||  spots[i][j+1].f > fNew)
             {
                 openList.insert( make_pair(fNew,make_pair (i, j+1)));
                 spots[i][j+1].f = fNew;
                 spots[i][j+1].g = gNew;
                 spots[i][j+1].h = hNew;
                 spots[i][j+1].previous_i = i;
                 spots[i][j+1].previous_j = j;
             }
         }
     }
     if (isValid(i, j-1) == true)
     {
         if (isDestination(i, j-1, dest) == true)
         {
             spots[i][j-1].previous_i = i;
             spots[i][j-1].previous_j = j;
             foundDest = true;
             return foundDest;
         }
         else if (closedList[i][j-1] == false && notWall(grid, i, j-1) == true)
         {
             gNew = spots[i][j].g + 1.0;
             hNew = heuristic(i, j-1, dest);
             fNew = gNew + hNew;
             if (spots[i][j-1].f == FLT_MAX ||  spots[i][j-1].f > fNew)
             {
                 openList.insert( make_pair (fNew,make_pair (i, j-1)));
                 spots[i][j-1].f = fNew;
                 spots[i][j-1].g = gNew;
                 spots[i][j-1].h = hNew;
                 spots[i][j-1].previous_i = i;
                 spots[i][j-1].previous_j = j;
             }
         }
     }
}

void aStarSearch(char grid[ROWS][COLS], Pair src, Pair dest)
{
    if (isDestination(src.first, src.second, dest) == true)
    {
        printf ("We are already at the destination\n");
        return;
    }

    int i, j;

    for (i=0; i<ROWS; i++)
    {
        for (j=0; j<COLS; j++)
        {
            spots[i][j].f = FLT_MAX;
            spots[i][j].g = FLT_MAX;
            spots[i][j].h = FLT_MAX;
            spots[i][j].previous_i = -1;
            spots[i][j].previous_j = -1;
            closedList[i][j]=false;
        }
    }
    i = src.first, j = src.second;
    spots[i][j].f = 0.0;
    spots[i][j].g = 0.0;
    spots[i][j].h = 0.0;
    spots[i][j].previous_i = i;
    spots[i][j].previous_j = j;
    openList.insert(make_pair (0.0, make_pair (i, j)));
    bool foundDest = false;

    while (!openList.empty())
    {
        pPair p = *openList.begin();
        openList.erase(openList.begin());
        i = p.second.first;
        j = p.second.second;
        closedList[i][j] = true;
        foundDest =addNeighbors(i,j,dest);
    }
    if (!foundDest){
         cout <<"Failed to get to the destination"<<endl;
    }
    else{
         cout <<"destination found"<<endl;
    }
    return;
}
int main()
{
    Pair src = make_pair(0, 0);
    Pair dest = make_pair(ROWS-1, COLS-1);
    aStarSearch(grid, src, dest);
    path(spots,dest);
    return(0);
}
