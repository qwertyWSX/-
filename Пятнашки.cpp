#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include <time.h>
#include <conio.h>
#define DELAY() Sleep(500)
using namespace std;


int sizeT = 16; // размер поля
int sizeL = sqrt(sizeT); // размер строки (столбца)
int** cellVal = new int* [sizeL]; //Массив заначений основного поля

void putCursor(int x, int y)
{
    COORD position;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    position.X = x;
    position.Y = y;
    SetConsoleCursorPosition(hConsole, position);
}
//преобразование переданных координат в координаты соответствующие значению массива cellVal
void getPos(int val, int& x, int& y)
{
    for (int i = 0; i < sizeL; i++)
        for (int j = 0; j < sizeL; j++)
            if (cellVal[i][j] == val)
            {
                x = i; y = j;
                break;
            }
}
//Проверка ввода ДА/НЕТ
bool yesNoInput()
{
    char a;
    while (true)
    {
        a = _getch();
        switch (int(a))
        {
        case 48: //'0'
            putCursor(60, 20);
            for (int i = 0; i < 60; i++) cout << " ";
            putCursor(60, 20);
            return false;
        case 49: //'1'
            putCursor(60, 20);
            for (int i = 0; i < 60; i++) cout << " ";
            putCursor(60, 20);
            return true;
        }
    }
}
//Заполнение массива случайными числами
void fillArr()
{
    int* arr = new int [sizeT];
    for (int i = 0; i < sizeT; i++)
        arr[i] = i;

    for (int i = 0; i < sizeT; i++)
    {
        int temp = rand() % (sizeT - i); 
        cellVal[i%sizeL][i/sizeL] = arr[temp]; //присвоение ячейке значения из случайно выбранной ячейки массива arr
        for (int j = temp; j < sizeT-1; j++)
            arr[j] = arr[j + 1]; //сдвиг массива влево от temp
    }
    delete[] arr;
}
//Проверка на собираемость
bool checkTableSum()
{
    int* arr = new int[sizeT]; //приведение двумерного массива к одномерному
    int value=0;
    int e=0;

    for (int i = 0; i < sizeT; i++)
    arr[i] = cellVal[i % sizeL][i / sizeL];

    for (int i = 0; i < sizeT; i++)
    {
       if (arr[i] == 0)
        {
            e = (i / sizeL) + 1;
        }
       else 
       {
           for (int j = i + 1; j < sizeT; j++)
           {
               if (arr[i] > arr[j] && arr[j] != 0) value++;
           }
       }
    }    
    delete[] arr;
    if (sizeT == 9 ) return (value+e+1) % 2;
    if (sizeT == 16) return (value + e) % 2;
}
//Задать цвет символа и фон
void setColor(char background, char text)
{
    int b, t;

    switch (background)
    {
    case 'B':
        b = 0;
        break;
    case 'U':
        b = 1;
        break;
    case 'G':
        b = 2;
        break;
    case 'C':
        b = 3;
        break;
    case 'R':
        b = 4;
        break;
    case 'P':
        b = 5;
        break;
    case 'Y':
        b = 14;
        break;
    case 'W':
        b = 15;
        break;
    }
    switch (text)
    {
    case 'B':
        t = 0;
        break;
    case 'U':
        t = 1;
        break;
    case 'G':
        t = 2;
        break;
    case 'C':
        t = 3;
        break;
    case 'R':
        t = 4;
        break;
    case 'P':
        t = 5;
        break;
    case 'Y':
        t = 14;
        break;
    case 'W':
        t = 15;
        break;
    }

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (WORD)((b << 4) | t));
}
//Нарисовать ячейку поля
void drawSym(int num, int raw, int pr) // передача параметров значения, строку и состояния
{
    char cellDraw[5][9] = { {' ',' ',' ',' ',' ',' ',' ',' ',' '},
                          {' ',' ',' ',' ',' ',' ',' ',' ',' '},
                          {' ',' ',' ',' ',' ',' ',' ',' ',' '},
                          {' ',' ',' ',' ',' ',' ',' ',' ',' '},
                          {' ',' ',' ',' ',' ',' ',' ',' ',' '} };
    switch (num)
    {
    case 1:
        for (int i = 0; i < 5; i++)
            cellDraw[i][4] = '#';
        break;

    case 2:
        for (int i = 2; i < 7; i++)
            cellDraw[0][i] = '#';
        cellDraw[1][6] = '#';
        for (int i = 2; i < 7; i++)
            cellDraw[2][i] = '#';
        cellDraw[3][2] = '#';
        for (int i = 2; i < 7; i++)
            cellDraw[4][i] = '#';
        break;

    case 3:
        for (int i = 2; i < 7; i++)
            cellDraw[0][i] = '#';
        cellDraw[1][6] = '#';
        for (int i = 2; i < 7; i++)
            cellDraw[2][i] = '#';
        cellDraw[3][6] = '#';
        for (int i = 2; i < 7; i++)
            cellDraw[4][i] = '#';
        break;

    case 4:
        for (int i = 0; i < 5; i++)
            cellDraw[i][6] = '#';
        for (int i = 2; i < 7; i++)
            cellDraw[2][i] = '#';
        cellDraw[0][2] = '#';
        cellDraw[1][2] = '#';
        break;

    case 5:
        for (int i = 2; i < 7; i++)
            cellDraw[0][i] = '#';
        cellDraw[1][2] = '#';
        for (int i = 2; i < 7; i++)
            cellDraw[2][i] = '#';
        cellDraw[3][6] = '#';
        for (int i = 2; i < 7; i++)
            cellDraw[4][i] = '#';
        break;

    case 6:
        for (int i = 2; i < 7; i++)
        {
            cellDraw[0][i] = '#';
            cellDraw[2][i] = '#';
            cellDraw[4][i] = '#';
        }
        cellDraw[1][6] = '#';
        cellDraw[3][2] = '#';
        cellDraw[3][6] = '#';
        break;

    case 7:
        for (int i = 0; i < 5; i++)
            cellDraw[i][6] = '#';
        for (int i = 2; i < 6; i++)
            cellDraw[0][i] = '#';
        break;

    case 8:
        for (int i = 2; i < 7; i++)
        {
            cellDraw[0][i] = '#';
            cellDraw[2][i] = '#';
            cellDraw[4][i] = '#';
        }
        cellDraw[1][2] = '#';
        cellDraw[1][6] = '#';
        cellDraw[3][2] = '#';
        cellDraw[3][6] = '#';
        break;

    case 9:
        for (int i = 2; i < 7; i++)
        {
            cellDraw[0][i] = '#';
            cellDraw[2][i] = '#';
            cellDraw[4][i] = '#';
        }
        cellDraw[1][2] = '#';
        cellDraw[1][6] = '#';
        cellDraw[3][6] = '#';
        break;

    case 10:
        for (int i = 0; i < 5; i++)
        {
            cellDraw[i][1] = '#';
            cellDraw[i][3] = '#';
            cellDraw[i][7] = '#';
        }
        cellDraw[0][4] = '#';
        cellDraw[0][5] = '#';
        cellDraw[0][6] = '#';
        cellDraw[4][4] = '#';
        cellDraw[4][5] = '#';
        cellDraw[4][6] = '#';
        break;

    case 11:
        for (int i = 0; i < 5; i++)
        {
            cellDraw[i][2] = '#';
            cellDraw[i][6] = '#';
        }
        break;

    case 12:
        for (int i = 0; i < 5; i++)
            cellDraw[i][1] = '#';

        for (int i = 3; i < 8; i++)
            cellDraw[0][i] = '#';
        cellDraw[1][7] = '#';
        for (int i = 3; i < 8; i++)
            cellDraw[2][i] = '#';
        cellDraw[3][3] = '#';
        for (int i = 3; i < 8; i++)
            cellDraw[4][i] = '#';
        break;

    case 13:
        for (int i = 0; i < 5; i++)
            cellDraw[i][1] = '#';

        for (int i = 3; i < 8; i++)
        {
            cellDraw[0][i] = '#';
            cellDraw[2][i] = '#';
            cellDraw[4][i] = '#';
        }
        cellDraw[1][7] = '#';
        cellDraw[3][7] = '#';
        break;

    case 14:
        for (int i = 0; i < 5; i++)
            cellDraw[i][1] = '#';

        for (int i = 0; i < 5; i++)
            cellDraw[i][7] = '#';
        for (int i = 3; i < 8; i++)
            cellDraw[2][i] = '#';
        cellDraw[0][3] = '#';
        cellDraw[1][3] = '#';
        break;

    case 15:
        for (int i = 0; i < 5; i++)
            cellDraw[i][1] = '#';

        for (int i = 3; i < 8; i++)
        {
            cellDraw[0][i] = '#';
            cellDraw[2][i] = '#';
            cellDraw[4][i] = '#';
        }
        cellDraw[1][3] = '#';
        cellDraw[3][7] = '#';
        break;
    }
   // setColor('U', 'W');
    for (int i = 0; i < 9; i++)
    {
        if (pr == 0) (cellDraw[raw][i] == '#') ? setColor('W', 'W') : setColor('U', 'W');
        if (pr == 1) (cellDraw[raw][i] == '#') ? setColor('W', 'W') : setColor('P', 'G');
        cout << cellDraw[raw][i];
    }
    setColor('B', 'U');
}
//Нарисовать таблицу
void draw(int posX=0xFF, int posY=0xFF)
{
    if (posX == 0xFF && posY == 0xFF)
        getPos(0, posX, posY);

    int x = 5;
    int y = 3;

   putCursor(x, y);
   setColor('B', 'U');
    for (int z =0; z <= 11*sizeL+1; z++)
    cout << "=";
    y++;
    for (int k = 0; k < sizeL; k++)
    {
        for (int j = 0; j < 5; j++)
        {
            putCursor(x, y);
            for (int i = 0; i < sizeL; i++)
            {
                cout << "||";
                (i==posX && k==posY)? drawSym(cellVal[i][k], j, 1): drawSym(cellVal[i][k], j, 0);
            }
            cout << "||";
            y++;
        }
        putCursor(x, y);
        for (int z = 0; z <= 11 * sizeL + 1; z++)
            cout << "=";
        y++;
    }
    setColor('B', 'W');
    putCursor(60, 12);
}
//Чтение нажатия клавиши и перемещение по полю
char readKey(int &posX, int &posY)
{
    char a;
    while (true)
    {
        a = _getch();
        switch (int(a))
        {
        case 75: //стрелка влево
            if (posX > 0) posX--;
            return 'L';
        case 77: //стрелка вправо
            if (posX < sizeL - 1) posX++;
            return 'R';
        case 80: //стрелка вниз
            if (posY < sizeL - 1) posY++;        
            return 'D';
        case 72: //стрелка вверх
            if (posY > 0) posY--;
            return 'U';
        case 13: //Enter
            return 'E';
        case 27: //Esc
            putCursor(60, 20);
            cout << "Вы действительно хотите завершить? (1-ДА, 0-НЕТ): ";
            if (yesNoInput()) return 'Q';
            else continue;

            /*default:
            cout << int(a);
            return 0;*/
        }
    }
}
//Перемещение пятнашки
void moveCell(int posX, int posY)
{
    int temp;
    if ((posX - 1) >= 0 && cellVal[posX - 1][posY] == 0)
    {
        temp = cellVal[posX][posY];
        cellVal[posX][posY] = 0;
        cellVal[posX - 1][posY] = temp;
    }
    if ((posX + 1) < sizeL && cellVal[posX + 1][posY] == 0)
    {
        temp = cellVal[posX][posY];
        cellVal[posX][posY] = 0;
        cellVal[posX + 1][posY] = temp;
    }
    if ((posY + 1) < sizeL && cellVal[posX][posY + 1] == 0)
    {
        temp = cellVal[posX][posY];
        cellVal[posX][posY] = 0;
        cellVal[posX][posY+1] = temp;
    }
    if ((posY - 1) >= 0  && cellVal[posX][posY - 1] == 0)
    {
        temp = cellVal[posX][posY];
        cellVal[posX][posY] = 0;
        cellVal[posX][posY - 1] = temp;
    }
}
//Проверка на правильность постановки пятнашек
bool checkTablePos()
{
        for (int j = 0; j < sizeL*sizeL - 1; j++)
        {
         if (cellVal[j%sizeL][j/sizeL] != j + 1) return false;
        }
    return true;
}

