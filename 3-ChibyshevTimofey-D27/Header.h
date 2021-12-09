#ifndef __HEADER_H_
#define __HEADER_H_

#ifdef __cplusplus
extern "C" {
#endif

#pragma warning(disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define _CRT_SECURE_NO_WARNINGS

void ResetQueen(int i, int j, int n, int** board);
void SetQueen(int i, int j, int n, int** board);
bool TryQueen(int i, int n, int** board, int* resultQueens);
int** CreateBoard(int n);
void DeleteBoard(int** board, int n);
int Reading(const char* inputName);
int Writing(int* resultQueens, int n, const char* outputName);
int LabSolution(const char* inputName, const char* outputName);

#ifdef __cplusplus
}
#endif

#endif