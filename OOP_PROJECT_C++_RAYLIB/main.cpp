#include <raylib.h>
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
using namespace std;

const int screenWidth = 705;
const int screenHeight = 705;

const int boardSize = 15; // 15x15 grid for the Ludo board
const int cellSize = screenHeight / boardSize;

// sound effect
Sound optionSelection;
Sound diceRoll;
Sound gameSound;
// fonts
Font customFont;
Font custom;
Font custom2;
void loadAssests()
{
    // option selction sound
    optionSelection = LoadSound("option.mp3");
    // game sound
    gameSound = LoadSound("op.mp3");
    // dice sound
    diceRoll = LoadSound("dice.mp3");

    // custom font
    customFont = LoadFont("my.ttf");
    custom = LoadFont("my2.ttf");
    custom2 = LoadFont("c.ttf");
}
void unloadAssests()
{
    UnloadSound(optionSelection);
    UnloadSound(gameSound);
    UnloadSound(diceRoll);
    UnloadFont(customFont);
    UnloadFont(custom);
    UnloadFont(custom2);
}

const int path[4][56][2] = {
    {{1, 6}, {2, 6}, {3, 6}, {4, 6}, {5, 6}, {6, 5}, {6, 4}, {6, 3}, {6, 2}, {6, 1}, {6, 0}, {7, 0}, {8, 0}, {8, 1}, {8, 2}, {8, 3}, {8, 4}, {8, 5}, {9, 6}, {10, 6}, {11, 6}, {12, 6}, {13, 6}, {14, 6}, {14, 7}, {14, 8}, {13, 8}, {12, 8}, {11, 8}, {10, 8}, {9, 8}, {8, 9}, {8, 10}, {8, 11}, {8, 12}, {8, 13}, {8, 14}, {7, 14}, {6, 14}, {6, 13}, {6, 12}, {6, 11}, {6, 10}, {6, 9}, {5, 8}, {4, 8}, {3, 8}, {2, 8}, {1, 8}, {0, 8}, {0, 7}, {1, 7}, {2, 7}, {3, 7}, {4, 7}, {5, 7}},
    {{8, 1}, {8, 2}, {8, 3}, {8, 4}, {8, 5}, {9, 6}, {10, 6}, {11, 6}, {12, 6}, {13, 6}, {14, 6}, {14, 7}, {14, 8}, {13, 8}, {12, 8}, {11, 8}, {10, 8}, {9, 8}, {8, 9}, {8, 10}, {8, 11}, {8, 12}, {8, 13}, {8, 14}, {7, 14}, {6, 14}, {6, 13}, {6, 12}, {6, 11}, {6, 10}, {6, 9}, {5, 8}, {4, 8}, {3, 8}, {2, 8}, {1, 8}, {0, 8}, {0, 7}, {0, 6}, {1, 6}, {2, 6}, {3, 6}, {4, 6}, {5, 6}, {6, 5}, {6, 4}, {6, 3}, {6, 2}, {6, 1}, {6, 0}, {7, 0}, {7, 1}, {7, 2}, {7, 3}, {7, 4}, {7, 5}},
    {{13, 8}, {12, 8}, {11, 8}, {10, 8}, {9, 8}, {8, 9}, {8, 10}, {8, 11}, {8, 12}, {8, 13}, {8, 14}, {7, 14}, {6, 14}, {6, 13}, {6, 12}, {6, 11}, {6, 10}, {6, 9}, {5, 8}, {4, 8}, {3, 8}, {2, 8}, {1, 8}, {0, 8}, {0, 7}, {0, 6}, {1, 6}, {2, 6}, {3, 6}, {4, 6}, {5, 6}, {6, 5}, {6, 4}, {6, 3}, {6, 2}, {6, 1}, {6, 0}, {7, 0}, {8, 0}, {8, 1}, {8, 2}, {8, 3}, {8, 4}, {8, 5}, {9, 6}, {10, 6}, {11, 6}, {12, 6}, {13, 6}, {14, 6}, {14, 7}, {13, 7}, {12, 7}, {11, 7}, {10, 7}, {9, 7}},
    {{6, 13}, {6, 12}, {6, 11}, {6, 10}, {6, 9}, {5, 8}, {4, 8}, {3, 8}, {2, 8}, {1, 8}, {0, 8}, {0, 7}, {0, 6}, {1, 6}, {2, 6}, {3, 6}, {4, 6}, {5, 6}, {6, 5}, {6, 4}, {6, 3}, {6, 2}, {6, 1}, {6, 0}, {7, 0}, {8, 0}, {8, 1}, {8, 2}, {8, 3}, {8, 4}, {8, 5}, {9, 6}, {10, 6}, {11, 6}, {12, 6}, {13, 6}, {14, 6}, {14, 7}, {14, 8}, {13, 8}, {12, 8}, {11, 8}, {10, 8}, {9, 8}, {8, 9}, {8, 10}, {8, 11}, {8, 12}, {8, 13}, {8, 14}, {7, 14}, {7, 13}, {7, 12}, {7, 11}, {7, 10}, {7, 9}}};