//перестановка нуля со значением
void swapZero(int& zero, int& val, int &turns)
{
    int xVal, yVal, x0, y0;
    if (zero != 0)
    {
        putCursor(0, 2); cout << "Ошибка swapZero!!!"; cellVal[-1][-1] = 0xFF;
    }
    for (int i = 0; i < sizeL; i++)
    {
        for (int j = 0; j < sizeL; j++)
        {
            if (cellVal[i][j] == 0) { x0 = i; y0 = j; }
            if (cellVal[i][j] == val) { xVal = i; yVal = j; }
        }
    }
    if ((abs(x0 - xVal) == 1 && y0 - yVal == 0) || (abs(y0 - yVal) == 1 && x0 - xVal == 0))
    {
        swap(zero, val);
        turns++;
        draw();
        DELAY();
    }
    else { putCursor(0, 2); cout << "Ошибка swapZero!!!"; cellVal[-1][-1] = 0xFF; }
}
//передвежение нуля до нужной позиции 
void moveZero(int xF, int yF, int& turns, bool* cellBlocked[])
{
   /* bool arr[4][4];
    for (int i=0;i<sizeT; i++)
        arr[i%4][i/4]= cellBlocked[i % 4][i / 4];*/

    int x0, y0;
    getPos(0, x0, y0);
    //Создание векторов движения нуля
    int* vector[20];
    int xM = x0, yM = y0; // запомнить положение нуля
    vector[0] = &cellVal[xM][yM];
    int pos = 1;
    int falure1 = 0; // Проверка попадания в бесконечный цикл
    int falure2 = 0;
    int falure3 = 0;
    while (!(xM == xF) || !(yM == yF))
    {
        while (xM != xF)
        {
            (xM < xF) ? xM++ : xM--;
            if (!cellBlocked[xM][yM])
            {
                vector[pos] = &cellVal[xM][yM];
                pos++;
            }
            else
            {
                (x0 < xF) ? xM-- : xM++;
                if (yM < sizeL && !cellBlocked[xM][yM + 1])
                {
                    yM++;
                    vector[pos] = &cellVal[xM][yM];
                    pos++;
                }
                else if (yM - 1 >= 0 && !cellBlocked[xM][yM - 1])
                {
                    yM--;
                    vector[pos] = &cellVal[xM][yM];
                    pos++;
                }
                else break;
            }
        }

        while (yM != yF)
        {
            (yM < yF) ? yM++ : yM--;
            if (!cellBlocked[xM][yM])
            {
               vector[pos] = &cellVal[xM][yM];
               pos++;
            }
            else 
            { 
                (y0 < yF) ? yM-- : yM++;
                if (xM + 1 < sizeL && !cellBlocked[xM + 1][yM])
                {
                    xM++;
                    vector[pos] = &cellVal[xM][yM];
                    pos++;
                }
                else if (xM - 1 >= 0 && !cellBlocked[xM - 1][yM])
                {
                    xM--;
                    vector[pos] = &cellVal[xM][yM];
                    pos++;
                }
                else break;
            }
        }       
    }

    //Исключаем повторы для этого ищем откуда второй раз начинается ноль
    int start;
    for (int i = 0; i < pos - 1; i++)
        if (*vector[i] == 0) start = i;

    for (int i = start; i < pos - 1; i++)
        swapZero(*vector[i], *vector[i + 1], turns);
}
//передвижение значения (xF, yF - координаты клетки куда, необходимио пеоставить val)
void moveValAI(int val, int xF, int yF, int& turns, bool* cellBlocked[])
{
    int xVal, yVal;         //координаты значения
    int x0, y0;             // координаты нуля
    getPos(val, xVal, yVal);

    while (!(xF == xVal) || !(yF == yVal))
    {        
        //Определение точки куда поставить ноль 
        int x0F = xVal, y0F = yVal;
        if ((xF > xVal) && !cellBlocked[xVal + 1][yVal]) x0F = xVal + 1;
        if ((xF < xVal) && !cellBlocked[xVal - 1][yVal]) x0F = xVal - 1;
        if ((yF > yVal) && (x0F == xVal)) y0F = yVal + 1;
        if ((yF < yVal) && (x0F == xVal)) y0F = yVal - 1;

        if (x0F == xVal && y0F == yVal) { cout << "Ошибка moveValAI()!!!"; cellBlocked[-1][-1]=true; }

        getPos(0, x0, y0);
        if (!(x0F == x0) || !(y0F == y0))
        {
            cellBlocked[xVal][yVal] = true;
            moveZero(x0F, y0F, turns, cellBlocked);
            cellBlocked[xVal][yVal] = false;
        }

        swapZero(cellVal[x0F][y0F], cellVal[xVal][yVal], turns);
        getPos(val, xVal, yVal);
    }
}
//постановка последней в ряду клетки dir x- нужно поставить в конец ряда y- в конец столбца
void putLast(int x0, int y0, char dir, int& turns)
{
    int* vectorX[9];
    int* vectorY[13];
    if (dir == 'x')
    {
        vectorX[0] = &cellVal[x0][y0];
        for (int i=0; i<3;i++)
        vectorX[i+1] = &cellVal[x0+i][y0-1];
        vectorX[4] = &cellVal[x0 + 2][y0];
        vectorX[5] = &cellVal[x0 + 1][y0];
        vectorX[6] = &cellVal[x0 + 1][y0-1];
        vectorX[7] = &cellVal[x0][y0-1];
        vectorX[8] = &cellVal[x0][y0];

        for (int i = 0; i < 8; i++)
            swapZero(*vectorX[i], *vectorX[i + 1], turns);
    }
    else if (dir == 'y')
    {
        vectorY[0] = &cellVal[x0][y0];
        for (int i = 0; i < 3; i++)
            vectorY[i + 1] = &cellVal[x0 - i][y0 - 1];
        vectorY[4] = &cellVal[x0-2][y0];
        vectorY[5] = &cellVal[x0-2][y0+1];
        vectorY[6] = &cellVal[x0 - 1][y0 + 1];
        vectorY[7] = &cellVal[x0 - 1][y0];
        vectorY[8] = &cellVal[x0 - 2][y0];
        for (int i=0; i<3;i++)
        vectorY[i + 9] = &cellVal[x0 - 2 +i][y0 - 1];
        vectorY[12] = &cellVal[x0][y0];

        for (int i = 0; i < 12; i++)
            swapZero(*vectorY[i], *vectorY[i + 1], turns);
    }
}
//Собирает ИИ
void assembleAI()
{
    int turns = 0; //Кол-во ходов ИИ
    //Массив, определяющий клетки которые уже установленны на свои места
    bool** cellBlocked = new bool*[sizeL];
    for (int i = 0; i < sizeL; i++)
        cellBlocked[i] = new bool [sizeL];
    for (int i = 0; i < sizeT; i++)
        cellBlocked[i % sizeL][i / sizeL] = false;
    int val = 1;

    for (int j = 0; j < sizeL - 2; j++)
    {
        for (int i = 0; i < sizeL - 1; i++)
        {
            moveValAI(val, i, j, turns, cellBlocked);
            cellBlocked[i][j] = true;
            val++;
        }
        if (cellVal[sizeL - 1][j] == val) 
        { 
            cellBlocked[sizeL - 1][j] = true; 
            val++; 
        }
        else if (cellVal[sizeL - 1][j] == 0 && cellVal[sizeL - 1][j+1] == val)
        {
            swapZero(cellVal[sizeL - 1][j], cellVal[sizeL - 1][j+1], turns);
            cellBlocked[sizeL - 1][j] = true;
            val++;
        }
        else
        {
            moveValAI(val, sizeL - 1, j + 1, turns, cellBlocked);
            cellBlocked[sizeL - 1][j + 1] = true;
            moveZero(sizeL - 3, j + 1, turns, cellBlocked);
            putLast(sizeL-3, j+1, 'x', turns);
            cellBlocked[sizeL - 1][j + 1] = false;
            cellBlocked[sizeL - 1][j] = true;
            val++;
        }
    }

    for (int i = 0; i < sizeL - 2; i++)
    {
        moveValAI(val, i, val/sizeL, turns, cellBlocked);
        cellBlocked[i][val / sizeL] = true;
        val+=sizeL;

        if (cellVal[i][sizeL - 1] == val)
        {
            cellBlocked[i][sizeL - 1] = true;
            val-=(sizeL-1);
        }
        else if (cellVal[i][sizeL - 1] == 0 && cellVal[i + 1][sizeL - 1] == val)
        {
            swapZero(cellVal[i][sizeL - 1], cellVal[i+1][sizeL - 1], turns);
            cellBlocked[i][sizeL - 1] = true;
            val -= (sizeL - 1);
        }
        else
        {
            moveValAI(val, i + 1, sizeL - 1, turns, cellBlocked);
            cellBlocked[i + 1][sizeL - 1] = true;
            moveZero(i + 2, sizeL -2, turns, cellBlocked);
            putLast(i + 2, sizeL - 2, 'y', turns);
            cellBlocked[i + 1][sizeL - 1] = false;
            cellBlocked[i][sizeL-1] = true;
            val -= (sizeL - 1);
        }

    }

    int pos0;
    int* vector[4];
    vector[0] = &cellVal[sizeL-2][sizeL - 2];
    vector[1] = &cellVal[sizeL - 1][sizeL - 2];
    vector[2] = &cellVal[sizeL - 1][sizeL - 1];
    vector[3] = &cellVal[sizeL - 2][sizeL - 1];
    for (int i = 0; i < 4; i++)
    {
        if (*vector[i] == 0) 
        {
            pos0 = i; break;
        }
    }

    while (!checkTablePos())
    {
        if (pos0 < 3) 
        { 
            swapZero(*vector[pos0], *vector[pos0+1], turns);
            pos0++;
        }          
        else  
        { 
            swapZero(*vector[pos0], *vector[0], turns);
            pos0 = 0;
        }
    }

    putCursor(60, 12);
    cout << "Количество ходов ИИ: " << turns;
}


