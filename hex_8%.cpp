#include <iostream>
#include <string>
#include <vector>

using namespace std;

void boardSize(int amountOfCells)
{
    switch (amountOfCells) 
    {
    case 1:
        cout<<"1"<<endl<<endl;
        return;
    case 4:
        cout<<"2"<<endl<<endl;
        return;
    case 9:
        cout<<"3"<<endl<<endl;
        return;
    case 16:
        cout<<"4"<<endl<<endl;
        return;
    case 25:
        cout<<"5"<<endl<<endl;
        return;
    case 36:
        cout<<"6"<<endl<<endl;
        return;
    case 49:
        cout<<"7"<<endl<<endl;
        return;
    case 64:
        cout<<"8"<<endl<<endl;
        return;
    case 81:
        cout<<"9"<<endl<<endl;
        return;
    case 100:
        cout<<"10"<<endl<<endl;
        return;
    case 121:
        cout<<"11"<<endl<<endl;
        return;
    }
    return;
}

void options(string option, vector<char>& hexElements, int amountOfCells, int amountOfPawns, int amountOfBlue, int amountOfRed)
{
    if (option == "BOARD_SIZE")
    {

        for (int i = 0; i < hexElements.size(); i++)
        {
            if (hexElements[i] == '<')
            {
                amountOfCells++;
            }
        }
        boardSize(amountOfCells);
    }
    else if (option == "PAWNS_NUMBER")
    {
        for (int i = 0; i < hexElements.size(); i++)
        {
            if (hexElements[i] == 'b' || hexElements[i] == 'r')
            {
                amountOfPawns++;
            }
        }
        cout << amountOfPawns;
    }
    else if (option == "IS_BOARD_CORRECT")
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
        if (amountOfRed == amountOfBlue+1 || amountOfRed == 0 && amountOfBlue == 0 || amountOfRed == amountOfBlue)
        {
            cout << "YES";
        }
        else
        {
            cout << "NO";
        }
    }
    else if (option == "IS_GAME_OVER")
    {

    }
    else if (option == "IS_BOARD_POSSIBLE ")
    {

    }
}

void loading( string line, vector<string>& hex, string option, vector<char>& hexElements, int amountOfCells, int amountOfPawns, int amountOfBlue, int amountOfRed, vector<char>& cells)
{
    while (getline(cin, line) && line != "BOARD_SIZE")
    {
        hex.push_back(line);
    }
    option = line;
    for (int i = 0; i < hex.size(); i++)
    {
        string& str = hex[i];
        // Concatenate each string in the vector
        for (int i = 0; i < str.size(); i++)
        {
            char element = str[i];
            if (!isspace(element))
            {
                hexElements.push_back(element);
            }
        }
    }
    options(option, hexElements, amountOfCells, amountOfPawns, amountOfBlue, amountOfRed);
    hex.clear();
    hexElements.clear();
    cells.clear();
    char getChar;
    if (cin.get(getChar) && getChar == '\n' && cin.peek() != '\n')
    {
        //cout << "kot";
        loading(line, hex, option, hexElements, amountOfCells, amountOfPawns, amountOfBlue, amountOfRed, cells);
        return;
    }
    //return;
}

int main()
{
    string line;
    vector<string> hex;
    string option;
    vector<char> hexElements;
    //vector<vector<char>> cells;
    vector<char> cells;
    //vector<vector<char>>elementns;
    int amountOfCells = 0;
    int amountOfPawns = 0;
    int amountOfRed = 0;
    int amountOfBlue = 0;

    
    loading(line, hex, option, hexElements, amountOfCells, amountOfPawns, amountOfBlue, amountOfRed, cells);

    // Read the input line by line
    /*while (true)
    {
        // Read the input line by line
        while (getline(cin, line) && line != "---")
        {
            if (line == "BOARD_SIZE")
            {
                option = line;
                break;
            }
            else if (line == "PAWNS_NUMBER")
            {
                option = line;
                break;
            }
            else if (line == "IS_BOARD_CORRECT")
            {
                option = line;
                break;
            }
            else
            {
                hex.push_back(line);
            }
        }


        for (int i = 0; i < hex.size(); i++)
        {
            string& str = hex[i];
            // Concatenate each string in the vector
            for (int i = 0; i < str.size(); i++)
            {
                char element = str[i];
                if (!isspace(element))
                {
                    hexElements.push_back(element);
                }
            }
        }

        /*for (int i = 0; i < hexElements.size(); i++)
        {
            if (hexElements[i] == '<')
            {
                amountOfCells++;
            }
        }*/

        //int size = boardSize(amountOfCells);
        /*/for (int i = 0; i < hexElements.size(); ++i)
        {
            if (hexElements[i] == '<')
            {
                if (hexElements[i + 1] == '>')
                {
                    //cells[i][j] = '0';
                    cells.push_back('0');
                }
                else if (hexElements[i + 1] == 'r')
                {
                    //cells[i][j] = 'r';
                    cells.push_back('r');
                }
                else
                {
                    //cells[i][j] = 'b';
                    cells.push_back('b');
                }
            }
        }

        for (int i = 0; i < cells.size(); ++i)
        {
            cout << cells[i] << ' ';
        }
        cout << endl;

        int size = boardSize(cells.size());
        int size1 = size;
        vector<vector<char>> elements(size, vector<char>(size));
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                elements[i][j] = 'w';
            }
        }
        //char elements[4][4];
        int k = 0;
        for (int i = 0; i < size; ++i)
        {
            for (int j = 0; j < size1;j++)
            {
                //k += j;
                elements[j][i] = cells[k];
                cells.erase(cells.begin()+k);
                k += j;
            }
            for (int z = 0; z < cells.size(); ++z)
            {
                cout << cells[z] << ' ';
            }
            cout << endl;
            size1--;
            k = 0;
        }
        size1 = size;
        //k = size-1;
        //k = 0;
        k = 0;
        //cout << k;
        int w = 1;
        int limit = 0;
        for (int j = 0; j < size - 1; j++)
        {
            for (int i = size-1; i > limit; i--)
            {
                elements[i][w] = cells[k];
                w++;
                k++;

            }
            limit++;
            w = limit + 1;
        }

        for (int i = 0; i <size; i++)
        {
            for (int j = 0; j <size ; j++)
            {
                cout << elements[i][j];
            }
            cout << endl;
        }

        options(option, hexElements, amountOfCells, amountOfPawns, amountOfBlue, amountOfRed);


        hex.clear();
        hexElements.clear();
        cells.clear();
        char nextChar;
        char anotherChar;
        if (cin.get(nextChar) && nextChar == '\n')
        {
            if (cin.get(anotherChar) && anotherChar != ' ')
            {
                break;
            }
        }

    }*/



    return 0;
}
