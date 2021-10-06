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

TEST(LIST_TEST, Create)
{
	list_t* tmp = NULL;
	tmp = Create();
	ASSERT_NE(tmp, nullptr);
	EXPECT_EQ(tmp->next, nullptr);
	Destroy(tmp);
}

TEST(NUMS_FILE1, NumberCount)
{
	int counter;
	FILE* input = fopen("TESTS\\test1.txt", "r");
	ASSERT_NE(input, nullptr);
	counter = NumberCount(input);
	EXPECT_EQ(counter, 5);
	fclose(input);
}

TEST(NUMS_FILE2, NumberCount)
{
	int counter;
	FILE* input1 = fopen("TESTS\\test2.txt", "r");
	ASSERT_NE(input1, nullptr);
	counter = NumberCount(input1);
	EXPECT_EQ(counter, 6);
	fclose(input1);
}

TEST(NO_NUMS_FILE, NumberCount)
{
	int counter;
	FILE* input2 = fopen("TESTS\\nonumsf.txt", "r");
	ASSERT_NE(input2, nullptr);
	counter = NumberCount(input2);
	EXPECT_EQ(counter, 0);
	fclose(input2);
}

TEST(CLEAR_FILE, NumberCount)
{
	int counter;
	FILE* input3 = fopen("TESTS\\clear.txt", "r");
	ASSERT_NE(input3, nullptr);
	counter = NumberCount(input3);
	EXPECT_EQ(counter, 0);
	fclose(input3);
}

TEST(END_ELEM, AddElementEnd)
{
	list_t* tmp = NULL;
	tmp = (list_t*)malloc(sizeof(list_t));
	ASSERT_NE(tmp, nullptr);
	tmp->data = 0;
	tmp->next = NULL;
	AddElementEnd(-1, tmp);
	ASSERT_NE(tmp, nullptr);
	EXPECT_EQ(tmp->next->data, -1);
	EXPECT_EQ(tmp->next->next, nullptr);
	Destroy(tmp);
}

TEST(READ_FILE1, ReadNumbers)
{
	list_t* tmp = NULL;
	tmp = (list_t*)malloc(sizeof(list_t));
	ASSERT_NE(tmp, nullptr);
	tmp->next = NULL;
	FILE* input = fopen("TESTS\\test1.txt", "r");
	ASSERT_NE(input, nullptr);
	int k = ReadNumbers(input, tmp, 5);
	EXPECT_EQ(k, 1);
	EXPECT_EQ(tmp->data, 2);
	EXPECT_EQ(tmp->next->data, -4224);
	EXPECT_EQ(tmp->next->next->data, 45);
	EXPECT_EQ(tmp->next->next->next->data, 68);
	EXPECT_EQ(tmp->next->next->next->next->data, 3);
	EXPECT_EQ(tmp->next->next->next->next->next, nullptr);
	fclose(input);
	Destroy(tmp);
}

TEST(READ_FILE2, ReadNumbers)
{
	list_t* tmp = NULL;
	tmp = (list_t*)malloc(sizeof(list_t));
	ASSERT_NE(tmp, nullptr);
	tmp->next = NULL;
	FILE* input1 = fopen("TESTS\\test2.txt", "r");
	ASSERT_NE(input1, nullptr);
	int k = ReadNumbers(input1, tmp, 6);
	EXPECT_EQ(k, 1);
	EXPECT_EQ(tmp->data, 0);
	EXPECT_EQ(tmp->next->data, 1);
	EXPECT_EQ(tmp->next->next->data, 5353);
	EXPECT_EQ(tmp->next->next->next->data, 433);
	EXPECT_EQ(tmp->next->next->next->next->data, 234);
	EXPECT_EQ(tmp->next->next->next->next->next->data, 13);
	EXPECT_EQ(tmp->next->next->next->next->next->next, nullptr);
	fclose(input1);
	Destroy(tmp);
}

TEST(NO_NUMS_FILE, ReadNumbers)
{
	list_t* tmp = NULL;
	tmp = (list_t*)malloc(sizeof(list_t));
	ASSERT_NE(tmp, nullptr);
	tmp->next = NULL;
	FILE* input2 = fopen("TESTS\\nonumsf.txt", "r");
	ASSERT_NE(input2, nullptr);
	int k = ReadNumbers(input2, tmp, 0);
	EXPECT_EQ(k, 0);
	EXPECT_EQ(tmp->next, nullptr);
	fclose(input2);
	Destroy(tmp);
}