const int notOpen[4][4][2] = {
    {{2, 2}, {3, 2}, {2, 3}, {3, 3}},
    {{11, 2}, {12, 2}, {11, 3}, {12, 3}},
    {{11, 11}, {12, 11}, {11, 12}, {12, 12}},
    {{2, 11}, {3, 11}, {2, 12}, {3, 12}}};

class Ludo;

class Player
{
private:
    bool won;          // variable true when player won the game
    int pos[4];        // for storing position of its 4 pieces
    int home;          // to count pieces that went home
    int notOpenPieces; // to count total pieces that dont open yet
    int winPosition;   // in which position player won i.e 1st 2nd
    static int win;    // to get win position
public:
    friend class Ludo; // as its data members are frequently access by Ludo class we made it friend
    // default constructor
    Player()
    {
        won = false;
        for (int i = 0; i < 4; i++)
        {
            pos[i] = -1;
        }
        home = 0;
        notOpenPieces = 4;
        winPosition = 0;
    }
    // copy Constructor
    Player(const Player &other)
    {
        won = other.won;
        for (int i = 0; i < 4; i++)
        {
            this->pos[i] = other.pos[i];
        }
        home = other.home;
        notOpenPieces = other.notOpenPieces;
    }

    // getter
    int getpos(int i) const
    {
        int x = pos[i];
        return x;
    }
    int getWinPos() const
    {
        return winPosition;
    }
    int getNotOpen() const
    {
        return notOpenPieces;
    }
    int getHome() const
    {
        return home;
    }
    bool getWon() const
    {
        return won;
    }
    void setpos(int i, int value)
    {
        pos[i] = value;
    }

    void addNotOpen(int value) // increament if  piece get capture and decrement when piece open
    {
        notOpenPieces += value;
    }

    void addHome() // increament whne piece get home
    {
        home += 1;
        if (home == 4) // when all 4 pieces get home player won
        {
            won = true;
            winPosition = win;
            win++; // increament in position for next player who won
        }
    }
};
int Player::win = 1; // initializing int
class Interface;     // class that help Ludo and User to interact
class Move;          // class that change position of player pieces
class Ludo
{
private:
    Player *ptr;       // ptr point at the aray for total playing players
    int turn;          // to account whose turn it iz
    int players;       // total players playing
    vector<int> score; // to store points of a player on its tunr

    // as its data members are frequently access by these 2 class2s  we made them friend
    friend class Interface;
    friend class Move;

public:
    // constructor
    Ludo(int p)
    {
        players = p;
        turn = 0;
        ptr = new Player[p];
    };
    // destructor
    ~Ludo()
    {
        if (ptr != nullptr)
        {
            delete[] ptr;
            ptr = nullptr;
        }
    };
    // setter
    void setscore(int s)
    {
        score.push_back(s);
        if (s == 6 && score.size() == 3) // when player get 3 sixes
        {
            score.clear();
        }
    }
    void changeTurn()
    {
        turn++;
        if (turn == players)
        {
            turn = 0;
        }
    }
    void setPlayerPosition(int i, int j, int p)
    {
        ptr[i].pos[j] = p;
        if (p == 56)
        {
            ptr[i].addHome();
        }
    }
    // getter

