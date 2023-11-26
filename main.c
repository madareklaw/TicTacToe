#include "stdio.h"

#define EMPTY ' '
#define X 'X'
#define O 'O'
#define COMPUTER_CHAR O
#define PLAYER_CHAR X

char CheckWinner();
int IsGameFinished();
int MakeMove(char c, int move);
void Print();
void InstructionsPrint();
void ComputerMove(char cpu, char player);
void Reset();

char board[3][3] = {{EMPTY, EMPTY, EMPTY},
                    {EMPTY, EMPTY, EMPTY},
                    {EMPTY, EMPTY, EMPTY}};

int moves[3][3] = {{7, 8, 9},
                   {4, 5, 6},
                   {1, 2, 3}};
void main()
{
    InstructionsPrint();
    int move = 0;
    char winnerId = EMPTY;
    for (;;)
    {
        while (!IsGameFinished())
        {
            int ok = 0;
            do
            {
                printf("Make a move for X ");
                //  ComputerMove(PLAYER_CHAR, COMPUTER_CHAR);
                // ok = 1;
                scanf("%d", &move);
                ok = MakeMove(X, move);
                if (!ok)
                {
                    printf("Invalid Move");
                    char dummy;
                    scanf("%c", &dummy); // eats a character off the buffer
                }
            } while (ok == 0);
            winnerId = CheckWinner();
            Print();
            if (winnerId != EMPTY)
            {
                printf("%c wins!\n", winnerId);
                break;
            }
            if (IsGameFinished())
            {
                break;
            }

            do
            {

                printf("Make a move for O ");

                // scanf("%d", &move);

                ComputerMove(COMPUTER_CHAR, PLAYER_CHAR);
                ok = 1;
                // ok = MakeMove(O, move);
                // if (!ok)
                // {
                //    printf("Invalid Move");
                // }

            } while (ok == 0);
            winnerId = CheckWinner();
            Print();
            if (winnerId != EMPTY)
            {
                printf("%c wins!\n", winnerId);
                break;
            }
        }
        Reset();
        printf("Play again? Y/N");
        char play;
        scanf("%s", &play);
        if (play != 'Y' && play != 'y')
        {
            break;
        }
    }
    printf("\n");
}
/// @brief Clear the board
void Reset()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board[i][j] = EMPTY;
        }
    }
}

/// @brief Checks to see if there is a winner
/// @return Winning char!
char CheckWinner()
{
    // check the rows
    for (int row = 0; row < 3; row++)
    {
        if (board[row][0] == EMPTY)
        {
            // check if row has empty
            continue;
        }

        if (board[row][0] == board[row][1] &&
            board[row][1] == board[row][2])
        {
            // all equal
            return board[row][0];
        }
    }
    // check the columns
    for (int column = 0; column < 3; column++)
    {
        if (board[0][column] == EMPTY)
        {
            // check if column has empty
            continue;
        }
        if (board[0][column] == board[1][column] &&
            board[1][column] == board[2][column])
        {
            // all equal

            return board[0][column];
        }
    }

    // check diagnals
    if (board[0][0] == board[1][1] &&
        board[1][1] == board[2][2])
    {
        // all equal
        if (board[1][1] != EMPTY)
        {
            return board[1][1];
        }
    }

    if (board[0][2] == board[1][1] &&
        board[1][1] == board[2][0])
    {
        // all equal
        if (board[1][1] != EMPTY)
        {
            return board[1][1];
        }
    }

    return EMPTY;
}

/// @brief Checks to see if there are any more moves possible
/// @return 1 no moves possible, 0 moves still possible
int IsGameFinished()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == EMPTY)
            {
                return 0;
            }
        }
    }
    return 1;
}

int MakeMove(char c, int move)
{
    if (move < 1)
    {
        // out of range
        return 0;
    }
    if (move > 9)
    {
        // out of range
        return 0;
    }

    int row = -1;
    int column = -1;

    if (move > 0 && move < 4)
    {
        // Move info
        row = 2;
        column = move - 1;
    }
    else if (move > 3 && move < 7)
    {
        // Move info
        row = 1;
        column = move - 3 - 1;
    }
    else if (move > 6 && move < 10)
    {
        // Move info
        row = 0;
        column = move - 6 - 1;
    }

    if (row != -1 && column != -1)
    {
        if (board[row][column] == EMPTY)
        {
            // only valid if space is empty
            board[row][column] = c;
            return 1;
        }
    }
    return 0;
}

void Print()
{
    system("cls");
    printf("\n");
    printf(" %c | %c | %c ", board[0][0], board[0][1], board[0][2]);
    printf("\n---|---|---\n");
    printf(" %c | %c | %c ", board[1][0], board[1][1], board[1][2]);
    printf("\n---|---|---\n");
    printf(" %c | %c | %c ", board[2][0], board[2][1], board[2][2]);
    printf("\n");
}

void InstructionsPrint()
{
    system("cls");
    printf("Use the numbers below to select where to go!");
    printf("\n");
    printf(" %c | %c | %c ", moves[0][0] + 0x30, moves[0][1] + 0x30, moves[0][2] + 0x30);
    printf("\n---|---|---\n");
    printf(" %c | %c | %c ", moves[1][0] + 0x30, moves[1][1] + 0x30, moves[1][2] + 0x30);
    printf("\n---|---|---\n");
    printf(" %c | %c | %c ", moves[2][0] + 0x30, moves[2][1] + 0x30, moves[2][2] + 0x30);
    printf("\n");
}