TEST(CLEAR_FILE, ReadNumbers)
{
	list_t* tmp = NULL;
	tmp = (list_t*)malloc(sizeof(list_t));
	ASSERT_NE(tmp, nullptr);
	tmp->next = NULL;
	FILE* input3 = fopen("TESTS\\clear.txt", "r");
	ASSERT_NE(input3, nullptr);
	int k = ReadNumbers(input3, tmp, 0);
	EXPECT_EQ(k, 0);
	EXPECT_EQ(tmp->next, nullptr);
	fclose(input3);
	Destroy(tmp);
}

TEST(RES_OF_MERGE, Merge)
{
	list_t tmp0[3];
	ASSERT_NE(tmp0, nullptr);
	tmp0[0].data = 0;
	tmp0[0].next = &tmp0[1];
	tmp0[1].data = 1;
	tmp0[1].next = &tmp0[2];
	tmp0[2].data = 9;
	tmp0[2].next = NULL;
	list_t tmp1[4];
	ASSERT_NE(tmp1, nullptr);
	tmp1[0].data = 2;
	tmp1[0].next = &tmp1[1];
	tmp1[1].data = 3;
	tmp1[1].next = &tmp1[2];
	tmp1[2].data = 6;
	tmp1[2].next = &tmp1[3];
	tmp1[3].data = 8;
	tmp1[3].next = NULL;
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
	Merge(t1, t2, t3);
	EXPECT_EQ(t3->data, 0);
	EXPECT_EQ(t3->next->data, 1);
	EXPECT_EQ(t3->next->next->data, 2);
	EXPECT_EQ(t3->next->next->next->data, 3);
	EXPECT_EQ(t3->next->next->next->next->data, 6);
	EXPECT_EQ(t3->next->next->next->next->next->data, 8);
	EXPECT_EQ(t3->next->next->next->next->next->next->data, 9);
	EXPECT_EQ(t3->next->next->next->next->next->next->next, nullptr);

}

TEST(UNSORT_NUMS, InserationSort)
{
	list_t tmp[5];
	tmp[0].data = -5;
	tmp[0].next = &tmp[1];
	tmp[1].data = 4;
	tmp[1].next = &tmp[2];
	tmp[2].data = 2;
	tmp[2].next = &tmp[3];
	tmp[3].data = 0;
	tmp[3].next = &tmp[4];
	tmp[4].data = 1;
	tmp[4].next = NULL;
	list_t* t = NULL;
	list_t* res = NULL;
	t = tmp;
	res = InserationSort(t);
	ASSERT_NE(res, nullptr);
	EXPECT_EQ(res->data, -5);
	EXPECT_EQ(res->next->data, 0);
	EXPECT_EQ(res->next->next->data, 1);
	EXPECT_EQ(res->next->next->next->data, 2);
	EXPECT_EQ(res->next->next->next->next->data, 4);
	EXPECT_EQ(res->next->next->next->next->next, nullptr);
}

TEST(SORT_NUMS, InserationSort)
{
	list_t tmp[5];
	tmp[0].data = -5;
	tmp[0].next = &tmp[1];
	tmp[1].data = -4;
	tmp[1].next = &tmp[2];
	tmp[2].data = -2;
	tmp[2].next = &tmp[3];
	tmp[3].data = 0;
	tmp[3].next = &tmp[4];
	tmp[4].data = 1;
	tmp[4].next = NULL;
	list_t* t = NULL;
	list_t* res = NULL;
	t = tmp;
	res = InserationSort(t);
	ASSERT_NE(res, nullptr);
	EXPECT_EQ(res->data, -5);
	EXPECT_EQ(res->next->data, -4);
	EXPECT_EQ(res->next->next->data, -2);
	EXPECT_EQ(res->next->next->next->data, 0);
	EXPECT_EQ(res->next->next->next->next->data, 1);
	EXPECT_EQ(res->next->next->next->next->next, nullptr);
}

TEST(MEMORY_LEAKS, ALL_FUNCTIONS_MEMORY_LEAKS)
{
	MemoryLeaks();
}