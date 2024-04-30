// hex.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>

using namespace std;


//Function that returns size of board
int boardSize(int amountOfCells)
{
    switch (amountOfCells)
    {
    case 1:
        return 1;
    case 4:
        return 2;
    case 9:
        return 3;
    case 16:
        return 4;
    case 25:
        return 5;
    case 36:
        return 6;
    case 49:
        return 7;
    case 64:
        return 8;
    case 81:
        return 9;
    case 100:
        return 10;
    case 121:
        return 11;
    }
    return 0;
}

//Function checking if there is correct amount of pawns on the board
bool checkIfBoardCorrect(int amountOfBlue, int amountOfRed, vector<char>& hexElements)
{
    for (int i = 0; i < hexElements.size(); i++)
    {
        if (hexElements[i] == 'b')
        {
            amountOfBlue++;
        }
        else if (hexElements[i] == 'r')
        {
            amountOfRed++;
        }
    }
    if (amountOfRed == amountOfBlue + 1 || amountOfRed == 0 && amountOfBlue == 0 || amountOfRed == amountOfBlue)
    {
        return true;
    }
    else
    {
        return false;
    }
}


//Function that fill vector cells
void fillCells(vector<char>& hexElements, vector<char>& cells)
{
    if (!hexElements.empty())
    {
        for (int i = 0; i < hexElements.size(); ++i)
        {
            if (hexElements[i] == '<')
            {
                if (hexElements[i + 1] == '>')
                {
                    cells.push_back('0');
                }
                else if (hexElements[i + 1] == 'r')
                {
                    cells.push_back('r');
                }
                else
                {
                    cells.push_back('b');
                }
            }
        }
    }
}


//Deep fisrt search function
void DFS(const vector<vector<char>>& board, vector<vector<bool>>& visited, int row, int col, int size, char color)
{
    visited[row][col] = true;

    //Possible moves: up, down, left, right, diagonally left-up, diagonally right-down
    int rowMoves[] = { -1, 1, 0, 0, -1, 1 };
    int columnMoves[] = { 0, 0, -1, 1, -1, 1 };

    //Going through all the possible directions
    for (int i = 0; i < 6; ++i) 
    {
        int newRow = row + rowMoves[i];
        int newColumn = col + columnMoves[i];

        if (color == 'b')
        {
            //Checking if new cell still belongs to the board and if it has blue pawn
            if (newRow>= 0 && newRow < size && newColumn >= 0 && newColumn < size && board[newRow][newColumn] == 'b' && !visited[newRow][newColumn]) 
            {
                DFS(board, visited, newRow, newColumn, size, 'b');
            }
        }
        else if (color == 'r')
        {
            //Checking if new cell still belongs to the board and if it has red pawn
            if (newRow >= 0 && newRow < size && newColumn >= 0 && newColumn < size && board[newRow][newColumn] == 'r' && !visited[newRow][newColumn]) 
            {
                DFS(board, visited, newRow, newColumn, size, 'r');
            }
        }

    }
}


// Function to check if the first row is connected to the last row by 'b'
bool isConnected(const vector<vector<char>>& board, int size, char color) 
{
    vector<vector<bool>> visited(size, vector<bool>(size, false));
    if (color == 'b')
    {
        //Starting from fisrt row and using deep first search looking path to the last row following blue pawns
        for (int j = 0; j < size; ++j) 
        {
            if (board[0][j] == 'b' && !visited[0][j]) 
            {
                DFS(board, visited, 0, j, size, 'b');
            }
        }

        //Checking if there was any cell visited in last row and based on this finnding out is it connected or not
        for (int j = 0; j < size; ++j) 
        {
            if (visited[size - 1][j]) 
            {
                return true;
            }
        }

        return false;
    }
    else 
    {
        //Starting from fisrt column and using deep first search looking path to the last column following red pawns
        for (int i = 0; i < size; ++i) 
        {
            if (board[i][0] == 'r' && !visited[i][0]) 
            {
                DFS(board, visited, i, 0, size, 'r');
            }
        }

        //Checking if there was any cell visited in last column and based on this finnding out is it connected or not
        for (int i = 0; i < size; ++i) 
        {
            if (visited[i][size - 1]) 
            {
                return true;
            }
        }

        return false;
    }

    
}


