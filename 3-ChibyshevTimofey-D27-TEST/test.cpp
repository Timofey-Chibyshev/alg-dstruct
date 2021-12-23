#include "pch.h"
#include "Header.h"

/*
IDE: Microsoft Visual Studio 2019
OS: Windows 10 Home rus 20H2 Build 19042.1348
PC configuration:
    CPU:            Intel(R) Core(TM) i3-7020U CPU @ 2.30GHz
    Motherboard:    LENOVO
    RAM:            8GB
    HDD:            1TB
*/

/*
StressTest results (run on Release VS configuration):
    Time: 57.601 sec to output answer
    RAM:  898 KB
*/

TEST(TestCaseName, TestName) 
{
    EXPECT_EQ(1, 1);
    EXPECT_TRUE(true);
}

TEST(StressTest, LabSolution) 
{
    const char* stressFileName1 = "forStressInput.txt";
    const char* stressFileName2 = "forStressOutput.txt";
    EXPECT_EQ(LabSolution(stressFileName1, stressFileName2), 1);
}

TEST(N4Test, FunctionalTest1)
{
    const char* filename1 = "N4Input.txt";
    const char* filename2 = "N4Output.txt";
    int k = LabSolution(filename1, filename2);
    EXPECT_EQ(k, 1);
    FILE* fp = fopen(filename2, "r");
    ASSERT_TRUE(fp);
    int correctResult[8] = {0, 1, 1, 3, 2, 0, 3, 2};
    int result[8];
    ASSERT_TRUE(fscanf(fp, "%d", &result[0]));
    ASSERT_TRUE(fscanf(fp, "%d", &result[1]));
    ASSERT_TRUE(fscanf(fp, "%d", &result[2]));
    ASSERT_TRUE(fscanf(fp, "%d", &result[3]));
    ASSERT_TRUE(fscanf(fp, "%d", &result[4]));
    ASSERT_TRUE(fscanf(fp, "%d", &result[5]));
    ASSERT_TRUE(fscanf(fp, "%d", &result[6]));
    ASSERT_TRUE(fscanf(fp, "%d", &result[7]));
    EXPECT_EQ(result[0], correctResult[0]);
    EXPECT_EQ(result[1], correctResult[1]);
    EXPECT_EQ(result[2], correctResult[2]);
    EXPECT_EQ(result[3], correctResult[3]);
    EXPECT_EQ(result[4], correctResult[4]);
    EXPECT_EQ(result[5], correctResult[5]);
    EXPECT_EQ(result[6], correctResult[6]);
    EXPECT_EQ(result[7], correctResult[7]);
    fclose(fp);
}

TEST(N3Test, FunctionalTest2)
{
    const char* filename1 = "N3Input.txt";
    const char* filename2 = "N3Output.txt";
    int k = LabSolution(filename1, filename2);
    EXPECT_EQ(k, 0);
}

TEST(N2Test, FunctionalTest3)
{
    const char* filename1 = "N2Input.txt";
    const char* filename2 = "N2Output.txt";
    int k = LabSolution(filename1, filename2);
    EXPECT_EQ(k, 0);
}

TEST(N8Test, FunctionalTest4)
{
    const char* filename1 = "N8Input.txt";
    const char* filename2 = "N8Output.txt";
    int k = LabSolution(filename1, filename2);
    EXPECT_EQ(k, 1);
    FILE* fp = fopen(filename2, "r");
    ASSERT_TRUE(fp);
    int correctResult[16] = { 0, 0, 1, 4, 2, 7, 3, 5, 4, 2, 5, 6, 6, 1, 7, 3 };
    int result[16];
    ASSERT_TRUE(fscanf(fp, "%d", &result[0]));
    ASSERT_TRUE(fscanf(fp, "%d", &result[1]));
    ASSERT_TRUE(fscanf(fp, "%d", &result[2]));
    ASSERT_TRUE(fscanf(fp, "%d", &result[3]));
    ASSERT_TRUE(fscanf(fp, "%d", &result[4]));
    ASSERT_TRUE(fscanf(fp, "%d", &result[5]));
    ASSERT_TRUE(fscanf(fp, "%d", &result[6]));
    ASSERT_TRUE(fscanf(fp, "%d", &result[7]));
    ASSERT_TRUE(fscanf(fp, "%d", &result[8]));
    ASSERT_TRUE(fscanf(fp, "%d", &result[9]));
    ASSERT_TRUE(fscanf(fp, "%d", &result[10]));
    ASSERT_TRUE(fscanf(fp, "%d", &result[11]));
    ASSERT_TRUE(fscanf(fp, "%d", &result[12]));
    ASSERT_TRUE(fscanf(fp, "%d", &result[13]));
    ASSERT_TRUE(fscanf(fp, "%d", &result[14]));
    ASSERT_TRUE(fscanf(fp, "%d", &result[15]));
    EXPECT_EQ(result[0], correctResult[0]);
    EXPECT_EQ(result[1], correctResult[1]);
    EXPECT_EQ(result[2], correctResult[2]);
    EXPECT_EQ(result[3], correctResult[3]);
    EXPECT_EQ(result[4], correctResult[4]);
    EXPECT_EQ(result[5], correctResult[5]);
    EXPECT_EQ(result[6], correctResult[6]);
    EXPECT_EQ(result[7], correctResult[7]);
    EXPECT_EQ(result[8], correctResult[8]);
    EXPECT_EQ(result[9], correctResult[9]);
    EXPECT_EQ(result[10], correctResult[10]);
    EXPECT_EQ(result[11], correctResult[11]);
    EXPECT_EQ(result[12], correctResult[12]);
    EXPECT_EQ(result[13], correctResult[13]);
    EXPECT_EQ(result[14], correctResult[14]);
    EXPECT_EQ(result[15], correctResult[15]);
    fclose(fp);
}