int main()
{
    srand(time(NULL));
    while (true)
    {
        int posX = 0; //координата Х текущей ячейки в таблице
        int posY = 0; //координата Y текущей ячейки в таблице
        int turns = 0; //кол-во ходов
        int** cellValMem = new int* [sizeL]; //Двумерный массив для запоминания первоначального положения клеток

        for (int i = 0; i < sizeL; i++)
        {
            cellVal[i] = new int[sizeL];
            cellValMem[i] = new int[sizeL];
        }

        do
        {
         fillArr();
        } while (checkTableSum());  // если нечетная, то не собирется

        for (int i = 0; i < sizeT; i++)
            cellValMem[i % sizeL][i / sizeL] = cellVal[i % sizeL][i / sizeL];

        setlocale(LC_ALL, "rus");
        putCursor(0, 0);
        cout << "Игра ПЯТНАШКИ ver.1\n";
        cout << "====================\n";
        putCursor(60, 3);
        cout << "Подсказки:";
        putCursor(60, 4);
        cout << "1. Для перемещения по полю используйте клавиши";
        putCursor(60, 5);
        cout << "   стрелок на клавиатуре.";
        putCursor(60, 6);
        cout << "2. Для перемещения числа на пусто квадрат.";
        putCursor(60, 7);
        cout << "   нажмите ENTER";
        putCursor(60, 8);
        cout << "3. Чтобы завершить и посмотреть ходы ИИ нажмите ESC.";

        unsigned int start_time = clock();
        while (true)
        {
            draw(posX, posY);
            char a = readKey(posX, posY);
            if (a == 'E')
            {
                moveCell(posX, posY);
                turns++;
                if (checkTablePos()) break;
            }
            else if (a == 'Q') break;
        }
        draw(posX, posY);
        putCursor(60, 10);
        cout << "Количество ходов: " << turns;
        unsigned int end_time = clock();
        putCursor(60, 11);
        int time_min = (end_time - start_time) / 60000;
        int time_sec = ((end_time - start_time) / 1000) - (time_min * 60);
        cout << "Затраченное время: " << time_min << " мин " << time_sec << "сек.";
        for (int i = 0; i < sizeL; i++)
        putCursor(60, 20);
        cout << "Посмотреть как собирет ИИ? (1-ДА, 0-НЕТ)";
        if (yesNoInput())
        {
            for (int i = 0; i < sizeT; i++)
            {
                cellVal[i % sizeL][i / sizeL] = cellValMem[i % sizeL][i / sizeL];
            }
            assembleAI();
        }
        putCursor(60, 20);
        cout << "Начать заново? (1-ДА, 0-НЕТ)";
        if (!yesNoInput()) break;
        putCursor(60, 10);
        cout << "                                                        ";
        putCursor(60, 11);
        cout << "                                                        ";
        putCursor(60, 12);
        cout << "                                                        ";
    }

  putCursor(0, 30);
  return 0;
}
