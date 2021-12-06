# TicTacToeMiniMax
This project is something i created for practicing a little bit with c++ and pointers.<br>
I created a bot for the famous game "Tic Tac Toe" using the algorithm "MiniMax".<br>
## How does MiniMax works?
The perfect bot in terms of victory is the one that is able to choose what to do after having calculated every possibilites<br>
MiniMax does this.<br>
So, after have created this really long structure with every possibilities and correlated wins/losses,<br>
we just make the bot choose the perfect action based on wins/losses.<br>
## How does my program works?
Here i'll explain a little bit better how i managed to create since i coded this without looking anything online.<br>
I can subdivide the bot in 2 parts:
1) Create every possibilites
2) Choose the best action based on the data he collected before
### Create every possibilites
It's basically a brute-force.<br>
We start with an empty table and, for every cell we find every possibilites.<br>
We continue like this until someone loose, win or the game end in a tie.<br>
I also added the possibility to save the complete result in a file<br>
The structure of the file is:<br>
- Every row is a possiblity
- Every row contains the following datas: 
1) Id of the father
2) Our id
3) Wins for cross
4) Wins for circle
5) Looses for cross
6) Looses for circle
7) Ties
8) Player 
9) Round 
### Choose the best action
After having the bot ready with every informations, by just giving the table and the player we want to focus it will give us back the best action.<br>
This is subdivided in 2 parts:
1) Finding the right table in the dataset (simple search)
2) For every nodes, check which one is better based on wins/losses