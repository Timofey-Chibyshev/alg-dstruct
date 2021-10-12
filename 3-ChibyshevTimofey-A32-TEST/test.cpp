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
	list_t* p = NULL;
	p = tmp;
	tmp = tmp->next;
	free(p);
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
	list_t* p = NULL;
	p = tmp;
	tmp = tmp->next;
	free(p);
	p = tmp;
	tmp = tmp->next;
	free(p);
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
	EXPECT_EQ(len, 4);
	EXPECT_EQ(tmp->data, -3);
	EXPECT_EQ(tmp->next->data, -2);
	EXPECT_EQ(tmp->next->next->data, -1);
	EXPECT_EQ(tmp->next->next->next->data, 0);
	EXPECT_EQ(tmp->next->next->next->next->data, 1);
	EXPECT_EQ(tmp->next->next->next->next->next, nullptr);
	list_t* p = NULL;
	p = tmp;
	tmp = tmp->next;
	free(p);
	p = tmp;
	tmp = tmp->next;
	free(p);
	p = tmp;
	tmp = tmp->next;
	free(p);
	p = tmp;
	tmp = tmp->next;
	free(p);
	p = tmp;
	tmp = tmp->next;
	free(p);
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
	list_t* p = NULL;
	p = tmp;
	tmp = tmp->next;
	free(p);
}

TEST(DIFFERENT_NUMS, Merge_TEST)
{
	int k = 0;
	list_t tmp0[3];
	ASSERT_NE(tmp0, nullptr);
	tmp0[0] = { 0, &tmp0[1] };
	tmp0[1] = { 1, &tmp0[2] };
	tmp0[2] = { 4, NULL };
	list_t tmp1[4];
	ASSERT_NE(tmp1, nullptr);
	tmp1[0] = { 2, &tmp1[1] };
	tmp1[1] = { 3, &tmp1[2] };
	tmp1[2] = { 5, &tmp1[3] };
	tmp1[3] = { 6, NULL };
	list_t tmp2[7];
	ASSERT_NE(tmp2, nullptr);
	tmp2[0].next = &tmp2[1];
	tmp2[1].next = &tmp2[2];
	tmp2[2].next = &tmp2[3];
	tmp2[3].next = &tmp2[4];
	tmp2[4].next = &tmp2[5];
	tmp2[5].next = &tmp2[6];
	tmp2[6].next = NULL;
	list_t* t1 = NULL;
	t1 = tmp0;
	list_t* t2 = NULL;
	t2 = tmp1;
	list_t* t3 = NULL;
	t3 = tmp2;
	k = Merge(t1, t2, t3, 2, 3);
	EXPECT_EQ(k, 2);
	EXPECT_EQ(t3->data, 0);
	EXPECT_EQ(t3->next->data, 1);
	EXPECT_EQ(t3->next->next->data, 2);
	EXPECT_EQ(t3->next->next->next->data, 3);
	EXPECT_EQ(t3->next->next->next->next->data, 4);
	EXPECT_EQ(t3->next->next->next->next->next->data, 5);
	EXPECT_EQ(t3->next->next->next->next->next->next->data, 6);
	EXPECT_EQ(t3->next->next->next->next->next->next->next, nullptr);
	t3 = t3->next;
	Destroy(t3);
}

TEST(CLEAR_TWO_LISTS, Merge_TEST)
{
	int k = 0;
	list_t* tmp0 = NULL;
	list_t* tmp1 = NULL;
	list_t* tmp2 = NULL;
	k = Merge(tmp0, tmp1, tmp2, 0, 0);
	EXPECT_EQ(k, 0);
	EXPECT_EQ(tmp2, nullptr);
}

TEST(CLEAR_ONE_LIST, Merge_TEST)
{
	int k = 0;
	list_t* t0 = NULL;
	list_t tmp1[3];
	ASSERT_NE(tmp1, nullptr);
	tmp1[0] = { 0, &tmp1[1] };
	tmp1[1] = { 1, &tmp1[2] };
	tmp1[2] = { 2, NULL };
	list_t tmp2[3];
	ASSERT_NE(tmp2, nullptr);
	tmp2[0] = { 0, &tmp2[1] };
	tmp2[1] = { 1, &tmp2[2] };
	tmp2[2] = { 2, NULL };
	list_t* t1 = NULL;
	t1 = tmp1;
	list_t* sum = NULL;
	sum = tmp2;
	k = Merge(t0, t1, sum, 0, 2);
	EXPECT_EQ(k, 1);
	EXPECT_EQ(sum->data, 0);
	EXPECT_EQ(sum->next->data, 1);
	EXPECT_EQ(sum->next->next->data, 2);
	EXPECT_EQ(sum->next->next->next, nullptr);
	sum = sum->next;
	Destroy(sum);
}

