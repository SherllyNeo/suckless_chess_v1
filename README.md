# suckless_chess_v1
A simple raylib chess board

# Features
You can read FEN notation into the board
./chess --fen "r5q1/pp1b1kr1/2p2p2/2Q5/2PpB3/1P4NP/P4P2/4RK2 w - - 1 0"
Will produce
![Image of fen above rendered](https://github.com/sherllyneo/suckless_chess_v1/blob/main/readme_images/fen.png?raw=true)


## ./chess will show board from starting position

![Image of fen above rendered](https://github.com/sherllyneo/suckless_chess_v1/blob/main/readme_images/start.png?raw=true)

## Many key bindings to spawn pieces, clear the board, or more.


## Displays FEN of current position on screen at all times - It will naively check for castling rights, move count and more

Display square names
![Image of fen above rendered](https://github.com/sherllyneo/suckless_chess_v1/blob/main/readme_images/square.png?raw=true)

# Key bindings
f - flips board to black or white

space - toggles between showing pieces or square names

d will dump current fen to $HOME/.local/share/chess/fen.txt

right click deletes a piece

left click picks up / drops a piece

c - sets board to starting position

C - clears board

h - undo

l - redo

To spawn a piece to your hand, press the letter for the piece 
eg:

q spawns a white queen, n spawns a white knight, k spawns a white king

holding left shift will spawn the black pieces

Q spawns a black queen, N spawns a black knight, k spawns a black king


# Install
make
sudo make install

move assets to $HOME/.local/share/chess/assets

# what this isn't 

This is a board editor, not an analysis board. 
It will not show a history of moves in PGN, instead only displaying FEN.
You can move pieces how you like.

This is a simple chess board, not a simple chess engine. Very minimalistic.