//Function to check if blue is still wining for IS_BOARD_POSSIBLE option
void checkIfBlueWins(int size, int amountOfBlue, int amountOfRed, vector<vector<char>>& elements)
{
    for (int i = size - 1; i >= 0; i--)
    {
        for (int j = 0; j < size; j++)
        {
            if (elements[j][i] == 'b')
            {
                char temp = elements[j][i];
                elements[j][i] = '0';
                amountOfBlue--;
                if (amountOfRed == amountOfBlue || amountOfRed == amountOfBlue + 1)
                {
                    if (isConnected(elements, size, 'b'))
                    {
                        elements[j][i] = temp;
                        amountOfBlue++;
                    }
                    else
                    {
                        cout << "YES" << endl << endl;
                        return;
                    }
                }
            }
            else
            {
                continue;
            }

        }
    }
    cout << "NO" << endl << endl;
    return;
    
}


//Function to check if red is still wining for IS_BOARD_POSSIBLE option
void checkIfRedWins(int size, int amountOfBlue, int amountOfRed, vector<vector<char>>& elements)
{
    for (int i = size - 1; i >= 0; i--)
    {
        for (int j = 0; j < size; j++)
        {
            if (elements[j][i] == 'r')
            {
                char temp = elements[j][i];
                elements[j][i] = '0';
                amountOfRed--;
                if (amountOfRed == amountOfBlue || amountOfRed == amountOfBlue + 1)
                {
                    if (isConnected(elements, size, 'r'))
                    {
                        elements[j][i] = temp;
                        amountOfRed++;
                    }
                    else
                    {
                        cout << "YES" << endl << endl;
                        return;
                    }
                }
            }
            else
            {
                continue;
            }
        }
    }
    cout << "NO" << endl << endl;
    return;
}


//Function for BOARD_SIZE option
void boardSizeOption(vector<char>& hexElements, int amountOfCells)
{
    if (hexElements.empty())
    {
        return;
    }
    else
    {
        for (int i = 0; i < hexElements.size(); i++)
        {
            if (hexElements[i] == '<')
            {
                amountOfCells++;
            }
        }
        cout << boardSize(amountOfCells) << endl << endl;
        return;
    }
}


//Function for PAWNS_NUMBER option
void pawnsNumberOption(vector<char>& hexElements, int amountOfPawns)
{
    if (hexElements.empty())
    {
        return;
    }
    else
    {
        for (int i = 0; i < hexElements.size(); i++)
        {
            if (hexElements[i] == 'b' || hexElements[i] == 'r')
            {
                amountOfPawns++;
            }
        }
        cout << amountOfPawns << endl << endl;
        return;
    }
}


//Function for IS_BOARD_CORRECT option
void isBoardCorrectOption(vector<char>& hexElements, int amountOfBlue, int amountOfRed)
{
    if (hexElements.empty())
    {
        return;
    }
    else
    {
        if (checkIfBoardCorrect(amountOfBlue, amountOfRed, hexElements))
        {
            cout << "YES" << endl << endl;
            return;
        }
        else
        {
            cout << "NO" << endl << endl;
            return;
        }
    }
}


//Function for IS_GAME_OVER option
void isGameOverOption(vector<char>& hexElements, int amountOfBlue, int amountOfRed, vector<vector<char>>& elements, int size)
{
    if (hexElements.empty())
    {
        return;
    }
    else
    {
        if (checkIfBoardCorrect(amountOfBlue, amountOfRed, hexElements))
        {
            if (isConnected(elements, size, 'b'))
            {
                cout << "YES BLUE" << endl << endl;
                return;
            }
            else
            {
                if (isConnected(elements, size, 'r'))
                {
                    cout << "YES RED" << endl << endl;
                    return;
                }
                else
                {
                    cout << "NO" << endl << endl;
                    return;
                }
            }
        }
        else
        {
            cout << "NO" << endl << endl;
            return;
        }
    }
}