void ComputerMove(char cpu, char player)
{
    // check to see if cpu can win
    int move = GetWinMove(cpu);
    if (move > 0)
    {
        MakeMove(cpu, move);
    }
    else
    {
        // check to see if player will win
        move = GetWinMove(player);
        if (move > 0)
        {
            MakeMove(cpu, move);
        }
        else
        {
            // no move will win at the moment... random i guess?
            int random = 0;
            srand(time(NULL));
            do
            {
                random = rand() % 10;
            } while (MakeMove(cpu, random) == 0);
        }
    }
}

int GetWinMove(char c)
{
    // check the rows
    for (int row = 0; row < 3; row++)
    {
        if (board[row][0] == board[row][1] &&
            board[row][2] == EMPTY)
        {
            if (board[row][1] == c)
            {
                return moves[row][2];
            }
        }
        if (board[row][0] == board[row][2] &&
            board[row][1] == EMPTY)
        {
            if (board[row][0] == c)
            {
                return moves[row][1];
            }
        }
        if (board[row][1] == board[row][2] &&
            board[row][0] == EMPTY)
        {
            if (board[row][1] == c)
            {
                return moves[row][0];
            }
        }
    }
    // check the columns
    for (int column = 0; column < 3; column++)
    {
        if (board[0][column] == board[1][column] &&
            board[2][column] == EMPTY)
        {
            if (board[0][column] == c)
            {
                return moves[2][column];
            }
        }
        if (board[0][column] == board[2][column] &&
            board[1][column] == EMPTY)
        {

            if (board[0][column] == c)
            {
                return moves[1][column];
            }
        }
        if (board[1][column] == board[2][column] &&
            board[0][column] == EMPTY)
        {

            if (board[1][column] == c)
            {
                return moves[0][column];
            }
        }
    }

    // check diagnals
    if (board[0][0] == board[1][1] &&
        board[2][2] == EMPTY)
    {
        if (board[1][1] == c)
        {
            return moves[2][2];
        }
    }

    if (board[0][0] == board[2][2] &&
        board[1][1] == EMPTY)
    {
        if (board[2][2] == c)
        {
            return moves[1][1];
        }
    }

    if (board[1][1] == board[2][2] &&
        board[0][0] == EMPTY)
    {
        if (board[1][1] == c)
        {
            return moves[0][0];
        }
    }
    if (board[0][2] == board[1][1] &&
        board[2][0] == EMPTY)
    {
        if (board[1][1] == c)
        {
            return moves[2][0];
        }
    }

    if (board[0][2] == board[2][0] &&
        board[1][1] == EMPTY)
    {
        if (board[2][0] == c)
        {
            return moves[1][1];
        }
    }

    if (board[1][1] == board[2][0] &&
        board[0][2] == EMPTY)
    {
        if (board[1][1] == c)
        {
            return moves[0][2];
        }
    }

    // check for corners
    if (board[0][0] == board[2][2])
    {
        if (board[0][0] == c)
        {
            // check between these is empty

            if (board[0][1] == EMPTY &&
                board[0][2] == EMPTY &&
                board[1][2] == EMPTY)
            {
                return moves[0][2];
            }
            if (board[1][0] == EMPTY &&
                board[2][0] == EMPTY &&
                board[2][1] == EMPTY)
            {
                return moves[2][0];
            }
        }
    }

    if (board[0][2] == board[2][0])
    {
        if (board[0][2] == c)
        {
            // check between these is empty

            if (board[0][1] == EMPTY &&
                board[0][0] == EMPTY &&
                board[1][0] == EMPTY)
            {
                return moves[0][2];
            }
            if (board[1][2] == EMPTY &&
                board[2][2] == EMPTY &&
                board[2][1] == EMPTY)
            {
                return moves[2][2];
            }
        }
    }

    // see if we can take a corner

    if (board[0][0] == board[2][0])
    {
        if (board[0][0] == c)
        {
            // check between these is empty

            if (board[1][1] == EMPTY &&
                board[2][1] == EMPTY &&
                board[2][2] == EMPTY)
            {
                return moves[2][2];
            }
            if (board[1][1] == EMPTY &&
                board[1][2] == EMPTY &&
                board[0][2] == EMPTY)
            {
                return moves[0][2];
            }
        }
    }
    if (board[0][0] == board[0][2])
    {
        if (board[0][0] == c)
        {
            // check between these is empty

            if (board[1][1] == EMPTY &&
                board[2][0] == EMPTY &&
                board[1][0] == EMPTY)
            {
                return moves[2][0];
            }
            if (board[1][1] == EMPTY &&
                board[2][2] == EMPTY &&
                board[1][2] == EMPTY)
            {
                return moves[2][2];
            }
        }
    }
    if (board[0][2] == board[2][2])
    {
        if (board[0][2] == c)
        {
            // check between these is empty

            if (board[1][1] == EMPTY &&
                board[2][0] == EMPTY &&
                board[2][1] == EMPTY)
            {
                return moves[2][0];
            }
            if (board[1][1] == EMPTY &&
                board[0][0] == EMPTY &&
                board[0][1] == EMPTY)
            {
                return moves[0][0];
            }
        }
    }
    if (board[2][2] == board[2][0])
    {
        if (board[0][0] == c)
        {
            // check between these is empty

            if (board[1][1] == EMPTY &&
                board[0][0] == EMPTY &&
                board[1][0] == EMPTY)
            {
                return moves[0][0];
            }
            if (board[1][1] == EMPTY &&
                board[0][2] == EMPTY &&
                board[1][2] == EMPTY)
            {
                return moves[1][2];
            }
        }
    }

    return -1;
}