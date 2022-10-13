//Bobaru Valentin-Ionut

#include <stdio.h>
#include <stdlib.h>

#define MOD 10007

// Dynamic allocation for a matrix with n rows and m columns
int **matrix_allocation(int n, int m)
{
	int **mat;
	// Allocating (n + 1) rows because the first line will be used for keeping
	// the dimensions of the matrix
	int **tmp = (int **)malloc((n + 1) * sizeof(int *));
	if (!tmp) {
		fprintf(stderr, "Malloc error!\n");
		return NULL;
	}
	//Dynamic allocation for the 2 ints that will represent the n (rows) and
	// m (columns)
	tmp[0] = (int *)malloc(2 * sizeof(int));
	if (!tmp[0]) {
		fprintf(stderr, "Malloc error\n");
		return NULL;
	}
	tmp[0][0] = n;
	tmp[0][1] = m;
	//Memory allocation for the n * m elements of the matrix (type int)
	for (int i = 1; i <= n; i++) {
		tmp[i] = (int *)malloc(m * sizeof(int));
		if (!tmp[i]) {
			fprintf(stderr, "Malloc error\n");
			return NULL;
			for (int j = 0; j < i; j++)
				free(tmp[i]);
		}
	}
	mat = tmp;
	return mat;
}

int **read_matrix(void)
{
	int **a, n, m;
	scanf("%d%d", &n, &m);
	// Memory allocation for the matrix
	a = matrix_allocation(n, m);
	// Reading the matrix elements from stdin
	for (int i = 1; i <= n; i++)
		for (int j = 0; j < m; j++)
			scanf("%d", &a[i][j]);
	return a;
}

void dimensions(int ***p, int contor)
{
	int x;
	scanf("%d", &x);
	if (x < contor && x >= 0)
		printf("%d %d\n", p[x][0][0], p[x][0][1]);
	else
		printf("No matrix with the given index\n");
}

void print_matrix(int ***mat, int contor)
{
	int x;
	scanf("%d", &x);
	// Printing the elements only if the index of the matrix is a valid one
	if (x < contor && x >= 0) {
		for (int i = 1; i <= mat[x][0][0]; i++) {
			for (int j = 0; j < mat[x][0][1]; j++)
				printf("%d ", mat[x][i][j]);
			printf("\n");
		}
	} else {
		printf("No matrix with the given index\n");
	}
}

int ***resize(int ***p, int contor)
{
	int n, m, x;
	// Reading the matrix index
	scanf("%d", &x);
	// Reading and allocating the memory for the line indices that will be
	// kept after the resizing
	scanf("%d", &n);
	int *l = (int *)malloc(n * sizeof(int));
	for (int i = 0; i < n; i++)
		scanf("%d", &l[i]);
	scanf("%d", &m);
	// Similarly for the columns
	int *c = (int *)malloc(m * sizeof(int));
	for (int i = 0; i < m; i++)
		scanf("%d", &c[i]);
	if (x >= contor || x < 0) {
		printf("No matrix with the given index\n");
		free(l);
		free(c);
	} else {
		// Memory allocation for the new resized matrix
		int **a = matrix_allocation(n, m);
		// and assigning the right elements from the old matrix (the indices
		// for the l and p look strange adn that's because i am using the frist
		// line for keeping the dimensions)
		for (int i = 1; i <= n; i++)
			for (int j = 0; j < m; j++)
				a[i][j] = p[x][l[i - 1] + 1][c[j]];
		// Freeing the memory used by the l and c arrays and the matrix p
		free(l);
		free(c);

		for (int i = 1; i <= p[x][0][0]; i++)
			free(p[x][i]);
		free(p[x][0]);
		free(p[x]);

		// Putting in place the new resized matrix
		p[x] = a;
	}
	return p;
}

int ***multiply(int ***p, int *contor)
{
	int a, b;
	scanf("%d%d", &a, &b);
	if ((a >= *contor || b >= *contor) || (a < 0 || b < 0)) {
		printf("No matrix with the given index\n");
		return p;
	}
	// Multiplying the matrices only if the nr_columns of the first is equal to
	// nr_rows of the second
	
	if (p[a][0][1] != p[b][0][0]) {
		printf("Cannot perform matrix multiplication\n");
		return p;
	}

	// Reallocating memory for another matrix
	p = (int ***)realloc(p, sizeof(int **) * (++*contor));
	int **m = matrix_allocation(p[a][0][0], p[b][0][1]);
	for (int i = 1; i <= p[a][0][0]; i++)
		for (int j = 0; j < p[b][0][1]; j++) {
			int val = 0;
			for (int l = 0; l < p[a][0][1]; l++) {
				int val_a = p[a][i][l] % MOD;
				int val_b = p[b][l + 1][j] % MOD;
				val += (val_a * val_b) % MOD;
			}
			while (val < 0)
				val += MOD;
			m[i][j] = val % MOD;
		}
	p[*contor - 1] = m;
	return p;
}