    int getPlayers() const
    {
        return players;
    }
    int getPlayersPlaying() const
    {
        int count = 0;
        for (int i = 0; i < players; i++)
        {
            if (!ptr[i].won)
            {
                count++;
            }
        }
        return count;
    }
    int getTurn() const
    {
        return turn;
    }
    int getPlayersPosition(int i, int j) const
    {
        return ptr[i].getpos(j);
    }
    Player &getData(int i) const
    {
        return ptr[i];
    }
};
// it will make Ludo and user to interact
class Interface
{
    // crown image
    Texture2D texture;

public:
    Interface()
    {
        texture = LoadTexture("crown.png");
    }
    ~Interface()
    {
        UnloadTexture(texture);
    }

    int rollDice()
    {
        return GetRandomValue(1, 6); // Simulate rolling a standard 6-sided dice
    }

    // fuunction that draw a circle at specefic box on the grid
    void DrawCircleAtPoint(int gridX, int gridY, Color fillColor, int radius = 22)
    {
        // calculating center of circle
        int centerX = gridX * cellSize + cellSize / 2;
        int centerY = gridY * cellSize + cellSize / 2;

        // Draw the filled circle
        DrawCircle(centerX, centerY, radius, fillColor);

        // Draw the circle outline
        for (int i = 0; i < 2; i++)
        {
            DrawCircleLines(centerX, centerY, radius + i, WHITE);
        }
    }

