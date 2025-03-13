#include <iostream>
#include "labirint.h"
#include "mystack.h"
#include <windows.h>
using namespace std;
struct before {
  unsigned short x, y, lvl;
};

void SetConsoleFontSize(int width, int height) {
  CONSOLE_FONT_INFOEX cfi;
  cfi.cbSize = sizeof(CONSOLE_FONT_INFOEX);
  cfi.nFont = 0;
  cfi.dwFontSize.X = width;   // Ширина шрифта
  cfi.dwFontSize.Y = height;  // Высота шрифта
  cfi.FontFamily = FF_DONTCARE;
  cfi.FontWeight = FW_NORMAL;
  wcscpy_s(cfi.FaceName, L"Consolas");  // Название шрифтa
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  SetCurrentConsoleFontEx(hConsole, FALSE, &cfi);
}

int main() {
  SetConsoleOutputCP(CP_UTF8);
  SetConsoleFontSize(20, 20);

  labirint doungeon(12, 12, 2);
  string d =
      "w w w w w w w w w w w w "
      "w s f f f f f f w s f w "
      "w w w w w w w f w f f w "
      "w f f f f f w f w w f w "
      "w f w w w f w f f w f w "
      "w f w f w f w f f f f w "
      "w f w f f e f f f f w w "
      "w f w f w f f w f f f w "
      "w f w f w f f f f w f w "
      "w f w f w w w w f w f w "
      "w f w f f f f f f w e w "
      "w e w w w w w w w w w w "
      "                        "
      "w w w w w w w w w w w w "
      "w s f f f f f e w s f w "    
      "w f w w w w w w w f w w "
      "w f f f f f f f f f f w "
      "w w w w w w w w f w w w "    
      "w e w f f f f f f f f w "
      "w f w f f w w w f w f w "
      "w f w f f w f f f w f w "
      "w f w s f w f w w w f w "
      "w f w w w w f w f f f w "
      "w f f f f f f w e w f w "
      "w w w w w w w w w w w w ";
  doungeon.setl(d);
  doungeon.solve_maze();//w 
  doungeon.show_exits();
  cout << "##################################" << endl;
  
  for (unsigned short i = 0; i < doungeon.exits.size(); i++) {
    doungeon.show_console_exit(i);
  }
  //doungeon.show_best_path();
  //doungeon.show_all_pathes();

  /*mystack<char> a, b;
  a.push('g');
  a.push('d');
  a.show();
  b = a;
  cout << a.pop();
  cout << a.pop();
  a.push('');
  cout << a.pop();
  cout << b.pop();
  cout << b.pop();*/

  /*labirint a(20,20,1);
  a.generate();
  a.solve_maze();
  a.show_console_exit();*/

  system("pause");
	return 0; 
}