// this function returns a value that will be used in sorting the matrices
// (this value has a strange forming rule)
int sum_matrix(int **mat)
{
	int sum = 0;
	for (int i = 1; i <= mat[0][0]; i++)
		for (int j = 0; j < mat[0][1]; j++) {
			if (mat[i][j] < 0)
				sum += (MOD + mat[i][j] % MOD) % MOD;
			else
				sum += (mat[i][j] % MOD) % MOD;
			sum %= MOD;
		}
	return sum;
}

int ***sort(int ***p, int contor)
{
	// Using an auxiliary variable for swaping the matrices
	int **aux, i, j;
	for (i = 0; i < contor - 1; i++)
		for (j = i + 1; j < contor; j++)
			if (sum_matrix(p[i]) > sum_matrix(p[j])) {
				aux = p[i];
				p[i] = p[j];
				p[j] = aux;
			}
	return p;
}

int ***transposition(int ***p, int contor)
{
	int x;
	scanf("%d", &x);
	if (x >= contor || x < 0) {
		printf("No matrix with the given index");
		return p;
	}
	// Memory allocation for the new transposed matrix
	int **t = matrix_allocation(p[x][0][1], p[x][0][0]);
	for (int i = 1; i <= t[0][0]; i++)
		for (int j = 0; j < t[0][1]; j++)
			t[i][j] = p[x][j + 1][i - 1];
	// Freeing the memory used by the old one
	for (int i = 1; i <= p[x][0][0]; i++)
		free(p[x][i]);
	free(p[x][0]);
	free(p[x]);
	p[x] = t;
	return p;
}

int ***deleting_a_matrix(int ***p, int *contor)
{
	int x;
	scanf("%d", &x);
	if (x >= *contor || x < 0) {
		printf("No matrix with the given index\n");
		return p;
	}
	// Creating a new triple pointer in which we will store all of the matrices
	// except p[x]
	int ***tmp = (int ***)malloc((*contor - 1) * sizeof(int **));
	for (int i = 1; i <= p[x][0][0]; i++)
		free(p[x][i]);
	free(p[x][0]);
	free(p[x]);
	for (int i = 0; i < x; i++)
		tmp[i] = p[i];
	for (int i = x; i < *contor - 1; i++)
		tmp[i] = p[i + 1];
	// recreating the references between p and the matrices we keep
	for (int i = 0; i < *contor - 1; i++)
		p[i] = tmp[i];
	free(tmp);
	--*contor;
	// If the matrix we deleted was the only one in p, we will free the memory
	// used for p
	if (*contor == 0)
		free(p);
	return p;
}

void free_resources(int ***p, int *contor)
{
	if (*contor > 0) {
		for (int k = 0; k < *contor; k++) {
			for (int i = 1; i <= p[k][0][0]; i++)
				free(p[k][i]);
			free(p[k][0]);
			free(p[k]);
		}
		contor = 0;
		free(p);
	}
}

int main(void)
{
	int ***p, contor = 0;
	char caracter;
	do {
		scanf(" %c", &caracter);
		switch (caracter) {
		case 'L':
			// If we load the first matrix, we will allocate memory for p
			if (contor == 0)
				p = (int ***)malloc(sizeof(int **) * (++contor));
			// Otherwise we reallocate memory for another matrix (int **)
			else
				p = (int ***)realloc(p, sizeof(int **) * (++contor));
			p[contor - 1] = read_matrix();
			break;
		case 'D':
			dimensions(p, contor);
			break;
		case 'P':
			print_matrix(p, contor);
			break;
		case 'C':
			p = resize(p, contor);
			break;
		case 'M':
			p = multiply(p, &contor);
			break;
		case 'O':
			p = sort(p, contor);
			break;
		case 'T':
			p = transposition(p, contor);
			break;
		case 'F':
			p = deleting_a_matrix(p, &contor);
			break;
		case 'Q':
			free_resources(p, &contor);
			break;
		default:
			printf("Unrecognized command\n");
			break;
		}
	} while (caracter != 'Q');
	return 0;
}
