#pragma once
#include <iostream>
#include "myqueue.h"
#include "mystack.h"
#include <sstream>
#include <vector>
#include <windows.h>
using namespace std;
class labirint {
 public:
  struct before { // before ~ before point
    unsigned short x = 0, y = 0, lvl = 0;
  };
  struct sq {  // sq типо square
    unsigned short turn = 65535;
    char chr = 'w';  // w~wall  f~free  s~stairs  e~exit  v~visited
    before prev{0,0,0};
  };

  vector<before> exits;
  unsigned short n = 0, m = 0, x0 = 0, y0 = 0, maxlvl = 0, lvl0 = 0; // n, m, maxlvl - max index
  sq*** l = nullptr;  // labirint

  
  

  labirint() { n = m = maxlvl = 0; }

  labirint(unsigned short n1, unsigned short m1, unsigned short maxlvl1)
      : n(n1), m(m1), maxlvl(maxlvl1) {
    l = new sq**[n];
    for (unsigned short x = 0; x < n; x++) {
      l[x] = new sq*[m];
      for (unsigned short y = 0; y < m; y++) {
        l[x][y] = new sq[maxlvl];
        for (unsigned short z = 0; z < maxlvl; z++) {
          l[x][y][z].chr = 'w';
          l[x][y][z].turn = 0;
        }
      }
    }
  }

  labirint(const labirint &A) { 
    n = A.n;
      m = A.m;
    x0 = A.x0;
      y0 = A.y0;
    maxlvl = A.maxlvl;
    lvl0 = A.lvl0;
    exits = A.exits;
    l = new sq **[n];
    for (unsigned short x = 0; x < n; x++) {
      l[x] = new sq *[m];
      for (unsigned short y = 0; y < m; y++) {
        l[x][y] = new sq[maxlvl];
        for (unsigned short z = 0; z < maxlvl; z++) {
          l[x][y][z] = A.l[x][y][z];
        }
      }
    }
  }

  ~labirint() {
    for (unsigned short x = 0; x < n; x++) {
      for (unsigned short y = 0; y < m; y++) {
        delete[] l[x][y];
      }
      delete[] l[x];
    }
    delete[] l;
  }

  int solve_maze() {
    unsigned short nums = 0;
    myq<before> q;
    before b, buf;
    b.x = x0;
    b.y = y0;
    b.lvl = lvl0;
    l[x0][y0][lvl0].turn = 1;
    q.push(b);

    while (!q.isempty() && nums < 65535) {
      b = q.pop();
      vector<before> vec;

      is_valid_x(q, b.x, b.y, b.lvl);
      is_valid_y(q, b.x, b.y, b.lvl);
      is_valid_stairs(q, b.x, b.y, b.lvl);
    }
    return nums;
  }

  void is_valid_x(myq<before> &q, unsigned short x, unsigned short y,
                            unsigned short lvl) {
    if (x != 0) {
      unsigned short x1 = x - 1;
      if (l[x1][y][lvl].chr != 'w' && l[x1][y][lvl].turn == 0) {
        if (l[x1][y][lvl].chr == 'e')
          exits.push_back(before{x1, y, lvl});

          q.push(before{x1, y, lvl});

        l[x1][y][lvl].turn = l[x][y][lvl].turn + 1;
        l[x1][y][lvl].prev = before{x, y, lvl};
      }
    }
    

    if (x != n - 1) {
      unsigned short x2 = x + 1;
      if (l[x2][y][lvl].chr != 'w' && l[x2][y][lvl].turn == 0) {
        if (l[x2][y][lvl].chr == 'e')
          exits.push_back(before{x2, y, lvl});

          q.push(before{x2, y, lvl});

        l[x2][y][lvl].turn = l[x][y][lvl].turn + 1;
        l[x2][y][lvl].prev = before{x, y, lvl};
      }
    }
  }

  void is_valid_y(myq<before> &q, unsigned short x, unsigned short y,
                            unsigned short lvl) {
    if (y != 0) {
      unsigned short y1 = y - 1;
      if (l[x][y1][lvl].chr != 'w' && l[x][y1][lvl].turn == 0) {
        if (l[x][y1][lvl].chr == 'e')
          exits.push_back(before{x, y1, lvl});
        
          q.push(before{x, y1, lvl});

        l[x][y1][lvl].turn = l[x][y][lvl].turn + 1;
        l[x][y1][lvl].prev = before{x, y, lvl};
      }
    }
    

    if (y != m - 1) {
      unsigned short y2 = y + 1;
      if (l[x][y2][lvl].chr != 'w' && l[x][y2][lvl].turn == 0) {
        if (l[x][y2][lvl].chr == 'e')
          exits.push_back(before{x, y2, lvl});

          q.push(before{x, y2, lvl});

        l[x][y2][lvl].turn = l[x][y][lvl].turn + 1;
        l[x][y2][lvl].prev = before{x, y, lvl};
      }
    }
  }

