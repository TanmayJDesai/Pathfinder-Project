#include <iostream>
#include <cstdlib>
#include <string>
#include <queue>
using namespace std;

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec);

class Coord
{
  public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
  private:
    int m_r;
    int m_c;
};

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
    queue<Coord> Mapper;
    Coord a(sr, sc);
    Mapper.push(a);
    maze[sr][sc] = '^';
    while (!Mapper.empty())
    {
        Coord currentCoords = Mapper.front();
        Mapper.pop();

        int rw = currentCoords.r();
        int clm = currentCoords.c();
        if (rw == er && clm == ec)
        {
            return true;
        }
        if (maze[rw][clm-1] == '.')
        {
            Mapper.push(Coord(rw, clm-1));
            maze[rw][clm-1] = '^';
        }
        if (maze[rw+1][clm] == '.')
        {
            Mapper.push(Coord(rw+1, clm));
            maze[rw+1][clm] = '^';
        }
        if (maze[rw][clm+1] == '.')
        {
            Mapper.push(Coord(rw, clm+1));
            maze[rw][clm+1] = '^';
        }
        if (maze[rw-1][clm] == '.')
        {
            Mapper.push(Coord(rw-1, clm));
            maze[rw-1][clm] = '^';
        }
    }
    return false;

}

int main()
      {
          string maze[10] = {
              "XXXXXXXXXX",
              "X.X..X...X",
              "X....XXX.X",
              "X.XXXX.X.X",
              "X......XXX",
              "X.XX.X...X",
              "X.X..X.X.X",
              "X.X.XXXX.X",
              "X.X...X..X",
              "XXXXXXXXXX"
          };
      
          if (pathExists(maze, 10,10, 4,6, 1,1))
              cout << "Solvable!" << endl;
          else
              cout << "Out of luck!" << endl;
      }

