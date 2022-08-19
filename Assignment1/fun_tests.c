#include <stdio.h>
#include <stdlib.h>
#include "student_functions.h"
#include "fun_tests.h"

void Test_Clean_Whitespace() {
    char case1[] = "  yang lei ";
    Clean_Whitespace(case1);
    printf("%s\n", case1);
}


void Test_CopyCharArray() {
    char des[1024] = {0};
    char case1[] = " yang lei ";
    copyCharArray(des, case1, 10);
    printf("case1=%s|;  des=%s|\n", case1, des);
}

void Read_CSV(char *filename, char csv[10][1024], int *num_movies) {
    FILE *fp;
    fp = fopen(filename, "r");
    fscanf(fp, "%d", num_movies);
    char read_rest_of_line[1024];
    fgets(read_rest_of_line, 1024, fp);
    printf("%s\n", read_rest_of_line);
    for (int i=0; i<*num_movies; i++){
        fgets(csv[i], 1024, fp);
        printf("%s\n", csv[i]);
    }
    fclose(fp);
    return;
}

void Test_MySplit() {
    char csv[10][1024]; // data structure for the entire movie csv file
    int num_movies;
    char titles[10][1024];
    char years[10][1024];
    char directors[10][1024];
    char ratings[10][1024];
    char dollars[10][1024];
    Read_CSV("movies1.csv", csv, &num_movies);
    printf("%d\n", num_movies);
    MySplit(csv, num_movies, titles, years, directors, ratings, dollars);
    printf("title: \n");
    for(int i = 0; i < num_movies; i++ )
    {
        printf("%s|-", titles[i]);
        printf("\n");
    }

    printf("years: \n");
    for(int i = 0; i < num_movies; i++ )
    {
        printf("%s|-", years[i]);
        printf("\n");
    }

    printf("directors: \n");
    for(int i = 0; i < num_movies; i++ )
    {
        printf("%s|-", directors[i]);
        printf("\n");
    }

    printf("ratings: \n");
    for(int i = 0; i < num_movies; i++ )
    {
        printf("%s|-", ratings[i]);
        printf("\n");
    }

    printf("dollars: \n");
    for(int i = 0; i < num_movies; i++ )
    {
        printf("%s|-", dollars[i]);
        printf("\n");
    }

}