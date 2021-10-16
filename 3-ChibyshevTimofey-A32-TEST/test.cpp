#include "pch.h"
#include "header.h"

#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>


void MemoryLeaks(void)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
}

TEST(TestCaseName, TestName)
{
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
}

TEST(Creation, Create_TEST)
{
	list_t* tmp = NULL;
	tmp = Create();
	ASSERT_NE(tmp, nullptr);
	EXPECT_EQ(tmp->next, nullptr);
	//free(tmp->next);
	//free(tmp);
}

TEST(END_ELEM, AddElementEnd_TEST)
{
	int k = 0;
	list_t* tmp = NULL;
	tmp = (list_t*)malloc(sizeof(list_t));
	ASSERT_NE(tmp, nullptr);
	tmp->data = 0;
	tmp->next = NULL;
	k = AddElementEnd(-1, tmp);
	ASSERT_NE(tmp, nullptr);
	EXPECT_EQ(tmp->next->data, -1);
	EXPECT_EQ(tmp->next->next, nullptr);
	EXPECT_EQ(k, 1);
	free(tmp->next);
	free(tmp);
}

TEST(DIFFERET_NUMS, ReadNumbers_TEST)
{
	int k = 0;
	int len = 0;
	const char* name = "TESTS\\diffnums.txt";
	list_t* tmp = NULL;
	tmp = (list_t*)malloc(sizeof(list_t));
	ASSERT_NE(tmp, nullptr);
	tmp->next = NULL;
	k = ReadNumbers(name, tmp, &len);
	EXPECT_EQ(k, 1);
	EXPECT_EQ(len, 5);
	EXPECT_EQ(tmp->data, -3);
	EXPECT_EQ(tmp->next->data, -2);
	EXPECT_EQ(tmp->next->next->data, -1);
	EXPECT_EQ(tmp->next->next->next->data, 0);
	EXPECT_EQ(tmp->next->next->next->next->data, 1);
	EXPECT_EQ(tmp->next->next->next->next->next, nullptr);
	free(tmp->next->next->next->next);
	free(tmp->next->next->next);
	free(tmp->next->next);
	free(tmp->next);
	free(tmp);
}

TEST(CLEAR_FILE, ReadNumbers_TEST)
{
	int k = 0;
	int len = 0;
	const char* name = "TESTS\\clear.txt";
	list_t* tmp = NULL;
	tmp = (list_t*)malloc(sizeof(list_t));
	ASSERT_NE(tmp, nullptr);
	tmp->next = NULL;
	k = ReadNumbers(name, tmp, &len);
	EXPECT_EQ(k, 1);
	EXPECT_EQ(len, 0);
	EXPECT_EQ(tmp->next, nullptr);
	free(tmp);
}

TEST(DIFFERENT_NUMS, Merge_TEST)
{
	int k = 0;
	list_t tmp0[3];
	tmp0[0] = { 0, &tmp0[1] };
	tmp0[1] = { 1, &tmp0[2] };
	tmp0[2] = { 4, NULL };
	list_t tmp1[4];
	tmp1[0] = { 2, &tmp1[1] };
	tmp1[1] = { 3, &tmp1[2] };
	tmp1[2] = { 5, &tmp1[3] };
	tmp1[3] = { 6, NULL };
	list_t* t3 = NULL;
    t3 = (list_t*)malloc(sizeof(list_t));
	ASSERT_NE(t3, nullptr);
	t3->next = NULL;
	k = Merge(tmp0, tmp1, t3, 3, 4);
	EXPECT_EQ(k, 2);
	EXPECT_EQ(t3->data, 0);
	EXPECT_EQ(t3->next->data, 1);
	EXPECT_EQ(t3->next->next->data, 2);
	EXPECT_EQ(t3->next->next->next->data, 3);
	EXPECT_EQ(t3->next->next->next->next->data, 4);
	EXPECT_EQ(t3->next->next->next->next->next->data, 5);
	EXPECT_EQ(t3->next->next->next->next->next->next->data, 6);
	EXPECT_EQ(t3->next->next->next->next->next->next->next, nullptr);
	free(t3->next->next->next->next->next->next);
	free(t3->next->next->next->next->next);
	free(t3->next->next->next->next);
	free(t3->next->next->next);
	free(t3->next->next);
	free(t3->next);
	free(t3);
}