//Function for IS_BOARD_POSSIBLE option
void isBoardPossibleOption(vector<char>& hexElements, int amountOfBlue, int amountOfRed, vector<vector<char>>& elements, int size)
{
    if (hexElements.empty())
    {
        return;
    }
    else
    {
        if (checkIfBoardCorrect(amountOfBlue, amountOfRed, hexElements))
        {
            for (int i = 0; i < hexElements.size(); i++)
            {
                if (hexElements[i] == 'b')
                {
                    amountOfBlue++;
                }
                else if (hexElements[i] == 'r')
                {
                    amountOfRed++;
                }
            }
            if (amountOfBlue == 0 && amountOfRed == 0)
            {
                cout << "YES" << endl << endl;
                return;
            }
            else
            {
                if (isConnected(elements, size, 'b'))
                {
                    checkIfBlueWins(size, amountOfBlue, amountOfRed, elements);
                }
                else if (isConnected(elements, size, 'r'))
                {
                    checkIfRedWins(size, amountOfBlue, amountOfRed, elements);
                }
                else
                {
                    cout << "YES" << endl << endl;
                    return;
                }
            }
        }
        else
        {
            cout << "NO" << endl << endl;
            return;
        }

    }
}


//Function for priniting output for Naive player options
void printingOutputForNaive(bool redWinIn1Move, bool blueWinIn1Move, bool redWinIn2Move, bool blueWinIn2Move)
{
    if (redWinIn1Move)
    {
        cout << "YES" << endl;
    }
    else
    {
        cout << "NO" << endl;
    }

    if (blueWinIn1Move)
    {
        cout << "YES" << endl;
    }
    else
    {
        cout << "NO" << endl;
    }

    if (redWinIn2Move)
    {
        cout << "YES" << endl;
    }
    else
    {
        cout << "NO" << endl;
    }

    if (blueWinIn2Move)
    {
        cout << "YES" << endl<<endl;
    }
    else
    {
        cout << "NO" << endl << endl;
    }
}