    // function that draw ludo board
    void DrawLudoBoard(Ludo &a)
    {

        Color colors[] = {RED, GREEN, BLUE, YELLOW};

        // Drawing save squares
        //// RED
        DrawRectangle(1 * cellSize, 6 * cellSize, 1 * cellSize, 1 * cellSize, colors[0]);
        for (int i = 1; i <= 5; i++)
        {
            int startX = i * cellSize;
            int startY = 7 * cellSize;
            DrawRectangle(startX, startY, 1 * cellSize, 1 * cellSize, colors[0]);
        }
        DrawRectangle(2 * cellSize, 8 * cellSize, 1 * cellSize, 1 * cellSize, colors[0]);

        // Green
        DrawRectangle(8 * cellSize, 1 * cellSize, 1 * cellSize, 1 * cellSize, colors[1]);
        for (int i = 1; i <= 5; i++)
        {
            int startX = 7 * cellSize;
            int startY = i * cellSize;
            DrawRectangle(startX, startY, 1 * cellSize, 1 * cellSize, colors[1]);
        }
        DrawRectangle(6 * cellSize, 2 * cellSize, 1 * cellSize, 1 * cellSize, colors[1]);
        // Blue
        DrawRectangle(12 * cellSize, 6 * cellSize, 1 * cellSize, 1 * cellSize, colors[2]);
        for (int i = 9; i < 14; i++)
        {
            int startX = i * cellSize;
            int startY = 7 * cellSize;
            DrawRectangle(startX, startY, 1 * cellSize, 1 * cellSize, colors[2]);
        }
        DrawRectangle(13 * cellSize, 8 * cellSize, 1 * cellSize, 1 * cellSize, colors[2]);

        // Yellow
        DrawRectangle(6 * cellSize, 13 * cellSize, 1 * cellSize, 1 * cellSize, colors[3]);
        for (int i = 9; i <= 13; i++)
        {
            int startX = 7 * cellSize;
            int startY = i * cellSize;
            DrawRectangle(startX, startY, 1 * cellSize, 1 * cellSize, colors[3]);
        }
        DrawRectangle(8 * cellSize, 12 * cellSize, 1 * cellSize, 1 * cellSize, colors[3]);

        // Draw the grid for black outline
        for (int i = 0; i <= boardSize; i++)
        {
            DrawLine(i * cellSize, 0, i * cellSize, screenHeight, BLACK);
            DrawLine(0, i * cellSize, screenWidth, i * cellSize, BLACK);
        }

        // Draw the home areas
        Color c[] = {RED, GREEN, YELLOW, BLUE};
        for (int i = 0; i < 4; i++)
        {
            int startX = (i % 2 == 0) ? 0 : 9 * cellSize;
            int startY = (i < 2) ? 0 : 9 * cellSize;
            DrawRectangle(startX, startY, 6 * cellSize, 6 * cellSize, c[i]);
        }

        // home area inner boxe
        DrawRectangle(1 * cellSize, 1 * cellSize, 4 * cellSize, 4 * cellSize, WHITE);
        DrawRectangle(10 * cellSize, 1 * cellSize, 4 * cellSize, 4 * cellSize, WHITE);
        DrawRectangle(1 * cellSize, 10 * cellSize, 4 * cellSize, 4 * cellSize, WHITE);
        DrawRectangle(10 * cellSize, 10 * cellSize, 4 * cellSize, 4 * cellSize, WHITE);

        // drwaing pieces which are not open
        for (int i = 0; i < a.getPlayers(); i++)
        {
            for (int j = 0; j < a.getData(i).getNotOpen(); j++)
            {
                int posX = notOpen[i][j][0], posY = notOpen[i][j][1];
                DrawCircleAtPoint(posX, posY, colors[i]);
            }
        }

        // it will display a crown and won position which have won
        for (int i = 0; i < a.getPlayers(); i++)
        {

            float startX = ((i < 1 && i>2) ? 1 : 10) * cellSize;
            float startY = ((i < 2) ? 1 : 10) * cellSize;
            if (a.getData(i).getWon())
            {
                int n = a.getData(i).getWinPos();
                string w = "WON  POSITION " + to_string(n);
                DrawTextEx(custom, w.c_str(), (Vector2){startX, startY + 20}, 30, 1, WHITE);
                DrawTexture(texture, startX + 1, startY + cellSize, WHITE);
            }
        }

        // drawing pieces which are open
        for (int i = 0; i < a.getPlayers(); i++)
        {
            for (int j = 0; j < 4; j++)
            {

                int pos = a.getPlayersPosition(i, j);
                if (pos != -1 && pos < 56)
                {
                    DrawCircleAtPoint(path[i][pos][0], path[i][pos][1], colors[i]);
                }
            }
        }

        // creating 4 triangles at center which is home
        Vector2 vertex1 = {6 * cellSize, 6 * cellSize};
        Vector2 vertex2 = {6 * cellSize, 9 * cellSize};
        Vector2 vertex3 = {9 * cellSize, 9 * cellSize};
        Vector2 vertex4 = {9 * cellSize, 6 * cellSize};
        Vector2 vertex5 = {352.5, 352.5};
        DrawTriangle(vertex1, vertex2, vertex5, RED);
        DrawTriangle(vertex2, vertex3, vertex5, YELLOW);
        DrawTriangle(vertex3, vertex4, vertex5, BLUE);
        DrawTriangle(vertex4, vertex1, vertex5, GREEN);

        // side user prompting screen
        DrawRectangle(15 * cellSize, 0 * cellSize, 200, 15 * cellSize, BLACK);
        turn(a);
    }
    // diplay promting screen
    void turn(Ludo &a)
    {
        int i = a.turn;
        Color colors[] = {RED, GREEN, BLUE, YELLOW};
        string TurnString = "Player " + to_string(i + 1) + " Turn";
        DrawTextEx(custom2, TurnString.c_str(), (Vector2){15.2 * cellSize, .7 * cellSize}, 20, 1, colors[i]);
        DrawTextEx(custom2, "Press dice to role it", (Vector2){15.3 * cellSize, 1.4 * cellSize}, 20, 1, WHITE);

        // displaying score
        if (a.score.size() != 0)
        {
            string scoreString = "->";
            for (size_t i = 0; i < a.score.size(); i++)
            {
                scoreString += to_string(a.score[i]) + " ";
            }

            DrawTextEx(custom2, "Your Score:", (Vector2){15.3 * cellSize, 2.1 * cellSize}, 20, 1, colors[i]);
            DrawTextEx(custom2, scoreString.c_str(), (Vector2){15.3 * cellSize, 2.8 * cellSize}, 25, 1, colors[i]);
        }
    }