  void is_valid_stairs(myq<before> &q, unsigned short x,
                                 unsigned short y, unsigned short lvl) {
    if (l[x][y][lvl].chr == 's') {
      if (lvl != 0) {
        unsigned short lvl1 = lvl - 1;
        if (l[x][y][lvl1].chr == 's' && l[x][y][lvl1].turn == 0) {
          q.push(before{x, y, lvl1});
          l[x][y][lvl1].turn = l[x][y][lvl].turn + 1;
          l[x][y][lvl1].prev = before{x, y, lvl};
        }
      }
      
      if (lvl != maxlvl - 1) {
        unsigned short lvl2 = lvl + 1;
        if (l[x][y][lvl2].chr == 's' && l[x][y][lvl2].turn == 0) {
          q.push(before{x, y, lvl2});
          l[x][y][lvl2].turn = l[x][y][lvl].turn + 1;
          l[x][y][lvl2].prev = before{x, y, lvl};
        }
      }
    }
  }


  void show_exits() {
    for (size_t i = 0; i < exits.size(); i++) {
      cout << "Exit number: " << i + 1 << "  x: " << exits[i].x
           << "  y: " << exits[i].y << "  lvl: " << exits[i].lvl
           << "  turns: " << l[exits[i].x][exits[i].y][exits[i].lvl].turn - 1 << endl;
    }
  }

  void show_best_path() { 
      cout << endl << "########################################" << endl;
      show_path(exits[0]);
      cout << "########################################" << endl;
  }

  void show_all_pathes() {
    for (unsigned short i = 0; i < exits.size(); i++) {
      cout << endl << "############\t" << "Path number "<< i+1 
          << "\t############" << endl;
      show_path(exits[i]);
      cout << "############################################" << endl;
    }

  }
  
  void show_path(before last) { 
      mystack<before> st;
      before c = last;
      
      while (!(c.x == x0 && c.y == y0 && c.lvl == lvl0)) {
        st.push(c);
        c = l[c.x][c.y][c.lvl].prev;
      }
      st.push(before{x0, y0, lvl0});
      unsigned short k = 0;
      while (!st.isempty()) {
        c = st.pop();
        cout << "Turn number " << k << "\t>> ";
        cout << "x = " << c.x << ", y = " << c.y << ", lvl = " << c.lvl << "."
             << endl;
        k++;
      }
  }

  void setl(string str) {
    x0 = 1;
    y0 = 1;
    istringstream in{str};
    for (unsigned short ur = 0; ur < maxlvl; ur++) {
      for (unsigned short x = 0; x < n; x++) {
        for (unsigned short y = 0; y < m; y++) {
          in >> l[x][y][ur].chr;
        }
      }
    }
  }

