# suckless_chess_v1
A simple raylib chess board

# Features
You can read FEN notation into the board
./chess --fen "r5q1/pp1b1kr1/2p2p2/2Q5/2PpB3/1P4NP/P4P2/4RK2 w - - 1 0"
Will produce
![Image of fen above rendered](https://github.com/sherllyneo/suckless_chess_v1/blob/main/readme_images/fen.png?raw=true)


./chess will show board from starting position


Many key bindings to spawn pieces, clear the board, or more.


Displays FEN of current position on screen at all times - 

# Key bindings
f - flips board to black or white

space - toggles between showing pieces or square names

left shift + f will save current fen to $HOME/.local/share/chess/fen.txt


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