    // draw dice at the middle of board
    void DrawDice(int number)
    {
        Color diceColor = RAYWHITE;
        Color dotColor = BLACK;

        DrawRectangle(7 * cellSize, 7 * cellSize, cellSize, cellSize, diceColor);

        // Calculate dot positions based on dice size
        float dotSize = cellSize / 8.0;
        float offset = cellSize / 3.0;

        if (number == 1 || number == 3 || number == 5) // if player role these dot at center one should be display
        {
            DrawCircle(7 * cellSize + cellSize / 2, 7 * cellSize + cellSize / 2, dotSize, dotColor);
        }
        if (number >= 2) // if user role more than two diagnol dot be displayed as well
        {
            DrawCircle(7 * cellSize + offset, 7 * cellSize + offset, dotSize, dotColor);
            DrawCircle(7 * cellSize + cellSize - offset, 7 * cellSize + cellSize - offset, dotSize, dotColor);
        }
        if (number >= 4) // if user role more than 3 than other diagnol dots should also be dislayed
        {
            DrawCircle(7 * cellSize + offset, 7 * cellSize + cellSize - offset, dotSize, dotColor);
            DrawCircle(7 * cellSize + cellSize - offset, 7 * cellSize + offset, dotSize, dotColor);
        }
        if (number == 6) // if user role six the middle adjacent dot should be dislayed
        {
            DrawCircle(7 * cellSize + offset, 7 * cellSize + cellSize / 2, dotSize, dotColor);
            DrawCircle(7 * cellSize + cellSize - offset, 7 * cellSize + cellSize / 2, dotSize, dotColor);
        }
    }
};

// it will get user input and make chnages in players pieces position of class Ludo
class Move
{
public:
    // function that will open a piece
    void open(Ludo &game)
    {
        for (size_t i = 0; i < 4; i++)
        {
            int pos = game.getPlayersPosition(game.turn, i);
            if (pos == -1) // if piee is not open open it
            {
                game.setPlayerPosition(game.turn, i, 0);
                game.ptr[game.turn].addNotOpen(-1); // decreament in total not open pieces
                break;
            }
        }
        game.score.erase(game.score.begin()); // ersasing 6 from score points
    }

