// hex.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define FIRST  "BOARD_SIZE"
#define SECOND "PAWNS_NUMBER"
#define THIRD  "IS_BOARD_CORRECT"
#define FOURTH "IS_GAME_OVER"
#define FIFTH  "IS_BOARD_POSSIBLE"

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

void DFS(const vector<vector<char>>& matrix, vector<vector<bool>>& visited, int row, int col, int size, char color)
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

        if (color == 'b')
        {
            // Check if the new cell is within bounds and contains 'b'
            if (new_row >= 0 && new_row < size && new_col >= 0 && new_col < size &&
                matrix[new_row][new_col] == 'b' && !visited[new_row][new_col]) {
                DFS(matrix, visited, new_row, new_col, size, 'b');
            }
        }
        else if (color == 'r')
        {
            // Check if the new cell is within bounds and contains 'b'
            if (new_row >= 0 && new_row < size && new_col >= 0 && new_col < size &&
                matrix[new_row][new_col] == 'r' && !visited[new_row][new_col]) {
                DFS(matrix, visited, new_row, new_col, size, 'r');
            }
        }

    }
}


// Function to check if the first row is connected to the last row by 'b'
bool isConnected(const vector<vector<char>>& matrix, int size, char color) 
{
    vector<vector<bool>> visited(size, vector<bool>(size, false));
    if (color == 'b')
    {
        // Start DFS from the first row
        for (int j = 0; j < size; ++j) {
            if (matrix[0][j] == 'b' && !visited[0][j]) {
                DFS(matrix, visited, 0, j, size, 'b');
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
    else 
    {
        // Start DFS from the left side
        for (int i = 0; i < size; ++i) {
            if (matrix[i][0] == 'r' && !visited[i][0]) {
                DFS(matrix, visited, i, 0, size, 'r');
            }
        }

        // Check if any cell on the right side is visited
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

int countPaths(const vector<vector<char>>& matrix, int size, char color) {
    vector<vector<bool>> visited(size, vector<bool>(size, false));
    int pathsFound = 0;

    // Start DFS from the left side
    for (int i = 0; i < size; ++i) {
        if (matrix[i][0] == color && !visited[i][0]) {
            DFS(matrix, visited, i, 0, size, color);
            pathsFound++;
        }
    }

    return pathsFound;
}


 bool hasMultiplePaths(const vector<vector<char>>& matrix, int size, char color) 
 {
    vector<vector<bool>> visited(size, vector<bool>(size, false));
    vector<pair<int, int>> start_positions;
    int pathsFound = 0;

    if (color == 'b') 
    {
        for (int j = 0; j < size; ++j) {
            if (matrix[0][j] == 'b'){
                start_positions.push_back({ 0, j });
            }
        }

        // Start DFS from every starting position
        for (const auto& start_pos : start_positions) {
            int start_row = start_pos.first;
            int start_col = start_pos.second;
            if (!visited[start_row][start_col]) {
                DFS(matrix, visited, start_row, start_col, size, 'b');
            }
        }

        // Check if any cell in the last row is visited
        for (int j = 0; j < size; ++j) {
            if (visited[size - 1][j]) {
                return true;
            }
        }
    }
    else 
    {
        // Start DFS from the left side
        for (int i = 0; i < size; ++i) {
            if (matrix[i][0] == 'r') {
                start_positions.push_back({ i, 0 });
            }
        }

        // Start DFS from every starting position
        for (const auto& start_pos : start_positions) {
            int start_row = start_pos.first;
            int start_col = start_pos.second;
            if (!visited[start_row][start_col]) {
                DFS(matrix, visited, start_row, start_col, size, 'r');
            }
        }

        // Check if any cell in the last column is visited
        for (int i = 0; i < size; ++i) {
            if (visited[i][size - 1]) {
                return true;
            }
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
                if (isConnected(elements, size, 'b'))
                {
                    cout << "YES BLUE" << endl << endl;
                }
                else
                {
                    if (isConnected(elements, size, 'r'))
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
    else if (option == "IS_BOARD_POSSIBLE")
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
                    cout << "YES"<<endl<<endl;
                    return;
                }
                else
                {
                    if (isConnected(elements, size, 'b'))
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
                    else if (isConnected(elements, size, 'r'))
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
    /*else if (option == "CAN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT" && option2 == )
    {
        cout << "kot";
    }*/
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
    string option2, option3, option4;
    while (getline(cin, line) && line != "BOARD_SIZE" && line!= "PAWNS_NUMBER" && line!= "IS_BOARD_CORRECT" && line!="IS_GAME_OVER"&&line!="IS_BOARD_POSSIBLE" && line!="CAN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT")
    {
        hex.push_back(line);
    }
    option = line;
    /*if (line == "CAN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT")
    {

        while(getline(cin, line))
        option2 = line;
        option3 = line;
        option4 = line;
    }
    //option = line;*/
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
    /*if (option == "CAN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT" && option2 == "CAN_BLUE_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT" && option3 == "CAN_RED_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT" && option4 == "CAN_BLUE_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT")
    {
        cout << "KOT";
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
