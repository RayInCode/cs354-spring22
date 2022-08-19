/*
 * name: Lei Yang
 * uw net Id: lyang439@wisc.edu
*/

#include <stdio.h>
#include <stdlib.h>
#include "student_functions.h"



/* this function takes a string and ruturns the number of
 * valid char (length in other word) in it excluding 
 * end sign '\0'
 * Example: Get_Len_String("test_*it") -> 7
*/
int Get_Len_String(char str[]) {
    int size = 0;
    int i = 0;
    while(str[i] != '\0') 
        i++;
    size = i;
    return size;
}

/* this function take a two dimension array of char (array of string)
 * and is valid number of its first dimension, to figure out the longest
 * length of strings
 * Example:
 * str = {"fistr", "second", "third"} -> 6
 */
int Get_Longest_Length(char str[10][1024], int num_movies){
    int longest_length = 0;
    int curr_length = 0;
    for(int i = 0; i < num_movies; i++){
        curr_length = Get_Len_String(str[i]);
        if(longest_length < curr_length){
            longest_length = curr_length;
        }
    }
    return longest_length;
}

/* this function copy characters from src[] to an
 * empty des[] in a certain amount (num)
 */
void Copy_Char_Array(char des[], char src[], int num){
    // if(sizeof(des) < num + 1){
    //     printf("Destination char[] is not large enough!\n");
    // }
    for(int i = 0; i < num; i++){
        des[i] = src[i];
    }
    des[num] = '\0';
}


/* this function take a string and the begin index of destination
 * and the distance to move, move the substring forward (left).
 * Example:
 * Move_String_Left("**test", 0, 2) -> "test"
 */
void Move_String_Left(char str[], int begin_index, int distance){
    int length = Get_Len_String(str);
    for(int i = begin_index; i <= length - distance; i++){
        str[i] = str[i + distance];
    }
}



/* This function takes a string as input and removes 
 * leading and trailing whitespace including spaces
 * tabs and newlines. It also removes multiple internal
 * spaces in a row. Arrays are passed by reference.
 * Example:
 * " Harry   potter " -> "Harry potter"
 */
void Clean_Whitespace(char str[]) {
    //1. trailing whitespace
    int length = Get_Len_String(str);
    //printf("original length: %d\n", length);
    int index_of_trail = length - 1;
    int m;  //as a mark

    //find index of first non whitespace char in reverse order
    for(m = length - 1; m > -1; m--){
        //printf("char: %c,  m: %d\n", str[m], m);
        if(str[m] != ' '){
            index_of_trail = m;
            break;
        }
    }
    //update the str
    if(m == -1){
        index_of_trail = -1;        // m==-1 means all str[] are space ' '
        return;
    }
    str[index_of_trail + 1] = '\0';     //set end element '\0' in right place
    length = Get_Len_String(str);       //update the length of str after deleting trailing space
    /*
    printf("length after removing trail: %d\n", length);
    printf("%s\n", str);
    */
    
    //2. leanding soace
    //find index of the first non whitespace char
    int index_of_lead = 0;
    for(int i = 0; i < length; i++) {
         if(str[i] != ' ') {
             index_of_lead = i;
             break;
         }  
    }
    //printf("index_of_lead: %d\n", index_of_lead);    
    Move_String_Left(str, 0, index_of_lead);        //move afterwards char forward include '\0'
    /*
    //print final length to test
    length = Get_Len_String(str);
    printf("Final length: %d\n", length);
    */

    //3. remove redundant interval space
    length = Get_Len_String(str);       //update the length
    int num_space = 0;
    for(int i = length - 1; i > -1; i--){
        if(str[i] == ' ') {
            ++num_space;
        }else{
            if(num_space > 1){
                Move_String_Left(str, i+1, num_space-1);
            }
            num_space = 0;
        }
    }
    return;
}

/* This function takes a string and makes the first
 * letter of every word upper case and the rest of the
 * letters lower case. Example:
 * "michael jorDan" -> "Michael Jordan"
 */ 