TEST(EQUAL_NUMS, Merge_TEST)
{
	int k = 0;
	list_t tmp0[3];
	ASSERT_NE(tmp0, nullptr);
	tmp0[0] = { 0, &tmp0[1] };
	tmp0[1] = { 1, &tmp0[2] };
	tmp0[2] = { 3, NULL };
	list_t tmp1[4];
	ASSERT_NE(tmp1, nullptr);
	tmp1[0] = { 0, &tmp1[1] };
	tmp1[1] = { 2, &tmp1[2] };
	tmp1[2] = { 3, &tmp1[3] };
	tmp1[3] = { 4, NULL };
	list_t tmp2[7];
	ASSERT_NE(tmp2, nullptr);
	tmp2[0].next = &tmp2[1];
	tmp2[1].next = &tmp2[2];
	tmp2[2].next = &tmp2[3];
	tmp2[3].next = &tmp2[4];
	tmp2[4].next = &tmp2[5];
	tmp2[5].next = &tmp2[6];
	tmp2[6].next = NULL;
	list_t* t1 = NULL;
	t1 = tmp0;
	list_t* t2 = NULL;
	t2 = tmp1;
	list_t* t3 = NULL;
	t3 = tmp2;
	k = Merge(t1, t2, t3, 2, 3);
	EXPECT_EQ(k, 2);
	EXPECT_EQ(t3->data, 0);
	EXPECT_EQ(t3->next->data, 1);
	EXPECT_EQ(t3->next->next->data, 2);
	EXPECT_EQ(t3->next->next->next->data, 3);
	EXPECT_EQ(t3->next->next->next->next->data, 4);
	EXPECT_EQ(t3->next->next->next->next->next, nullptr);
	t3 = t3->next;
	Destroy(t3);
}

TEST(DIFFERENT_NUMS, Write_TEST)
{
	const char* name = "TESTS\\forwrite.txt";
	int checkres[3];
	int k1 = 0;
	int k2 = 0;
	list_t tmp[3];
	ASSERT_NE(tmp, nullptr);
	tmp[0] = { 0, &tmp[1] };
	tmp[1] = { 1, &tmp[2] };
	tmp[2] = { 2, NULL };
	list_t* t1 = NULL;
	t1 = tmp;
	k1 = Write(tmp, name, 2);
	EXPECT_EQ(k1, 2);
	FILE* input = fopen(name, "r");
	ASSERT_NE(input, nullptr);
	k2 = fscanf(input, "%d %d %d", &checkres[0], &checkres[1], &checkres[2]);
	EXPECT_EQ(k2, 3);
	EXPECT_EQ(checkres[0], 0);
	EXPECT_EQ(checkres[1], 1);
	EXPECT_EQ(checkres[2], 2);
	fclose(input);
}

TEST(CLEAR_LIST, Write_TEST)
{
	const char* name = "TESTS\\forwrite.txt";
	int k1 = 0;
	int k2 = 0;
	int checkres[1];
	list_t* t1 = NULL;
	k1 = Write(t1, name, 0);
	EXPECT_EQ(k1, 1);
	FILE* input = fopen(name, "r");
	ASSERT_NE(input, nullptr);
	k2 = fscanf(input, "%d", &checkres[0]);
	EXPECT_EQ(k2, -1);
	fclose(input);
}

TEST(NOT_EMPTY_FILES_DIFFERENT_NUMS, AllOperations_TEST)
{
	int k1, k2;
	k1 = 0;
	k2 = 0;
	int checkres[7];
	const char* name1 = "TESTS\\test1.txt";
	const char* name2 = "TESTS\\test2.txt";
	const char* name3 = "TESTS\\final.txt";
	k1 = AllOperations(name1, name2, name3);
	FILE* input = fopen(name3, "r");
	ASSERT_NE(input, nullptr);
	k2 = fscanf(input, "%d %d %d %d %d %d %d", &checkres[0], &checkres[1], &checkres[2], &checkres[3], &checkres[4], &checkres[5], &checkres[6]);
	EXPECT_EQ(k1, 2);
	EXPECT_EQ(k2, 7);
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
	int k1, k2;
	k1 = 0;
	k2 = 0;
	int checkres[7];
	const char* name1 = "TESTS\\diffnums.txt";
	const char* name2 = "TESTS\\equalnums.txt";
	const char* name3 = "TESTS\\final.txt";
	k1 = AllOperations(name1, name2, name3);
	FILE* input = fopen(name3, "r");
	ASSERT_NE(input, nullptr);
	k2 = fscanf(input, "%d %d %d %d %d %d %d", &checkres[0], &checkres[1], &checkres[2], &checkres[3], &checkres[4], &checkres[5], &checkres[6]);
	EXPECT_EQ(k1, 2);
	EXPECT_EQ(k2, 7);
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
	int k1, k2;
	k1 = 0;
	k2 = 0;
	int checkres[5];
	const char* name1 = "TESTS\\diffnums.txt";
	const char* name2 = "TESTS\\clear.txt";
	const char* name3 = "TESTS\\final.txt";
	k1 = AllOperations(name1, name2, name3);
	FILE* input = fopen(name3, "r");
	ASSERT_NE(input, nullptr);
	k2 = fscanf(input, "%d %d %d %d %d", &checkres[0], &checkres[1], &checkres[2], &checkres[3], &checkres[4]);
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