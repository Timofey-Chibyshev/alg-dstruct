#include "pch.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "header.h"

TEST(TestCaseName, TestName) 
{
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(FillTreeTest, OneNodeTree) 
{
    /*
        0
    */

    tree t = { 999, nullptr };
    FillTree(&t);
    EXPECT_EQ(t.height, 0); 
}

TEST(FillTreeTest, OneLevelTree) {
    /*
               2
             /
           0
             \
               1
    */

    tree t[3] = { 0 };

    t[0].height = 999;
    t[0].left = &t[1];
    t[0].right = &t[2];
    t[1].height = 999;
    t[1].left = nullptr;
    t[1].right = nullptr;
    t[2].height = 999;
    t[2].left = nullptr;
    t[2].right = nullptr;

    FillTree(t);

    EXPECT_EQ(t[0].height, 1);
    EXPECT_EQ(t[1].height, 0);
    EXPECT_EQ(t[2].height, 0);
}

TEST(FillTreeTest, OneWayTree) {
    /*
             1      3
           /   \   /
         0       2
    */

    tree t[4] = { 0 };

    t[0].height = 999;
    t[0].left = nullptr;
    t[0].right = &t[1];
    t[1].height = 999;
    t[1].left = &t[2];
    t[1].right = nullptr;
    t[2].height = 999;
    t[2].left = nullptr;
    t[2].right = &t[3];
    t[3].height = 999;
    t[3].left = nullptr;
    t[3].right = nullptr;

    FillTree(t);

    EXPECT_EQ(t[0].height, 3);
    EXPECT_EQ(t[1].height, 2);
    EXPECT_EQ(t[2].height, 1);
    EXPECT_EQ(t[3].height, 0);
}

TEST(FillTreeTest, NearlyOneWayTree) {
    /*
        0
       /
      1
       \
        2
       / \
      5   3
         /
        4
    */

    tree t[6] = { 0 };
  
    t[0].height = 999;
    t[0].left = &t[1];
    t[0].right = nullptr;
    t[1].height = 999;
    t[1].left = nullptr;
    t[1].right = &t[2];
    t[2].height = 999;
    t[2].left = &t[5];
    t[2].right = &t[3];
    t[3].height = 999;
    t[3].left = &t[4];
    t[3].right = nullptr;
    t[4].height = 999; 
    t[4].left = nullptr; 
    t[4].right = nullptr;
    t[5].height = 999;
    t[5].left = nullptr;
    t[5].right = nullptr;

    FillTree(t);

    EXPECT_EQ(t[0].height, 3); 
    EXPECT_EQ(t[1].height, 2); 
    EXPECT_EQ(t[2].height, 1); 
    EXPECT_EQ(t[3].height, 1);
    EXPECT_EQ(t[4].height, 0);
    EXPECT_EQ(t[5].height, 0);
}

TEST(FillTreeTest, FullTree) {
/*
                  2
                /  
               /
              0         /7
               \      4 
                \   / 
                  1 
                    \  /6
                      3
                       \5
 */  

    tree t[8] = { 0 };

    t[0].height = 999;
    t[0].left = &t[1];
    t[0].right = &t[2];
    t[1].height = 999;
    t[1].left = &t[3];
    t[1].right = &t[4];
    t[2].height = 999;
    t[2].left = nullptr;
    t[2].right = nullptr;
    t[3].height = 999;
    t[3].left = &t[5];
    t[3].right = &t[6];
    t[4].height = 999;
    t[4].left = nullptr;
    t[4].right = &t[7];
    t[5].height = 999;
    t[5].left = nullptr;
    t[5].right = nullptr;
    t[6].height = 999;
    t[6].left = nullptr;
    t[6].right = nullptr;
    t[7].height = 999;
    t[7].left = nullptr;
    t[7].right = nullptr;

    FillTree(t);

    EXPECT_EQ(t[0].height, 1);
    EXPECT_EQ(t[1].height, 2);
    EXPECT_EQ(t[2].height, 0);
    EXPECT_EQ(t[3].height, 1);
    EXPECT_EQ(t[4].height, 1);
    EXPECT_EQ(t[5].height, 0);
    EXPECT_EQ(t[6].height, 0);
    EXPECT_EQ(t[7].height, 0);
}

void PrintTreeFuncTest(tree* t, const char* filenameOut) 
{
    FILE* fp = fopen(filenameOut, "w");
    ASSERT_NE(fp, nullptr);
    PrintTree(fp, t, 0);
    fclose(fp);
}

TEST(PrintTreeTest, OneNodeTree)
{
    /*
        0
    */
    tree t = { 0, nullptr };

    int correctAnswer = 0;
    int fromFile;
    const char* filename = "oneVertex.txt";
    
    PrintTreeFuncTest(&t, filename);
    
    FILE* fp = fopen(filename, "r");
    ASSERT_NE(fp, nullptr);
    ASSERT_TRUE(fscanf(fp, "%d", &fromFile));
    
    EXPECT_EQ(fromFile, correctAnswer);
}

TEST(PrintTreeTest, OneLevelTree)
{
    /*  
               2
             /
           0
             \
               1
    */
   
    tree t[3] = { 0 };

    t[0].height = 1;
    t[0].left = &t[1];
    t[0].right = &t[2];
    t[1].height = 0;
    t[1].left = nullptr;
    t[1].right = nullptr;
    t[2].height = 0;
    t[2].left = nullptr;
    t[2].right = nullptr;

    int correctAnswer[3] = { 0, 1, 0 };
    int fromFile[3];
    const char* filename = "oneLevel.txt";

    PrintTreeFuncTest(&t[0], filename);

    FILE* fp = fopen(filename, "r");
    ASSERT_NE(fp, nullptr);

    ASSERT_TRUE(fscanf(fp, "%d", &fromFile[0]));
    ASSERT_TRUE(fscanf(fp, "%d", &fromFile[1]));
    ASSERT_TRUE(fscanf(fp, "%d", &fromFile[2]));
    
    EXPECT_EQ(memcmp(fromFile, correctAnswer, 3), 0);
    
    fclose(fp);
}

TEST(PrintTreeTest, OneWayTree) 
{
    /*
             1      
           /   \   / 3
          /      2
        0
    */

    tree t[4] = { 0 };

    t[0].height = 3;
    t[0].left = nullptr;
    t[0].right = &t[1];
    t[1].height = 2;
    t[1].left = &t[2];
    t[1].right = nullptr;
    t[2].height = 1;
    t[2].left = nullptr;
    t[2].right = &t[3];
    t[3].height = 0;
    t[3].left = nullptr;
    t[3].right = nullptr;

    int correctAnswer[4] = { 2, 0, 1, 3 };
    int fromFile[4];
    const char* filename = "oneWay.txt";

    PrintTreeFuncTest(&t[0], filename);

    FILE* fp = fopen(filename, "r");
    ASSERT_NE(fp, nullptr);

    ASSERT_TRUE(fscanf(fp, "%d", &fromFile[0]));
    ASSERT_TRUE(fscanf(fp, "%d", &fromFile[1]));
    ASSERT_TRUE(fscanf(fp, "%d", &fromFile[2]));
    ASSERT_TRUE(fscanf(fp, "%d", &fromFile[3]));

    EXPECT_EQ(memcmp(fromFile, correctAnswer, 4), 0);

    fclose(fp);
}

TEST(PrintTreeTest, NearlyOneWayTree) 
{
    /*
                         
            0  
             \             3
              \          /   \4
               \       2
                \    /   \
                 \  /      5 
                  1     
    */

    tree t[6] = { 0 };

    t[0].height = 3;
    t[0].left = &t[1];
    t[0].right = nullptr;
    t[1].height = 2;
    t[1].left = nullptr;
    t[1].right = &t[2];
    t[2].height = 1;
    t[2].left = &t[5];
    t[2].right = &t[3];
    t[3].height = 1;
    t[3].left = &t[4];
    t[3].right = nullptr;
    t[4].height = 0;
    t[4].left = nullptr;
    t[4].right = nullptr;
    t[5].height = 0;
    t[5].left = nullptr;
    t[5].right = nullptr;

    int correctAnswer[6] = { 3, 1, 0, 1, 0, 2 };
    int fromFile[6];
    const char* filename = "nearlyOneWay.txt";

    PrintTreeFuncTest(&t[0], filename);

    FILE* fp = fopen(filename, "r");
    ASSERT_NE(fp, nullptr);

    ASSERT_TRUE(fscanf(fp, "%d", &fromFile[0]));
    ASSERT_TRUE(fscanf(fp, "%d", &fromFile[1]));
    ASSERT_TRUE(fscanf(fp, "%d", &fromFile[2]));
    ASSERT_TRUE(fscanf(fp, "%d", &fromFile[3]));
    ASSERT_TRUE(fscanf(fp, "%d", &fromFile[4]));
    ASSERT_TRUE(fscanf(fp, "%d", &fromFile[5]));

    EXPECT_EQ(memcmp(fromFile, correctAnswer, 6), 0);

    fclose(fp);
}

TEST(PrintTreeTest, FullTree) {
    /*
                      2
                    /
                   /
                  0         /7
                   \      4
                    \   /
                      1
                        \  /6
                          3
                           \5
     */

    tree t[8] = { 0 };

    t[0].height = 1;
    t[0].left = &t[1];
    t[0].right = &t[2];
    t[1].height = 2;
    t[1].left = &t[3];
    t[1].right = &t[4];
    t[2].height = 0;
    t[2].left = nullptr;
    t[2].right = nullptr;
    t[3].height = 1;
    t[3].left = &t[5];
    t[3].right = &t[6];
    t[4].height = 1;
    t[4].left = nullptr;
    t[4].right = &t[7];
    t[5].height = 0;
    t[5].left = nullptr;
    t[5].right = nullptr;
    t[6].height = 0;
    t[6].left = nullptr;
    t[6].right = nullptr;
    t[7].height = 0;
    t[7].left = nullptr;
    t[7].right = nullptr;

    int correctAnswer[8] = { 0, 1, 0, 1, 2, 0, 1, 0 };
    int fromFile[8];
    const char* filename = "fullWay.txt";

    PrintTreeFuncTest(&t[0], filename);

    FILE* fp = fopen(filename, "r");
    ASSERT_NE(fp, nullptr);

    ASSERT_TRUE(fscanf(fp, "%d", &fromFile[0]));
    ASSERT_TRUE(fscanf(fp, "%d", &fromFile[1]));
    ASSERT_TRUE(fscanf(fp, "%d", &fromFile[2]));
    ASSERT_TRUE(fscanf(fp, "%d", &fromFile[3]));
    ASSERT_TRUE(fscanf(fp, "%d", &fromFile[4]));
    ASSERT_TRUE(fscanf(fp, "%d", &fromFile[5]));
    ASSERT_TRUE(fscanf(fp, "%d", &fromFile[6]));
    ASSERT_TRUE(fscanf(fp, "%d", &fromFile[7]));

    EXPECT_EQ(memcmp(fromFile, correctAnswer, 8), 0);

    fclose(fp);
}
