# ludo using C++ and raylib

# Technical Functionalities

•	Sound Effects: The game includes various sound effects for actions like option selection, dice rolling, and background game sounds to enhance the gaming experience.
•	Custom Fonts: Different custom fonts are loaded and used to improve the visual appeal and readability of the game.
•	Dice Rolling: The game includes a dice rolling functionality that simulates the rolling of a 6-sided dice.
•	Graphical Interface: The game uses Raylib to render a graphical interface, including drawing the Ludo board, pieces, dice, and other game elements.
•	Player Interaction: The game includes mechanisms for players to interact with the game, such as moving pieces and rolling the dice.
•	Game Logic: The game contains logic for handling player turns, piece movements, capturing opponent pieces, and winning conditions.







# User Manual

# For installation:
Installation of resources: Ensure Raylib is installed on your system. Load the game assets such as sounds and fonts in the specified directory.
Running the Game: Compile and run the game code using a C++ compiler that supports Raylib.
Playing the Game:
Objective: Move all your pieces from the start to the home position before your opponents.
Rolling the Dice: Press the dice button to roll the dice. The number rolled determines how many steps a piece can move.
Moving Pieces: Select a piece to move it according to the dice roll. If a piece lands on an opponent's piece, the opponent's piece is captured and sent back to the start.
Winning the Game: A player wins by moving all four pieces to the home position.
Age Group:
The game is suitable for players aged 6 and above. It is designed to be easy to understand for younger players while still providing strategic depth for older players.



# Scope of the Project
Current Scope:
Multiplayer Gameplay: The game currently supports multiplayer gameplay for up to four players.
Basic Game Mechanics: Includes essential mechanics such as dice rolling, piece movement, capturing, and winning conditions.
Graphical User Interface: The game has a simple yet functional graphical interface for easy interaction and visualization.
Future Enhancements
AI Opponents: Adding computer-controlled opponents for single-player mode.
Online Multiplayer: Implementing online multiplayer capabilities to allow players to compete over the internet.
Enhanced Graphics: Improving the graphical interface with more detailed and dynamic visuals.
Customizable Rules: Allowing players to customize game rules such as the number of pieces and board size.



# Classes & Functions
Classes:
•	Ludo
•	Interface
•	Move
•	Player

# Global functions
•	bool gameOver(Ludo &game)
•	int selectPlayers()
•	void loadAssests()
•	void unloadAssests()