//Function gathering all the options
void options(string option, vector<char>& hexElements, int amountOfCells, int amountOfPawns, int amountOfBlue, int amountOfRed, vector<vector<char>>& elements, int size)
{
    if (option == "BOARD_SIZE")
    {
        boardSizeOption(hexElements, amountOfCells);
    }
    else if (option == "PAWNS_NUMBER")
    {
        pawnsNumberOption(hexElements, amountOfPawns);
    }
    else if (option == "IS_BOARD_CORRECT")
    {
        isBoardCorrectOption(hexElements, amountOfBlue, amountOfRed);
    }
    else if (option == "IS_GAME_OVER")
    {
        isGameOverOption(hexElements, amountOfBlue, amountOfRed, elements, size);
    }
    else if (option == "IS_BOARD_POSSIBLE")
    {
        isBoardPossibleOption(hexElements, amountOfBlue, amountOfRed, elements, size);
    }
    else if (option == "CAN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT")
    {
        bool redWinIn1Move = false;
        bool blueWinIn1Move = false;
        bool redWinIn2Move = false;
        bool blueWinIn2Move = false;
        int amountOfFreeCells = 0;

        if (hexElements.empty())
        {
            return;
        }
        else
        {
            if (checkIfBoardCorrect(amountOfBlue, amountOfRed, hexElements))
            {
                for (int i = 0; i < hexElements.size(); i++)
                {
                    if (hexElements[i] == 'b')
                    {
                        amountOfBlue++;
                    }
                    else if (hexElements[i] == 'r')
                    {
                        amountOfRed++;
                    }
                    else if (hexElements[i] == '<')
                    {
                        if (hexElements[i + 1] == '>')
                        {
                            amountOfFreeCells++;
                        }
                    }
                }
                if (amountOfRed == 0 && amountOfBlue == 0 && amountOfFreeCells == 1)
                {
                    redWinIn1Move = true;
                }
                else
                {
                    if (amountOfRed == amountOfBlue && amountOfFreeCells >= 1)
                    {
                        if (!isConnected(elements, size, 'r'))
                        {
                            for (int i = size - 1; i >= 0; i--)
                            {
                                for (int j = 0; j < size; j++)
                                {
                                    if (elements[j][i] == '0')
                                    {
                                        char temp = elements[j][i];
                                        elements[j][i] = 'r';
                                        if (isConnected(elements, size, 'r'))
                                        {
                                            redWinIn1Move = true;
                                            elements[j][i] = temp;
                                        }
                                        else
                                        {
                                            elements[j][i] = temp;
                                        }
                                    }
                                }
                            }
                        }

                    }
                    if (amountOfRed == amountOfBlue + 1 && amountOfFreeCells >= 2)
                    {
                        if (!isConnected(elements, size, 'r'))
                        {
                            for (int i = size - 1; i >= 0; i--)
                            {
                                for (int j = 0; j < size; j++)
                                {
                                    if (elements[j][i] == '0')
                                    {
                                        char temp = elements[j][i];
                                        elements[j][i] = 'r';
                                        if (isConnected(elements, size, 'r'))
                                        {
                                            redWinIn1Move = true;
                                            elements[j][i] = temp;
                                        }
                                        else
                                        {
                                            elements[j][i] = temp;
                                        }
                                    }
                                }
                            }
                        }

                    }
                    if (amountOfRed == amountOfBlue + 1 && amountOfFreeCells >= 1)
                    {
                        if (!isConnected(elements, size, 'b'))
                        {
                            for (int i = size - 1; i >= 0; i--)
                            {
                                for (int j = 0; j < size; j++)
                                {
                                    if (elements[j][i] == '0')
                                    {
                                        char temp = elements[j][i];
                                        elements[j][i] = 'b';
                                        if (isConnected(elements, size, 'b'))
                                        {
                                            blueWinIn1Move = true;
                                            elements[j][i] = temp;
                                        }
                                        else
                                        {
                                            elements[j][i] = temp;
                                        }
                                    }
                                }
                            }
                        }

                    }
                    if (amountOfRed == amountOfBlue && amountOfFreeCells >= 2)
                    {
                        if (!isConnected(elements, size, 'b'))
                        {
                            for (int i = size - 1; i >= 0; i--)
                            {
                                for (int j = 0; j < size; j++)
                                {
                                    if (elements[j][i] == '0')
                                    {
                                        char temp = elements[j][i];
                                        elements[j][i] = 'b';
                                        if (isConnected(elements, size, 'b'))
                                        {
                                            blueWinIn1Move = true;
                                            elements[j][i] = temp;
                                        }
                                        else
                                        {
                                            elements[j][i] = temp;
                                        }
                                    }
                                }
                            }
                        }

                    }
                    if (amountOfRed == amountOfBlue && amountOfFreeCells >= 3)
                    {
                        if (!isConnected(elements, size, 'r'))
                        {
                            for (int i = size - 1; i >= 0; i--)
                            {
                                for (int j = 0; j < size; j++)
                                {
                                    if (elements[j][i] == '0')
                                    {
                                        char temp = elements[j][i];
                                        elements[j][i] = 'r';
                                        if (isConnected(elements, size, 'r'))
                                        {
                                            elements[j][i] = temp;
                                            break;
                                        }
                                        for (int k = size - 1; k >= 0; k--)
                                        {
                                            for (int l = 0; l < size; l++)
                                            {
                                                if (elements[l][k] == '0')
                                                {
                                                    char check = elements[l][k];
                                                    elements[l][k] = 'r';
                                                    if (isConnected(elements, size, 'r'))
                                                    {
                                                        redWinIn2Move = true;
                                                        elements[l][k] = check;
                                                    }
                                                    else
                                                    {
                                                        elements[l][k] = check;
                                                    }

                                                }
                                            }
                                        }
                                        elements[j][i] = temp;
                                    }
                                }
                            }
                        }

                    }
                    if (amountOfRed == amountOfBlue + 1 && amountOfFreeCells >= 4)
                    {
                        if (!isConnected(elements, size, 'r'))
                        {
                            for (int i = size - 1; i >= 0; i--)
                            {
                                for (int j = 0; j < size; j++)
                                {
                                    if (elements[j][i] == '0')
                                    {
                                        char temp = elements[j][i];
                                        elements[j][i] = 'r';
                                        if (isConnected(elements, size, 'r'))
                                        {
                                            elements[j][i] = temp;
                                            break;
                                        }
                                        for (int k = size - 1; k >= 0; k--)
                                        {
                                            for (int l = 0; l < size; l++)
                                            {
                                                if (elements[l][k] == '0')
                                                {
                                                    char check = elements[l][k];
                                                    elements[l][k] = 'r';
                                                    if (isConnected(elements, size, 'r'))
                                                    {
                                                        redWinIn2Move = true;
                                                        elements[l][k] = check;
                                                    }
                                                    else
                                                    {
                                                        elements[l][k] = check;
                                                    }

                                                }
                                            }
                                        }
                                        elements[j][i] = temp;
                                    }
                                }
                            }
                        }

                    }
                    if (amountOfRed == amountOfBlue + 1 && amountOfFreeCells >= 3)
                    {
                        if (!isConnected(elements, size, 'b'))
                        {
                            for (int i = size - 1; i >= 0; i--)
                            {
                                for (int j = 0; j < size; j++)
                                {
                                    if (elements[j][i] == '0')
                                    {
                                        char temp = elements[j][i];
                                        elements[j][i] = 'b';
                                        if (isConnected(elements, size, 'b'))
                                        {
                                            elements[j][i] = temp;
                                            //cout << j << i << endl;
                                            //break;
                                        }
                                        for (int k = size - 1; k >= 0; k--)
                                        {
                                            for (int l = 0; l < size; l++)
                                            {
                                                if (elements[l][k] == '0')
                                                {
                                                    char check = elements[l][k];
                                                    elements[l][k] = 'b';
                                                    if (isConnected(elements, size, 'b'))
                                                    {
                                                        blueWinIn2Move = true;
                                                        elements[l][k] = check;
                                                        //cout << j << i << endl;
                                                    }
                                                    else
                                                    {
                                                        elements[l][k] = check;
                                                    }

                                                }
                                            }
                                        }
                                        elements[j][i] = temp;
                                    }
                                }
                            }
                        }

                    }
                    if (amountOfRed == amountOfBlue && amountOfFreeCells >= 4)
                    {
                        if (!isConnected(elements, size, 'b'))
                        {
                            for (int i = size - 1; i >= 0; i--)
                            {
                                for (int j = 0; j < size; j++)
                                {
                                    if (elements[j][i] == '0')
                                    {
                                        char temp = elements[j][i];
                                        elements[j][i] = 'b';
                                        if (isConnected(elements, size, 'b'))
                                        {
                                            elements[j][i] = temp;
                                            break;
                                        }
                                        for (int k = size - 1; k >= 0; k--)
                                        {
                                            for (int l = 0; l < size; l++)
                                            {
                                                if (elements[l][k] == '0')
                                                {
                                                    char check = elements[l][k];
                                                    elements[l][k] = 'b';
                                                    if (isConnected(elements, size, 'b'))
                                                    {
                                                        blueWinIn2Move = true;
                                                        elements[l][k] = check;
                                                    }
                                                    else
                                                    {
                                                        elements[l][k] = check;
                                                    }

                                                }
                                            }
                                        }
                                        elements[j][i] = temp;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }              
        
        printingOutputForNaive(redWinIn1Move, blueWinIn1Move, redWinIn2Move, blueWinIn2Move);       


    }
}

void changeHexInto2DMatrix(vector<char>& hexElements, vector<char>& cells, int size, vector<vector<char>>& elements)
{
    int size1 = size;
    int number = 0;
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size1;j++)
        {
            elements[j][i] = cells[number];
            cells.erase(cells.begin() + number);
            number += j;
        }
        /*for (int z = 0; z < cells.size(); ++z)
        {
            cout << cells[z] << ' ';
        }
        cout << endl;*/
        size1--;
        number = 0;
    }
    size1 = size;
    number = 0;
    int oppositeOfI = 1;
    int limit = 0;
    for (int j = 0; j < size - 1; j++)
    {
        for (int i = size - 1; i > limit; i--)
        {
            elements[i][oppositeOfI] = cells[number];
            oppositeOfI++;
            number++;

        }
        limit++;
        oppositeOfI = limit + 1;
    }

    /*for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            cout << elements[i][j];
        }
        cout << endl;
    }*/
}

void loading(string line, vector<string>& hex, string option, vector<char>& hexElements, int amountOfCells, int amountOfPawns, int amountOfBlue, int amountOfRed, vector<char>& cells)
{
    vector<string> naiveOpponent;
    while (getline(cin, line) && line != "BOARD_SIZE" && line!= "PAWNS_NUMBER" && line!= "IS_BOARD_CORRECT" && line!="IS_GAME_OVER"&&line!="IS_BOARD_POSSIBLE" && line!="CAN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT")
    {
        hex.push_back(line);
    }
    //option = line;
    if (line == "CAN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT")
    {
        option = line;
        naiveOpponent.push_back(line);
        for (int i = 0; i < 3; i++)
        {
            getline(cin, line);
            naiveOpponent.push_back(line);
        }
        
    }
    else
    {
        option = line;
    }
   
    for (int i = 0; i < hex.size(); i++)
    {
        string& str = hex[i];
        for (int i = 0; i < str.size(); i++)
        {
            char element = str[i];
            if (!isspace(element))
            {
                hexElements.push_back(element);
            }
        }
    }

    fillCells(hexElements, cells);

    /*for (int i = 0; i < cells.size(); ++i)
    {
        cout << cells[i] << ' ';
    }
    cout << endl;*/

    int size = boardSize(cells.size());
    vector<vector<char>> elements(size, vector<char>(size));


    changeHexInto2DMatrix(hexElements, cells, size,elements);  

    options(option, hexElements, amountOfCells, amountOfPawns, amountOfBlue, amountOfRed, elements, size);

    hex.clear();
    hexElements.clear();
    cells.clear();
    elements.clear();
    naiveOpponent.clear();
    char next;
    if (option == "CAN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT")
    {
        if (cin.get(next) && next != '\n')
        {
            loading(line, hex, option, hexElements, amountOfCells, amountOfPawns, amountOfBlue, amountOfRed, cells);
            return;
        }
    }
    else
    {
        if (cin.get(next) && next == '\n' && cin.peek() != '\n')
        {
            loading(line, hex, option, hexElements, amountOfCells, amountOfPawns, amountOfBlue, amountOfRed, cells);
            return;
        }
    }
   
}




int main()
{
    string line;
    vector<string> hex;
    string option;
    vector<char> hexElements;
    vector<char> cells;
    int amountOfCells = 0;
    int amountOfPawns = 0;
    int amountOfRed = 0;
    int amountOfBlue = 0;

    loading(line, hex, option, hexElements, amountOfCells, amountOfPawns, amountOfBlue, amountOfRed, cells);
    
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
