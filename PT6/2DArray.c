#include "2DArray.h"
#include "UI_Manager.h"

char** word;

void move_array(int street, int avenue) {
    int row, col, sizeX, sizeY;

    char letter1, letter2;
    
    letter1 = No;
    letter2 = We;

    sizeX = 4 + 5 * avenue;
    sizeY = 4 + 4 * street;

    word = (char**)malloc(sizeY * sizeof(char*));

    for (int i = 0; i < sizeY; i++) {
        word[i] = (char*)malloc(sizeX * sizeof(char));
    }

    for (row = 0; row < sizeY; row++) {
        for (col = 0; col < sizeX; col++)
            word[row][col] = space;
    }

    for (col = 2; col < sizeX; col++) {
        word[1][col] = We;
        word[2][col] = Ea;
        word[sizeY - 2][col] = We;
        word[sizeY - 1][col] = Ea;
    }

    for (row = 1; row < sizeY; row++) {
        if (row < 3)
            word[row][1] = So;
        else if (row == (sizeY - 1))
            word[row][1] = Ea;
        else {
            word[row][1] = ES;
            word[row][2] = No;
        }
    }

    for (row = 2; row < sizeY; row++) {
        if (row == 2)
        {
            word[row][sizeX - 1] = No;
            word[row][sizeX - 2] = So;
        }
        else if (row == (sizeY - 2))
        {
            word[row][sizeX - 1] = No;
            word[row][sizeX - 2] = We;
        }
        else if (row == (sizeY - 1))
        {
            word[row][sizeX - 1] = No;
            word[row][sizeX - 2] = Ea;
        }
        else
        {
            word[row][sizeX - 1] = WN;
            word[row][sizeX - 2] = So;
        }
    }

    /*for (int i = 0; i < xbuildings; i++) {
        for (int j = 0; j < ybuildings; j++) {
            fillBuilding(word, 3 + 4*i, 5 + 4*i, 3+ 4*j, 5+4*j);
        }
    }*/

    if (letter1 == So)
    {
        for (col = 7; col < (sizeX - 5); col += 10)
        {
            for (row = 1; row < sizeY; row++)
            {
                if (row == 1)
                    word[row][col] = WS;
                else if (row == 2)
                    word[row][col] = ES;
                else if ((row > 2 && (row - 2) % 4 == 0) && row != (sizeY - 2))
                    word[row][col] = word[row][col];
                else if (row == (sizeY - 2))
                    word[row][col] = WS;
                else if (row == (sizeY - 1))
                    word[row][col] = word[row][col];
                else
                    word[row][col] = So;
            }
        }
        for (col = 12; col < (sizeX - 5); col += 10)
        {
            for (row = 1; row < sizeY; row++)
            {
                if (row == 1)
                    word[row][col] = word[row][col];
                else if (row == 2)
                    word[row][col] = EN;
                else if ((row > 2 && (row - 2) % 4 == 0) && row != (sizeY - 2))
                    word[row][col] = word[row][col];
                else if (row == (sizeY - 2))
                    word[row][col] = WN;
                else if (row == (sizeY - 1))
                    word[row][col] = EN;
                else
                    word[row][col] = No;
            }
        }
    }
    else if (letter1 == No)
    {
        for (col = 12; col < (sizeX - 5); col += 10)
        {
            for (row = 1; row < sizeY; row++)
            {
                if (row == 1)
                    word[row][col] = WS;
                else if (row == 2)
                    word[row][col] = ES;
                else if ((row > 2 && (row - 2) % 4 == 0) && row != (sizeY - 2))
                    word[row][col] = word[row][col];
                else if (row == (sizeY - 2))
                    word[row][col] = WS;
                else if (row == (sizeY - 1))
                    word[row][col] = word[row][col];
                else
                    word[row][col] = So;
            }
        }
        for (col = 7; col < (sizeX - 5); col += 10)
        {
            for (row = 1; row < sizeY; row++)
            {
                if (row == 1)
                    word[row][col] = word[row][col];
                else if (row == 2)
                    word[row][col] = EN;
                else if ((row > 2 && (row - 2) % 4 == 0) && row != (sizeY - 2))
                    word[row][col] = word[row][col];
                else if (row == (sizeY - 2))
                    word[row][col] = WN;
                else if (row == (sizeY - 1))
                    word[row][col] = EN;
                else
                    word[row][col] = No;
            }
        }
    }
    if (letter2 == We)
    {
        for (row = 6; row < (sizeY - 5); row += 8)
        {
            for (col = 1; col < sizeX; col++)
            {
                if (col == 1)
                    word[row][col] = So;
                else if (col == 2)
                    word[row][col] = WN;
                else if ((col > 2 && (col - 2) % 5 == 0))
                    if (word[row - 1][col] == No)
                        word[row][col] = WN;
                    else
                        word[row][col] = WS;
                else if (col == (sizeX - 1))
                    word[row][col] = WN;
                else
                    word[row][col] = We;
            }
        }
        for (row = 10; row < (sizeY - 5); row += 8)
        {
            for (col = 1; col < sizeX; col++)
            {
                if (col == 1)
                    word[row][col] = ES;
                else if (col == 2)
                    word[row][col] = EN;
                else if ((col > 2 && (col - 2) % 5 == 0))
                    if (word[row - 1][col] == No)
                        word[row][col] = EN;
                    else
                        word[row][col] = ES;
                else if (col == (sizeX - 1))
                    word[row][col] = No;
                else
                    word[row][col] = Ea;
            }
        }
    }
    if (letter2 == Ea)
    {
        for (row = 10; row < (sizeY - 5); row += 8)
        {
            for (col = 1; col < sizeX; col++)
            {
                if (col == 1)
                    word[row][col] = So;
                else if (col == 2)
                    word[row][col] = WN;
                else if ((col > 2 && (col - 2) % 5 == 0))
                    if (word[row - 1][col] == No)
                        word[row][col] = WN;
                    else
                        word[row][col] = WS;
                else if (col == (sizeX - 1))
                    word[row][col] = WN;
                else
                    word[row][col] = We;
            }
        }
        for (row = 6; row < (sizeY - 5); row += 8)
        {
            for (col = 1; col < sizeX; col++)
            {
                if (col == 1)
                    word[row][col] = ES;
                else if (col == 2)
                    word[row][col] = EN;
                else if ((col > 2 && (col - 2) % 5 == 0))
                    if (word[row - 1][col] == No)
                        word[row][col] = EN;
                    else
                        word[row][col] = ES;
                else if (col == (sizeX - 1))
                    word[row][col] = No;
                else
                    word[row][col] = Ea;
            }
        }
    }
    /* CAN PRINT THE ARRAY TO SEE STREET DIRECTIONS FOR TROUBLESHOOTING
    for (row = 0; row < sizeY; row++) {
        for (col = 0; col < sizeX; col++) {
            printf("%c", word[row][col]);
        }
        printf("\n");
    }*/
    /* NEED TO FIGURE OUT WHERE TO PUT THIS
    for (int i = 0; i < sizeY; i++) {
        free(word[i]);
    }
    free(word);
    */
}