// hex.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>

using namespace std;

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

void DFSRed(const vector<vector<char>>& matrix, vector<vector<bool>>& visited, int row, int col, int size) 
{
    // Mark the current cell as visited
    visited[row][col] = true;

    // Define the possible moves: up, down, left, right, diagonally left-up, diagonally right-down
    int dr[] = { -1, 1, 0, 0, -1, 1 };
    int dc[] = { 0, 0, -1, 1, -1, 1 };

    // Iterate through all possible moves
    for (int i = 0; i < 6; ++i) {
        int new_row = row + dr[i];
        int new_col = col + dc[i];

        // Check if the new cell is within bounds and contains 'b'
        if (new_row >= 0 && new_row < size && new_col >= 0 && new_col < size &&
            matrix[new_row][new_col] == 'r' && !visited[new_row][new_col]) {
            DFSRed(matrix, visited, new_row, new_col, size);
        }
    }
}

// Function to check if left side is connected to right side
bool isConnectedRed(const vector<vector<char>>& matrix, int size) {
    vector<vector<bool>> visited(size, vector<bool>(size, false));

    // Start DFS from the left side
    for (int i = 0; i < size; ++i) {
        if (matrix[i][0] == 'r' && !visited[i][0]) {
            DFSRed(matrix, visited, i, 0, size);
        }
    }

    // Check if any cell on the right side is visited
    for (int i = 0; i < size; ++i) {
        if (visited[i][size - 1]) {
            return true;
        }
    }

    return false;
}

void DFSBlue(const vector<vector<char>>& matrix, vector<vector<bool>>& visited, int row, int col, int size) {
    // Mark the current cell as visited
    visited[row][col] = true;

    // Define the possible moves: up, down, left, right, diagonally left-up, diagonally right-down
    int dr[] = { -1, 1, 0, 0, -1, 1 };
    int dc[] = { 0, 0, -1, 1, -1, 1 };

    // Iterate through all possible moves
    for (int i = 0; i < 6; ++i) {
        int new_row = row + dr[i];
        int new_col = col + dc[i];

        // Check if the new cell is within bounds and contains 'b'
        if (new_row >= 0 && new_row < size && new_col >= 0 && new_col < size &&
            matrix[new_row][new_col] == 'b' && !visited[new_row][new_col]) {
            DFSBlue(matrix, visited, new_row, new_col, size);
        }
    }
}

// Function to check if the first row is connected to the last row by 'b'
bool isConnectedBlue(const vector<vector<char>>& matrix, int size) {
    vector<vector<bool>> visited(size, vector<bool>(size, false));

    // Start DFS from the first row
    for (int j = 0; j < size; ++j) {
        if (matrix[0][j] == 'b' && !visited[0][j]) {
            DFSBlue(matrix, visited, 0, j, size);
        }
    }

    // Check if any cell in the last row is visited
    for (int j = 0; j < size; ++j) {
        if (visited[size - 1][j]) {
            return true;
        }
    }

    return false;
}




void options(string option, vector<char>& hexElements, int amountOfCells, int amountOfPawns, int amountOfBlue, int amountOfRed, vector<vector<char>>& elements, int size)
{
    if (option == "BOARD_SIZE")
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
        }
    }
    else if (option == "PAWNS_NUMBER")
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
        }
    }
    else if (option == "IS_BOARD_CORRECT")
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
            }
            else
            {
                cout << "NO" << endl << endl;
            }
        }
    }
    else if (option == "IS_GAME_OVER")
    {
        if (hexElements.empty())
        {
            return;
        }
        else
        {
            if (checkIfBoardCorrect(amountOfBlue, amountOfRed, hexElements))
            {
                if (isConnectedBlue(elements, size))
                {
                    cout << "YES BLUE" << endl << endl;
                }
                else
                {
                    if (isConnectedRed(elements, size))
                    {
                        cout << "YES RED" << endl << endl;
                    }
                    else
                    {
                        cout << "NO" << endl << endl;
                    }
                }
            }
            else
            {
                cout << "NO" << endl << endl;
            }
        } 
    }
    else if (option == "IS_BOARD_POSSIBLE ")
    {

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
    while (getline(cin, line) && line != "BOARD_SIZE" && line!= "PAWNS_NUMBER" && line!= "IS_BOARD_CORRECT" && line!="IS_GAME_OVER")
    {
        hex.push_back(line);
    }
    option = line;
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

    /*if (isConnectedRed(elements, size))
    {
        cout << "YES RED" << endl;
    }
    else 
    {
        cout << "NO RED" << endl;
    }

    if (isConnectedBlue(elements, size)) {
        cout << "YES BLUE" << endl;
    }
    else {
        cout << "NO BLUE" << endl;
    }*/




    options(option, hexElements, amountOfCells, amountOfPawns, amountOfBlue, amountOfRed, elements, size);

    hex.clear();
    hexElements.clear();
    cells.clear();
    elements.clear();
    char getChar;
    if (cin.get(getChar) && getChar == '\n' && cin.peek() != '\n')
    {
        loading(line, hex, option, hexElements, amountOfCells, amountOfPawns, amountOfBlue, amountOfRed, cells);
        return;
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