    // function that will check if there is an oppent piece at new position and capture it
    void checkCapture(Ludo &game, int newPos)
    {
        // player new position x and y
        int X = path[game.turn][newPos][0], Y = path[game.turn][newPos][1];
        // for storing oppents x and y
        int opponentX, opponentY;

        for (int i = 0; i < game.players; i++)
        {
            // if pieces of oppenent are not open and if it is cuurent player continue
            if (i == game.turn || game.ptr[i].getNotOpen() + game.ptr[i].getHome() == 4)
            {
                continue;
            }
            for (int j = 0; j < 4; j++)
            {
                int opponentPos = game.getPlayersPosition(i, j);
                if (opponentPos > -1 && opponentPos < 56)
                {
                    opponentX = path[i][opponentPos][0];
                    opponentY = path[i][opponentPos][1];
                }
                // if oppent x and y match with player capture the piece
                if (X == opponentX && Y == opponentY)
                {
                    game.setPlayerPosition(i, j, -1); // opponent piece back to home
                    game.ptr[i].addNotOpen(1);        // increament in not open home pieces
                    opponentX = -1;
                    opponentY = -1;
                }
            }
        }
    }
    // this will take user input via mouse and invoke the move he want to play
    bool checkmove(Ludo &game)
    {
        // if there is not a six and all of the pieces is not open change the turn to next
        if (game.score.size() == 1 && game.ptr[game.turn].getNotOpen() + game.ptr[game.turn].getHome() == 4)
        {
            game.changeTurn();
            // game.turn++;
            // if (game.turn == game.players)
            // {
            //     game.turn = 0;
            // }
            game.score.clear();
            return true;
        } // if there is one six open a piece automatically
        else if (game.score.size() >= 2 && game.ptr[game.turn].getNotOpen() == 4)
        {
            this->open(game);
        } // if there is only one piece left it will move automatically
        else if (game.ptr[game.turn].getHome() == 3)
        {
            int totalPoints = 0; // for storing total score
            for (size_t i = 0; i < game.score.size(); i++)
            {
                totalPoints += game.score[i];
            }
            for (size_t j = 0; j < 4; j++)
            {
                int pos = game.getPlayersPosition(game.turn, j);
                if (pos != -1 && pos != 58 && pos + totalPoints <= 56) // if total points can be move
                {
                    game.setPlayerPosition(game.turn, j, pos + totalPoints);
                    int newpos = game.getPlayersPosition(game.turn, j);
                    // if new position is not a save square look for captures
                    if (newpos != 8 && newpos != 0 && newpos != 13 && newpos != 21 && newpos != 26 && newpos != 34 && newpos != 39 && newpos != 47 && newpos < 51)
                    {
                        checkCapture(game, newpos);
                    }
                    break;
                }
            }
            game.score.clear();
        } // if there is only one pice out it will move autonatically
        else if (game.score.size() == 1 && game.ptr[game.turn].getNotOpen() + game.ptr[game.turn].getHome() == 3 && game.score[0] != 6)
        {
            for (size_t j = 0; j < 4; j++)
            {
                int pos = game.getPlayersPosition(game.turn, j);
                if (pos != -1 && pos != 56 && pos + game.score[0] <= 56)
                {

                    game.setPlayerPosition(game.turn, j, pos + game.score[0]);
                    int newpos = game.getPlayersPosition(game.turn, j);
                    // if new position is not a save square look for captures
                    if (newpos != 8 && newpos != 0 && newpos != 13 && newpos != 21 && newpos != 26 && newpos != 34 && newpos != 39 && newpos != 47 && newpos < 51)
                    {
                        checkCapture(game, newpos);
                    }
                    break;
                }
            }
            game.score.clear();
        } // Now this will take input which piece he want to move and how many points
        else if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {

            Vector2 mousePos = GetMousePosition(); // getting mouse position
            // check if user promt to open a piece and he has a six
            if (CheckCollisionPointRec(mousePos, {static_cast<float>(notOpen[game.turn][0][0] * cellSize),
                                                  static_cast<float>(notOpen[game.turn][0][1] * cellSize),
                                                  static_cast<float>(2 * cellSize),
                                                  static_cast<float>(2 * cellSize)}) &&
                game.score[0] == 6 && game.ptr[game.turn].getNotOpen() != 0)
            {
                this->open(game); // open the piece
            }
            else
            { // for storing point user want to move and its index in score vector
                static int points = 0;
                static int index = -1;
                // if it is first in score vector
                if (CheckCollisionPointRec(mousePos, {15.3f * cellSize, 2.8f * cellSize, 25, 25.0f}))
                {
                    points = game.score[0];
                    cout << points << endl;
                    index = 0;
                } // if it is second in score vector
                else if (CheckCollisionPointRec(mousePos, {15.3f * cellSize + 26.0, 2.8f * cellSize, 25, 25.0f}) && game.score.size() == 2)
                {
                    points = game.score[1];
                    cout << points << endl;
                    index = 1;
                } // if it is third in score vector
                else if (CheckCollisionPointRec(mousePos, {15.3f * cellSize + 2 * 26.0, 2.8f * cellSize, 25, 25.0f}) && game.score.size() == 3)
                {
                    points = game.score[2];
                    cout << points << endl;
                    index = 2;
                }
                // if there is only one point in score or user selected the point
                if (points > 0 || game.score.size() == 1)
                {
                    // if there is only one pints in score vector
                    if (game.score.size() == 1 && points == 0)
                    {
                        points = game.score[0];
                        index = 0;
                    }
                    for (int i = 0; i < 56 && points; i++)
                    {
                        // check if user press on its any of pieces path
                        if (CheckCollisionPointRec(mousePos, {static_cast<float>(path[game.turn][i][0] * cellSize), static_cast<float>(path[game.turn][i][1] * cellSize), 1 * cellSize, 1 * cellSize}))
                        {
                            for (size_t j = 0; j < 4 && points; j++)
                            {
                                // if there is a piece on that bloack
                                int pos = game.getPlayersPosition(game.turn, j);
                                if (pos == i && pos + points <= 56)
                                {
                                    // chaning the position
                                    game.setPlayerPosition(game.turn, j, pos + points);
                                    int newpos = game.getPlayersPosition(game.turn, j);
                                    // look for capture
                                    if (newpos != 8 && newpos != 0 && newpos != 13 && newpos != 21 && newpos != 26 && newpos != 34 && newpos != 39 && newpos != 47 && newpos < 51)
                                    {
                                        checkCapture(game, newpos);
                                    }
                                    points = 0;
                                    // erasiing the point we moved
                                    game.score.erase(game.score.begin() + index);
                                    index = -1;
                                }
                            }
                        }
                    }
                }
            }
        }
        bool canPlay = false;
        for (size_t i = 0; i < game.score.size() && !canPlay; i++)
        {

            for (int k = 0; k < 4 && !canPlay; i++)
            {
                if (game.ptr[game.turn].getpos(k) > -1 && game.ptr[game.turn].getpos(k) + game.score[i] <= 56)
                {
                    canPlay = true;
                }
            }
        }
        if (!canPlay)
        {
            game.score.clear();
        }

        if (game.score.size() == 0)
        {
            game.changeTurn();
            return true;
        }
        else
            return false;
    }
};

