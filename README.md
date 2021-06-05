# Rubric-Cube-Solver-using-A-Algorithm
Puzzle Description
•	The Rubik's Cube is an important test domain for heuristic search that has  1019  possible states, making it impossible to store in memory.
•	A single move on a Rubik's Cube can be defined as a quarter turn (90') of any face either clockwise or anticlockwise.



In this part of the assignment we are going to write a C++ program that will take the initial and final configurations of the cube and will find a sequence of moves that will transform the initial state into the final state. The solutions will be found by using one uninformed search strategy i.e. iterative-deepening and one informed search strategy named A*
For this assignment you must assume that turning a face of the Rubik’s cube by 90o either in clockwise or counter clockwise direction is considered one move each
Your program will take as input a file containing the initial and final configuration pair and will output the set of moves needed to solve the puzzle.
 

File Format
The first line of the file will contains the initial configuration (a space separated list of 54 digit  code of the colors) the second line contains the final configuration.
A complete configuration of a puzzle consists of 54 space separated digits which give the color information on each of the six sides of the cube. A color on each of the nine cubes on a given side   is a digit from the set {1, 2, 3, 4, 5, 6}. The first  9 digits of these 54 digits specifying the colors of the 9 cubes faces on the front side (left-right and top-bottom), the next 9 numbers specifying the color information on the back side and then comes the color information of top, bottom, left and right sides.
