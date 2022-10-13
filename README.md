# My_octave

This is an university project in which i practiced how a pointer and memory
allocation works, creating a program "similar to" Octave. It basically does
a few matrix operation like multiplying, transposition, resizing, sorting based
on fixed criteria, loading or deleting a matrix in the memory. So, i am using a
triple pointer which is a matrix array.

**Load**
-> loads in the memory a new matrix, at the end of the matrix array
Usage:
L 2 3
8 9 9
1 4 5
(loads a matrix with 2 rows and 3 columns)

**Dimensions**
-> prints the dimensions of a matrix with a given index
Usage:
D 0

**Print_matrix**
-> prints the elements of a matrix with a given index
Usage:
P 0

**Resize**
-> resizing a matrix using the next parameters:
    - the matrix index
    - the number of the lines and the indices of the lines that i want to keep
    - the number of the columns and the indices of the columns that i want to keep
Usage:
R 0
1 1
2 0 2
(from 8 9 9 / 1 4 5, the matrix will become 1 5 -> keeping the elements from [1][0] and [1][2])

**Multiply**
-> creating a new matrix that is the result of multiplying two matrices with the given indices
Usage:
M 0 1

**Sort**
-> sorting the matrices array by a value that is the sum of the elements % MOD
-> it does not require any arguments
Usage:
O

**Transposition**
-> modifying a given index matrix with its transposed
Usage:
T 0

**Deleting matrix**
-> deleting a given index matrix from the array
Usage:
F 0

**Quit**
-> exits the program, freeing all the resources used
Usage:
Q