// this will get input from user how manby players want to play
int selectPlayers()
{
    int option = -1;

    // game logo
    Texture2D logo = LoadTexture("open.png");

    while (option == -1 && !WindowShouldClose())
    {

        ClearBackground(BLACK);
        Vector2 position = {280.5, 60};
        // displaying header
        DrawTextEx(customFont, "LUDO GAME ", position, 50, 2, RED);
        DrawTexture(logo, 500, 10, WHITE);
        position = {370, 120};
        DrawTextEx(customFont, "Welocome", position, 30, 1, GREEN);
        // diplaying option
        DrawTextEx(custom, "Select number of players: ", (Vector2){100, 160}, 30, 1, BLUE);
        DrawTextEx(custom, "->2 Players", (Vector2){100, 200}, 30, 1, WHITE);
        DrawTextEx(custom, "->3 Players", (Vector2){100, 240}, 30, 1, WHITE);
        DrawTextEx(custom, "->4 Players", (Vector2){100, 280}, 30, 1, WHITE);

        // chechking for user input and making option according to it
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            Vector2 mouse = GetMousePosition();
            if (CheckCollisionPointRec(mouse, {100, 200, 200, 30}))
            {
                PlaySound(optionSelection);
                option = 2;
            }
            else if (CheckCollisionPointRec(mouse, {100, 240, 200, 30}))
            {
                PlaySound(optionSelection);
                option = 3;
            }
            else if (CheckCollisionPointRec(mouse, {100, 280, 200, 30}))
            {
                PlaySound(optionSelection);
                option = 4;
            }
        }

        EndDrawing();
    }

    UnloadTexture(logo);
    // return the option selected
    return option;
}
// this will display game over screen and adn ask if he want to play again
bool gameOver(Ludo &game)
{
    int option = -1;
    // logo
    Texture2D logo = LoadTexture("op.png");

    while (option == -1 && !WindowShouldClose())
    {
        ClearBackground(BLACK);
        Vector2 position = {280.5, 60};
        DrawTextEx(customFont, "GAME OVER ", position, 50, 2, RED);
        DrawTexture(logo, 500, 10, WHITE);

        Color colors[] = {RED, GREEN, BLUE, YELLOW};
        string winPositions = "->";
        int i = 0;
        // displaing players positions
        for (i = 0; i < game.getPlayers(); i++)
        {
            if (game.getData(i).getWon())
            {
                winPositions += "Player " + to_string(i + 1) + " Postion " + to_string(game.getData(i).getWinPos());
            }
            else
            {
                winPositions += "Player " + to_string(i + 1) + " Lost";
            }

            DrawTextEx(custom, winPositions.c_str(), (Vector2){100, static_cast<float>(40 * (int)(i + 4))}, 30, 1, colors[i]);
            winPositions = "->";
        }

        // Displaying options
        DrawTextEx(custom, "Want to Play Again", (Vector2){100, static_cast<float>(160 + (i * 40))}, 30, 1, BLUE);
        DrawTextEx(custom, "->YES", (Vector2){100, static_cast<float>(200 + (i * 40))}, 30, 1, WHITE);
        DrawTextEx(custom, "->NO", (Vector2){100, static_cast<float>(240 + (i * 40))}, 30, 1, WHITE);

        // chechking for input
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            Vector2 mouse = GetMousePosition();
            if (CheckCollisionPointRec(mouse, {100, static_cast<float>(200 + (i * 40)), 160, 30}))
            {
                PlaySound(optionSelection);
                option = 1;
            }
            else if (CheckCollisionPointRec(mouse, {100, static_cast<float>(240 + (i * 40)), 160, 30}))
            {
                PlaySound(optionSelection);
                option = 2;
            }
        }

        EndDrawing();
    }
    UnloadTexture(logo);
    // returning the option selcted
    if (option == 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int main()
{
    bool continuePlay = true;
    // openig a window for game
    InitWindow(screenWidth + 200, screenHeight, "Simple Ludo Board");
    // setting audio device
    InitAudioDevice();
    // settinf rame per second
    SetTargetFPS(60);
    
    //load font and sounds
    loadAssests();

    PlaySound(gameSound);

    while (continuePlay && !WindowShouldClose())
    {
        // getting how many players are there
        int players = selectPlayers();
        // creating game
        Ludo game(players);
        Interface UI;
        Move done;
        int score = 1;
        bool turn = true;

        while (!WindowShouldClose())
        {
            if (!IsSoundPlaying(gameSound))
            {
                PlaySound(gameSound); // Replay the sound when it finishes
            }
            BeginDrawing();
            ClearBackground(WHITE);
            // Draw board
            UI.DrawLudoBoard(game);
            // Draw dice
            UI.DrawDice(score);

            // checking for input for rolling the dice
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && turn)
            {
                Vector2 mousePos = GetMousePosition();
                if (CheckCollisionPointRec(mousePos, {7 * cellSize, 7 * cellSize, 1 * cellSize, 1 * cellSize}))
                {
                    PlaySound(diceRoll);
                    score = UI.rollDice();
                    game.setscore(score);
                    // rolling dice turn end snow for the move
                    if (score != 6)
                    {
                        turn = false;
                    }
                }
            }
            // cheking for move
            if (!turn)
            {
                turn = done.checkmove(game);
            }
            // checking if the nex player already won than change to next one
            while (game.getData(game.getTurn()).getWon())
            {
                game.changeTurn();
            }
            EndDrawing();
            // if only one player left end game
            if (game.getPlayersPlaying() == 1)
            {
                break;
            }
        }
        // game over window
        continuePlay = gameOver(game);
    }
    //unload font and sounds
    unloadAssests();
    //close window
    CloseWindow();
    //close audio
    CloseAudioDevice();

    return 0;
}