TEST(CLEAR_TWO_LISTS, Merge_TEST)
{
	int k = 0;
	list_t* tmp0 = NULL;
	tmp0 = (list_t*)malloc(sizeof(list_t));
	ASSERT_NE(tmp0, nullptr);
	tmp0->next = NULL;
	list_t* tmp1 = NULL;
	tmp1 = (list_t*)malloc(sizeof(list_t));
	ASSERT_NE(tmp1, nullptr);
	tmp1->next = NULL;
	list_t* tmp2 = NULL;
	tmp2 = (list_t*)malloc(sizeof(list_t));
	ASSERT_NE(tmp2, nullptr);
	tmp2->next = NULL;
	k = Merge(tmp0, tmp1, tmp2, 0, 0);
	EXPECT_EQ(k, 0);
	EXPECT_EQ(tmp2->next, nullptr);
	free(tmp0);
	free(tmp1);
	free(tmp2);
}

TEST(CLEAR_ONE_LIST, Merge_TEST)
{
	int k = 0;
	list_t* t0 = NULL;
	t0 = (list_t*)malloc(sizeof(list_t));
	ASSERT_NE(t0, nullptr);
	t0->next = NULL;
	list_t tmp1[3];
	tmp1[0] = { 0, &tmp1[1] };
	tmp1[1] = { 1, &tmp1[2] };
	tmp1[2] = { 2, NULL };
	list_t* sum = NULL;
	sum = (list_t*)malloc(sizeof(list_t));
	ASSERT_NE(sum, nullptr);
	sum->next = NULL;
	k = Merge(t0, tmp1, sum, 0, 2);
	EXPECT_EQ(k, 1);
	EXPECT_EQ(sum->data, 0);
	EXPECT_EQ(sum->next->data, 1);
	EXPECT_EQ(sum->next->next->data, 2);
	EXPECT_EQ(sum->next->next->next, nullptr);
	free(sum->next->next);
	free(sum->next);
	free(sum);
	free(t0);
}

TEST(EQUAL_NUMS, Merge_TEST)
{
	int k = 0;
	list_t tmp0[3];
	tmp0[0] = { 0, &tmp0[1] };
	tmp0[1] = { 1, &tmp0[2] };
	tmp0[2] = { 3, NULL };
	list_t tmp1[4];
	tmp1[0] = { 0, &tmp1[1] };
	tmp1[1] = { 2, &tmp1[2] };
	tmp1[2] = { 3, &tmp1[3] };
	tmp1[3] = { 4, NULL };
	list_t* t3 = NULL;
	t3 = (list_t*)malloc(sizeof(list_t));
	ASSERT_NE(t3, nullptr);
	t3->next = NULL;
	k = Merge(tmp0, tmp1, t3, 3, 4);
	EXPECT_EQ(k, 2);
	EXPECT_EQ(t3->data, 0);
	EXPECT_EQ(t3->next->data, 1);
	EXPECT_EQ(t3->next->next->data, 2);
	EXPECT_EQ(t3->next->next->next->data, 3);
	EXPECT_EQ(t3->next->next->next->next->data, 4);
	EXPECT_EQ(t3->next->next->next->next->next, nullptr);
	free(t3->next->next->next->next);
	free(t3->next->next->next);
	free(t3->next->next);
	free(t3->next);
	free(t3);
}

TEST(DIFFERENT_NUMS, Write_TEST)
{
	const char* name = "TESTS\\forwrite.txt";
	int checkres[4];
	int k2 = 0;
	int k3 = 0;
	list_t tmp[3];
	tmp[0] = { 0, &tmp[1] };
	tmp[1] = { 1, &tmp[2] };
	tmp[2] = { 2, NULL };
	Write(tmp, name, 2);
	FILE* input = fopen(name, "r");
	ASSERT_NE(input, nullptr);
	k2 = fscanf(input, "%d %d %d", &checkres[0], &checkres[1], &checkres[2]);
	k3 = fscanf(input, "%d", &checkres[3]);
	EXPECT_EQ(k2, 3);
	EXPECT_EQ(k3, -1);
	EXPECT_EQ(checkres[0], 0);
	EXPECT_EQ(checkres[1], 1);
	EXPECT_EQ(checkres[2], 2);
	fclose(input);
}

TEST(CLEAR_LIST, Write_TEST)
{
	const char* name = "TESTS\\forwrite.txt";
	int k2 = 0;
	int checkres[1];
	list_t* t1 = NULL;
	t1 = (list_t*)malloc(sizeof(list_t));
	ASSERT_NE(t1, nullptr);
	t1->next = NULL;
	Write(t1, name, 0);
	FILE* input = fopen(name, "r");
	ASSERT_NE(input, nullptr);
	k2 = fscanf(input, "%d", &checkres[0]);
	EXPECT_EQ(k2, -1);
	fclose(input);
	free(t1);
}

