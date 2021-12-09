#include "Header.h"

void ResetQueen(int i, int j, int n, int** board)
{
	int x = 0;
	int upperDiag = 0;
	int lowerDiag = 0;
	for (x; x < n; x++)
	{
		--board[x][j];
		--board[i][x];
		upperDiag = j - i + x;
		if (upperDiag >= 0 && upperDiag < n)
		{
			--board[x][upperDiag];
		}
		lowerDiag = j + i - x;
		if (lowerDiag >= 0 && lowerDiag < n)
		{
			--board[x][lowerDiag];
		}
	}
	board[i][j] = 0;
}

void SetQueen(int i, int j, int n, int** board)
{
	int x = 0;
	int upperDiag = 0;
	int lowerDiag = 0;
	for (x; x < n; x++)
	{
		++board[x][j];
		++board[i][x];
		upperDiag = j - i + x;
		if (upperDiag >= 0 && upperDiag < n)
		{
			++board[x][upperDiag];
		}
		lowerDiag = j + i - x;
		if (lowerDiag >= 0 && lowerDiag < n)
		{
			++board[x][lowerDiag];
		}
	}
	board[i][j] = -1;
}

bool TryQueen(int i, int n, int** board, int* resultQueens)
{
	bool result = false;
	int j = 0;
	for (j; j < n; j++)
	{
		if (board[i][j] == 0)
		{
			SetQueen(i, j, n, board);
			resultQueens[i] = j;
			if (i == n - 1)
			{
				result = true;
			}
			else
			{
				result = TryQueen(i + 1, n, board, resultQueens);
				if (!result)
				{
					ResetQueen(i, j, n, board);
				}
			}
		}
		if (result)
		{
			break;
		}
	}
	return result;
}

int** CreateBoard(int n)
{
	int i, j;
	int** board = (int**)malloc(n * sizeof(int*));
	if (board == NULL)
	{
		printf("\nERROR\n");
		return NULL;
	}
	for (i = 0; i < n; i++)
	{
		board[i] = (int*)malloc(n * sizeof(int));
	}
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			board[i][j] = 0;
		}
	}
	return board;
}

void DeleteBoard(int** board, int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		free(board[i]);
	}
	free(board);
}

int Reading(const char* inputName)
{
	int size;
	FILE* fp = fopen(inputName, "r");
	if (fp == NULL)
	{
		printf("cant open fileread\n");
		return 0;
	}
	if (fscanf(fp, "%d", &size) != 1)
	{
		perror("ERROR!");
		return 0;
	}
	fclose(fp);
	return size;
}

int Writing(int* resultQueens, int n, const char* outputName)
{
	int i;
	FILE* fp = fopen(outputName, "w");
	if (fp == NULL)
	{
		printf("cant open filewrite\n");
		return 0;
	}
	for (i = 0; i < n; i++)
	{
		fprintf(fp, "%d %d\n", i, resultQueens[i]);
	}
	fclose(fp);
	return 1;
}

int LabSolution(const char* inputName, const char* outputName)
{
	int n = Reading(inputName);
	if (!n)
	{
		printf("\nERROR\n");
		return 0;
	}
	int** board = CreateBoard(n);
	if (!board)
	{
		printf("\nERROR\n");
		return 0;
	}
	int* result = (int*)malloc(n * sizeof(int));
	if (!result)
	{
		printf("\nERROR\n");
		return 0;
	}
	if (TryQueen(0, n, board, result))
	{
		if (!Writing(result, n, outputName))
		{
			return 0;
		}
	}
	else
	{
		return 0;
	}
	DeleteBoard(board, n);
	free(result);
	return 1;
}
