# Tic Tac Toe
As a final project for our SYDE292L Digital Systems Lab, we decided to bring Tic Tac Toe to the Arduino.

A board is printed on both the screen and the Arduino. Each space on the board is assigned a number from 1 to 9, with 1 being the top left corner, 2 being the top center, 3 the top right and so on until 9 on the bottom right. On the player's turn, the player uses the Arduino's Up/Down button to iterate through the numbers and press Select once they have chosen the space where they wish to place their X or O. The Arduino is then passed to the other player. However, if the player takes too long (>10s) to select a number, they lose their turn and their X or O is not placed.

The first player to successfully have 3 in a row wins!