TEST(NOT_EMPTY_FILES_DIFFERENT_NUMS, AllOperations_TEST)
{
	int k1, k2, k3;
	k1 = 0;
	k2 = 0;
	k3 = 0;
	int checkres[8];
	const char* name1 = "TESTS\\test1.txt";
	const char* name2 = "TESTS\\test2.txt";
	const char* name3 = "TESTS\\final.txt";
	k1 = AllOperations(name1, name2, name3);
	FILE* input = fopen(name3, "r");
	ASSERT_NE(input, nullptr);
	k2 = fscanf(input, "%d %d %d %d %d %d %d", &checkres[0], &checkres[1], &checkres[2], &checkres[3], &checkres[4], &checkres[5], &checkres[6]);
	k3 = fscanf(input, "%d", &checkres[7]);
	EXPECT_EQ(k1, 1);
	EXPECT_EQ(k2, 7);
	EXPECT_EQ(k3, -1);
	EXPECT_EQ(checkres[0], -3);
	EXPECT_EQ(checkres[1], -2);
	EXPECT_EQ(checkres[2], -1);
	EXPECT_EQ(checkres[3], 0);
	EXPECT_EQ(checkres[4], 1);
	EXPECT_EQ(checkres[5], 2);
	EXPECT_EQ(checkres[6], 3);
	fclose(input);
}

TEST(NOT_EMPTY_FILES_EQUAL_NUMS, AllOperations_TEST)
{
	int k1, k2, k3;
	k1 = 0;
	k2 = 0;
	k3 = 0;
	int checkres[8];
	const char* name1 = "TESTS\\diffnums.txt";
	const char* name2 = "TESTS\\equalnums.txt";
	const char* name3 = "TESTS\\final.txt";
	k1 = AllOperations(name1, name2, name3);
	FILE* input = fopen(name3, "r");
	ASSERT_NE(input, nullptr);
	k2 = fscanf(input, "%d %d %d %d %d %d %d", &checkres[0], &checkres[1], &checkres[2], &checkres[3], &checkres[4], &checkres[5], &checkres[6]);
	k3 = fscanf(input, "%d", &checkres[7]);
	EXPECT_EQ(k1, 1);
	EXPECT_EQ(k2, 7);
	EXPECT_EQ(k3, -1);
	EXPECT_EQ(checkres[0], -3);
	EXPECT_EQ(checkres[1], -2);
	EXPECT_EQ(checkres[2], -1);
	EXPECT_EQ(checkres[3], 0);
	EXPECT_EQ(checkres[4], 1);
	EXPECT_EQ(checkres[5], 2);
	EXPECT_EQ(checkres[6], 3);
	fclose(input);
}

TEST(NOT_EMPTY_AND_EMPTY_FILE, AllOperations_TEST)
{
	int k1, k2, k3;
	k1 = 0;
	k2 = 0;
	k3 = 0;
	int checkres[6];
	const char* name1 = "TESTS\\diffnums.txt";
	const char* name2 = "TESTS\\clear.txt";
	const char* name3 = "TESTS\\final.txt";
	k1 = AllOperations(name1, name2, name3);
	FILE* input = fopen(name3, "r");
	ASSERT_NE(input, nullptr);
	k2 = fscanf(input, "%d %d %d %d %d", &checkres[0], &checkres[1], &checkres[2], &checkres[3], &checkres[4]);
	k3 = fscanf(input, "%d", &checkres[5]);
	EXPECT_EQ(k1, 1);
	EXPECT_EQ(k2, 5);
	EXPECT_EQ(checkres[0], -3);
	EXPECT_EQ(checkres[1], -2);
	EXPECT_EQ(checkres[2], -1);
	EXPECT_EQ(checkres[3], 0);
	EXPECT_EQ(checkres[4], 1);
	fclose(input);
}

TEST(EMPTY_AND_NOT_REAL_FILE, AllOperations_TEST)
{
	int k1;
	k1 = 0;
	const char* name1 = "TESTS\\notreal.txt";
	const char* name2 = "TESTS\\clear.txt";
	const char* name3 = "TESTS\\final1.txt";
	k1 = AllOperations(name1, name2, name3);
	EXPECT_EQ(k1, -1);
}

TEST(NOT_REAL_AND_NOT_REAL_FILE, AllOperations_TEST)
{
	int k1;
	k1 = 0;
	const char* name1 = "TESTS\\notreal1.txt";
	const char* name2 = "TESTS\\notreal2.txt";
	const char* name3 = "TESTS\\final1.txt";
	k1 = AllOperations(name1, name2, name3);
	EXPECT_EQ(k1, -1);
}

TEST(MEMORY_LEAKS, ALL_FUNCTIONS_MEMORY_LEAKS)
{
	MemoryLeaks();
}