  void show_console_exit(const unsigned short &k = 0, unsigned short v = 65535) { 
      SetConsoleOutputCP(CP_UTF8);
    if (exits.empty()) {
        cout << "exits not found" << endl;
      return;
    }
      labirint x(*this);
      mystack<before> st;
      before c = exits[k];

      while (!(c.x == x.x0 && c.y == x.y0 && c.lvl == x.lvl0)) {
        st.push(c);
        c = l[c.x][c.y][c.lvl].prev;
      }
      //st.push(before{x.x0, x.y0, x.lvl0});
      if (v > x.l[exits[k].x][exits[k].y][exits[k].lvl].turn)
        v = x.l[exits[k].x][exits[k].y][exits[k].lvl].turn - 1;

      for (unsigned short i = 1; i < v; i++) {
        before z = st.pop();
        x.l[z.x][z.y][z.lvl].chr = 'x';
      }
      before z = st.pop();
      x.l[z.x][z.y][z.lvl].chr = 'y';

      cout << endl
           << "**********************************************" << endl
           << "     Exit number " << k + 1 << ": " << endl
           << endl;

    if (x.m > 70) {
      cout << "I cant display labirint" << endl;
      return;
    }
    if (x.maxlvl == 1) {
      cout <<  endl << endl 
          << "     Labirint and first " << v << " steps to exit::" << endl;
      for (unsigned short a = 0; a < n; a++) {
        cout << "   ";
        
        for (unsigned short b = 0; b < m; b++) {
          if (l[a][b][0].chr == 's') 
            if (l[a][b][0].chr == 'f' || a == x0 && b == y0)
              std::cout << u8"♠";
            else std::cout << u8"↑";
          else 
          if (a == x0 && b == y0) std::cout << u8"©";
          else {
            if (l[a][b][0].chr == 'f') std::cout << u8"◌";
            if (l[a][b][0].chr == 'w') std::cout << u8"■";
            if (l[a][b][0].chr == 'e') std::cout << u8"Ε";
            if (l[a][b][0].chr == 'x') std::cout << u8"●";
            if (l[a][b][0].chr == 'y') std::cout << u8"◊";
          }
        }
        for (int i = 0; i < 44 - 2*m; i++) {
          cout << " ";
        }
        for (unsigned short b = 0; b < m; b++) {
          if (x.l[a][b][0].chr == 's')
            if (x.l[a][b][0].chr == 'f' || a == x0 && b == y0)
              std::cout << u8"♠";
            else
              std::cout << u8"↑";
          else if (a == x0 && b == y0)
            std::cout << u8"©";
          else {
            if (x.l[a][b][0].chr == 'f') std::cout << u8"◌";
            if (x.l[a][b][0].chr == 'w') std::cout << u8"■";
            if (x.l[a][b][0].chr == 'e') std::cout << u8"Ε";
            if (x.l[a][b][0].chr == 'x') std::cout << u8"●";
            if (x.l[a][b][0].chr == 'y') std::cout << u8"◊";
          }
        }
        cout << endl;
      }
      cout << endl << endl;
        return;
    } else {
    
    
        cout << endl
           << endl
           << "     Labirint and first " << v << " steps to exit::" << endl;
      for (unsigned short z = 0; z < maxlvl; z++) {
          cout << endl << endl << "     Floor number " << z + 1 << ": " << endl;
          for (unsigned short a = 0; a < n; a++) {
            cout << "   ";

            for (unsigned short b = 0; b < m; b++) {
              if (l[a][b][z].chr == 's')
                if (l[a][b][z].chr == 'f' || a == x0 && b == y0 && z == lvl0)
                  std::cout << u8"♠";
                else
                  std::cout << u8"↑";
              else if (a == x0 && b == y0 && z == lvl0)
                std::cout << u8"©";
              else {
                if (l[a][b][z].chr == 'f') std::cout << u8"◌";
                if (l[a][b][z].chr == 'w') std::cout << u8"■";
                if (l[a][b][z].chr == 'e') std::cout << u8"Ε";
                if (l[a][b][z].chr == 'x') std::cout << u8"●";
                if (l[a][b][z].chr == 'y') std::cout << u8"◊";
              }
            }
            for (int i = 0; i < 44 - 2 * m; i++) {
              cout << " ";
            }
            for (unsigned short b = 0; b < m; b++) {
              if (x.l[a][b][z].chr == 's')
                if (x.l[a][b][z].chr == 'f' || a == x0 && b == y0 && z == lvl0)
                  std::cout << u8"♠";
                else
                  std::cout << u8"↑";
              else if (a == x0 && b == y0 && z == lvl0)
                std::cout << u8"©";
              else {
                if (x.l[a][b][z].chr == 'f') std::cout << u8"◌";
                if (x.l[a][b][z].chr == 'w') std::cout << u8"■";
                if (x.l[a][b][z].chr == 'e') std::cout << u8"Ε";
                if (x.l[a][b][z].chr == 'x') std::cout << u8"●";
                if (x.l[a][b][z].chr == 'y') std::cout << u8"◊";
              }
            }
            cout << endl;
          }
      }
      cout << endl
           << "**********************************************" << endl
           << endl;
    }
  }

  void generate() {
    int a = 0, b = 0;
    x0 = rand() % (n - 2) + 1;
    y0 = rand() % (m - 2) + 1;
    vector<pair<unsigned short, unsigned short>> vec{{x0, y0}};
    l[x0][y0][0].chr = 'f';
    short masx[]{0, 2, 0, -2};
    short masy[]{2, 0, -2, 0};
    for (unsigned short z = 0; z < maxlvl; z++) {
      for (unsigned short x = 0; x < n; x++) {
        for (unsigned short y = 0; y < m; y++) {
          l[x][y][z].chr = 'w';
          l[x][y][z].turn = 0;
          l[x][y][z].prev = {0, 0, 0};
        }
      }
      while (!vec.empty()) {
          int k = rand() % vec.size();
        int r = rand() % 4;
          for (short i = 0; i < 4; i++) {
          r = (r + i) % 4;
            int currx = vec[k].first + masx[r];
          int curry = vec[k].second + masy[r];
          if (currx > 0 && curry > 0 && currx < n - 1 && curry < m - 1 &&
                  l[currx][curry][z].chr != 'f') {
            vec.push_back({currx, curry});
            l[currx][curry][z].chr = 'f';
            l[vec[k].first + masx[r] /2][vec[k].second + masy[r]/2][z].chr = 'f';
            break;
          }
            if (i == 3) vec.erase(vec.begin() + k);
          }
      }
      for (int i = 0; i < (rand() % 4 + 1); i++) {
        a = rand() % n;
        b = rand() % m;
        if (a > 0 && b > 0 && l[a][b][z].chr == 'f' && (a!=x0 && b!= y0 && z!=lvl0)) {
          i++;
          l[a][b][z].chr = 'e';
        }
      }
     
      vec.push_back({a, b});
    }
  }
};