void Fix_Case(char str[]) {
    int length = Get_Len_String(str);
    int space_flag = 1;
    for(int i = 0; i < length; i++) {
        if(str[i] == ' '){
            space_flag = 1;
            continue;
        }
        //if current char is not a space ' '
        else{
            //if the current char is lowercase
            if(str[i] > 96 && str[i] < 123){
                if(space_flag) str[i] -= 32;
            }
            //if the current char is uppercase
            else if(str[i] > 64 && str[i] < 91){
                if(!space_flag) str[i] += 32;
            }
            space_flag = 0;
        }
    }
    return;
}

/* this funtion take a string and make
 * its format fitting the specification.
 * Example:
 * " yesterDay  oncE MORE " -> "Yesterday Once More"
 */
void Title(char str[]){
    Clean_Whitespace(str);
    Fix_Case(str);
    return;
}

/* this function takes a string and returns the 
 * integer equivalent
 */
int String_To_Year(char str[]) {
    // do your work here
    Clean_Whitespace(str);
    int res = atoi(str);
    return res;
}

/* this function takes the name of a 
 * director as a string and removes all but
 * the last name.  Example:
 * "Bucky Badger" -> "Badger"
 */
void Director_Last_Name(char str[]) {
    Clean_Whitespace(str);

    int length = Get_Len_String(str);
    int begin_index = 0;
    //find the index for the fisrt letter of last name
    for(int i = length - 1; i > -1; i--){
        if(str[i] > 64 && str[i] < 91){
            begin_index = i;
            break;
        }
    }
    Move_String_Left(str, 0, begin_index);

    Fix_Case(str);
    return;
}

/* this function takes the a string and returns
 * the floating point equivalent. Example:
 * "6.5" -> 6.5
 */
float String_To_Rating(char str[]) {
    Clean_Whitespace(str);
    float res = atof(str);
    return res;
}


/* this function takes a string representing
 * the revenue of a movie and returns the decimal
 * equivlaent. The suffix M or m represents millions,
 * K or k represents thousands.
* example: "123M" -> 123000000 
*/
long long String_To_Dollars(char str[])  {
    //declare the varaibles will uesd below
    long long dollars = 0;
    long unit = 0;
    int length = 0; 
    int i = 0;

    Clean_Whitespace(str);
    length = Get_Len_String(str);
    i = length - 1;     //index of the mark

    if(str[i] == 'M' || str[i] == 'm') {
        unit = 1000000;
        str[i] = '\0';
    } else if (str[i] == 'K' || str[i] == 'k'){
        unit = 1000;
        str[i] = '\0';
    }
    else {
        unit = 1;
    }
    dollars = (long long)(atof(str) * unit);
    return dollars;
}





/* this function splits csv into 5  string array components cooresponding to 
 * five column in output respectively
 */
void Split_To_Strings(char csv[10][1024], int num_movies, char titles[10][1024], char years[10][1024], char directors[10][1024], char ratings[10][1024], char dollars[10][1024]) {
    //read each string in the csv (each line in .csv file)
    for(int i = 0; i < num_movies; i++){
        //read each char in csv[i]
        char temp[8][1024] = {0};       //temp string array storing infomation in each line (string in csv)
        int stringLenTemp[8] = {0};     //length of each string in current line
        int j = 0;      //the index indicate the columen in final output 
        int k = 0;      //current index in each unit string
        int index = 0;
        //test
        //printf("csv[%d][0]]=%c|\n", i, csv[i][index]);
        while(csv[i][index] != '\0'  && csv[i][index] != '\n'){
            if(csv[i][index] == ','){
                index++;
                j++;
                k = 0;
                continue;
            }
            temp[j][k] = csv[i][index];
            //test
            //printf("temp[%d][%d]=%c|\n", j, k, temp[j][k]);
            index++;
            k++;  
            stringLenTemp[j]++;
        }

        //assign the outcome to destination
        Copy_Char_Array(titles[i], temp[0], stringLenTemp[0]);
        //printf("temp[0]=%s|   title[%d]=%s|\n", temp[0], i, titles[i]);
        Copy_Char_Array(years[i], temp[1], stringLenTemp[1]);
        //printf("temp[1]=%s|   years[%d]=%s|  len=%d\n", temp[1], i, years[i], stringLenTemp[1]);
        Copy_Char_Array(directors[i], temp[3], stringLenTemp[3]);
        Copy_Char_Array(ratings[i], temp[4], stringLenTemp[4]);
        Copy_Char_Array(dollars[i], temp[5], stringLenTemp[5]);   
    }
    return;
}







