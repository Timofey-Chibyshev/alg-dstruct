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
	while (tmp != NULL)
	{
		p = tmp;
		tmp = tmp->next;
		free(p);
	}
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
	while (tmp != NULL)
	{
		p = tmp;
		tmp = tmp->next;
		free(p);
	}
}

TEST(DIFFERET_NUMS, ReadNumbers_TEST)
{
	int k = 0;
	int len = 0;
	const char* name = "TESTS\\test1.txt";
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
	while (tmp != NULL)
	{
		p = tmp;
		tmp = tmp->next;
		free(p);
	}
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
	while (tmp != NULL)
	{
		p = tmp;
		tmp = tmp->next;
		free(p);
	}
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
	EXPECT_EQ(t3->next->data, 0);
	EXPECT_EQ(t3->next->next->data, 1);
	EXPECT_EQ(t3->next->next->next->data, 2);
	EXPECT_EQ(t3->next->next->next->next->data, 3);
	EXPECT_EQ(t3->next->next->next->next->next->data, 3);
	EXPECT_EQ(t3->next->next->next->next->next->next->data, 4);
	EXPECT_EQ(t3->next->next->next->next->next->next->next, nullptr);
}

TEST(DIFFERENT_NUMS, Write_TEST)
{
	const char* name = "TESTS\\forwrite.txt";
	int k = 0;
	list_t tmp[3];
	ASSERT_NE(tmp, nullptr);
	tmp[0] = { 0, &tmp[1] };
	tmp[1] = { 1, &tmp[2] };
	tmp[2] = { 2, NULL };
	list_t* t1 = NULL;
	t1 = tmp;
	k = Write(tmp, name, 2);
	EXPECT_EQ(k, 2);
}

TEST(CLEAR_LIST, Write_TEST)
{
	const char* name = "TESTS\\forwrite.txt";
	int k = 0;
	list_t* t1 = NULL;
	k = Write(t1, name, 0);
	EXPECT_EQ(k, 1);
}

TEST(MEMORY_LEAKS, ALL_FUNCTIONS_MEMORY_LEAKS)
{
	MemoryLeaks();
}