/* This function takes the array of strings representing 
 * the csv movie data and divides it into the individual
 * components for each movie.
 * Use the above helper functions.
 */
void Split(char csv[10][1024], int num_movies, char titles[10][1024], int years[10], char directors[10][1024], float ratings[10], long long dollars[10]) {
    char char_years[10][1024];
    char char_ratings[10][1024];
    char char_dollars[10][1024];
    Split_To_Strings(csv, num_movies, titles, char_years, directors, char_ratings, char_dollars);    //read the csv[i] each time
    /*
    printf("titles: \n");
    for(int i = 0; i < num_movies; i++ )
    {
        printf("-|%s|-", titles[i]);
        printf("\n");
    }

    printf("years: \n");
    for(int i = 0; i < num_movies; i++ )
    {
        printf("-|%s|-", char_years[i]);
        printf("\n");
    }

    printf("directors: \n");
    for(int i = 0; i < num_movies; i++ )
    {
        printf("-|%s|-", directors[i]);
        printf("\n");
    }

    printf("ratings: \n");
    for(int i = 0; i < num_movies; i++ )
    {
        printf("-|%s|-", char_ratings[i]);
        printf("\n");
    }

    printf("dollars: \n");
    for(int i = 0; i < num_movies; i++ )
    {
        printf("-|%s|", char_dollars[i]);
        printf("\n");
    }
    */


    for(int i = 0; i < num_movies; i++){
        Title(titles[i]);
    }
    for(int i = 0; i < num_movies; i++){
        ratings[i] = String_To_Rating(char_ratings[i]);
        //printf("finalRating[%d] = %f\n", i, ratings[i]);

    }
    
    for(int i = 0; i < num_movies; i++){
        years[i] = String_To_Year(char_years[i]);
        //printf("years[%d] = %d\n", i, years[i]);
    }

    for(int i = 0; i < num_movies; i++){
        dollars[i] = String_To_Dollars(char_dollars[i]);
        //printf("dollars[%d] = %lld\n", i, dollars[i]);
    }


    for(int i = 0; i < num_movies; i++){
        Director_Last_Name(directors[i]);
    }

    return;
}




/* This function prints a well formatted table of
 * the movie data 
 * Row 1: Header - use name and field width as below
 * Column 1: Id, field width = 3, left justified
 * Column 2: Title, field width = lenth of longest movie + 2 or 7 which ever is larger, left justified, first letter of each word upper case, remaining letters lower case, one space between words
 * Column 3: Year, field with = 6, left justified
 * Column 4: Director, field width = length of longest director last name + 2 or 10 (which ever is longer), left justified, only last name, first letter upper case, remaining letters lower case
 * column 5: Rating, field width = 6, precision 1 decimal place (e.g. 8.9, or 10.0), right justified
 * column 6: Revenue, field width = 11, right justified
 */
void Print_Table(int num_movies, char titles[10][1024], int years[10], char directors[10][1024], float ratings[10], long long dollars[10]) {
    //
    int longest_length_director = Get_Longest_Length(directors, num_movies);
    int longest_length_title = Get_Longest_Length(titles, num_movies);
    int field_width_director = 10;
    int field_width_title = 7;
    if(field_width_director < longest_length_director + 2) {
        field_width_director = longest_length_director + 2;
    }
    if(field_width_title < longest_length_title + 2) {
        field_width_title = longest_length_title + 2;
    }
    //printf("field_width_title = %d; field_width_director = %d\n", field_width_title, field_width_director);

    //printf header
    printf("%-3s%-*s%-6s%-*s%6s%11s\n", "Id", field_width_title, "Title", "Year", field_width_director, "Director", "Rating", "Revenue");


    //printf content
    for(int i = 0; i < num_movies; i++){
        printf("%-3d%-*s%-6d%-*s%6.1f%11lld\n", i+1, field_width_title, titles[i],
                years[i], field_width_director, directors[i], ratings[i], dollars[i]);
    }

    // printf("%-3d%-*s%-6d%-*s%6.1f%11lld", num_movies, field_width_title, titles[num_movies-1],
    //         years[num_movies-1], field_width_director, directors[num_movies-1], ratings[num_movies-1], dollars[num_movies-1]);
    //printf last row without '\n'

    return;
}


