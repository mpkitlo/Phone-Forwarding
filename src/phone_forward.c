#include "phone_forward.h"
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h> 

#define NUMBER_OF_DIGITS 12

/**
 * To jest struktura przechowująca przekierowania numerów telefonów.
 */
struct PhoneForward{
    ///- To jest 12 elemntowa tablica wskaników reprezentujaca synów
    ///- danego wierzchołka reprezentują kolejno liczby od 0 do 11.
    PhoneForward *children[NUMBER_OF_DIGITS];
    ///- To jest wskaźnik na przekierowanie w danym wierzchołku.
    char *forwarding;
    ///- To jest zmienna przechowująca głebokość drzewa.
    size_t depth;
};

/**
 * To jest struktura przechowująca ciąg numerów telefonów.
 */
struct PhoneNumbers{
    ///- To tablica napisow.
    char **list;
    ///- To jest zmienna przechowująca wielkość tablicy.
    size_t size;
    ///- To jest zmienna przechowująca nastepne wolne miejsce w tablicy do uzycia.
    size_t used;
};

bool check_if_prefix(char * num1, char * num2){
    size_t length_num1 = num_length(num1);
    size_t length_num2 = num_length(num2);

    if(length_num1 > length_num2){return false;}

    for(size_t i = 0;i < length_num1;i++){
        if(num1[i] != num2[i]){
            return false;
        }
    }
    return true;
}

char * str_coppy(char * num){
    size_t length = num_length(num);
    char * temp = calloc(length+1,sizeof(char));

    if(temp == NULL){return temp;}

    for(size_t i = 0;i < length;i++){
        temp[i] = num[i];
    }

    temp[length] = '\0';
    return temp;
}

bool strings_equal(char * num1, char * num2){
    size_t num1_length = num_length(num1);
    size_t num2_length = num_length(num2);
    if(num1_length != num2_length){
        return false;
    }
    for(size_t i = 0;i < num1_length;i++){
        if(num1[i] != num2[i]){
            return false;
        }
    }
    return true;
    
}

char * compare_strings(char * num1, char * num2){
    size_t num1_length = num_length(num1);
    size_t num2_length = num_length(num2);
    size_t length = num2_length;

    if(num1_length < num2_length){
        length = num1_length;
    }
    
    for(size_t i = 0;i < length;i++){
        if(return_idx(num1[i]) < return_idx(num2[i])){
            return num1;
        }
        else if(return_idx(num1[i]) > return_idx(num2[i])){
            return num2;
        }
    }
    
    if(num1_length < num2_length){
        return num1;
    }
    return num2;
}

int return_idx(char digit){
    if('0' <= digit && digit <= '9'){
        return digit - '0';
    }
    if(digit == '*'){
        return 10;
    }
    return 11;
}

char return_char(int idx){
    if(0 <= idx && idx <= 9){
        char result = '0'+idx;
        return result;
    }
    if(idx == 10){
        return '*';
    }
    return '#';
}

bool is_digit(char digit){
    if(('0' <= digit && digit <= '9') || digit == '*' || digit == '#'){
        return true;
    }
    return false;
}

size_t num_length(char *num){
    size_t i = 0;
    while(num[i] != '\0'){ 
        i++;
    }
    return i;
}

bool check_if_num(char const *num){
    if(num == NULL){
        return false;
    }
    if(num[0] == '\0'){
        return false;
    }
    int i = -1;
    while(num[++i] != '\0'){
        if(!is_digit(num[i])){
            return false;
        }
    }
    return true;
}

PhoneNumbers * phnumNew(PhoneNumbers * pnum){
    if(pnum != NULL){
        char ** temp = calloc(1,sizeof(char *));
        if(temp == NULL){
            return NULL;
        }
        pnum->list = temp;
        pnum->list[0] = NULL;
        pnum->size = 1;
        pnum->used = 0;
    }

    return pnum;
}

PhoneNumbers * phnumAdd(PhoneNumbers *pnum ,char *num){
    if(pnum != NULL){
        if(pnum->size == pnum->used){
            char **temp;
            pnum->size *= 2;
            temp = realloc(pnum->list, sizeof(char *)*pnum->size);
            if(temp == NULL){
                free(temp);
                return NULL;
            }
            else{
                pnum->list = temp;
                for(size_t i = pnum->used;i<pnum->size;i++){
                    pnum->list[i] = NULL;
                }
            }
        }
        
        size_t i = 0;
        while(i < pnum->used && compare_strings(pnum->list[i], num) == pnum->list[i]){
            i++;
        }

        for(size_t w = pnum->used;i < w;w--){
            pnum->list[w] = pnum->list[w-1];
        }
        
        pnum->list[i] = num;
        pnum->used++;
    }
    return pnum;
}

void phnumDelete(PhoneNumbers *pnum){
    if(pnum != NULL){
        for(size_t i = 0; i<pnum->used; i++){
            free(pnum->list[i]);
            pnum->list[i] = NULL;
        }
        if(pnum->list != NULL){
            free(pnum->list);
            pnum->list = NULL;
        }
        if(pnum != NULL){
            free(pnum);
            pnum = NULL;
        }
    }
}

char const * phnumGet(PhoneNumbers const *pnum, size_t idx){
    if(pnum != NULL && idx < pnum->size && pnum->list[idx] != NULL){
        return pnum->list[idx];
    }
    return NULL;
}

PhoneForward * phfwdNew(void){
    PhoneForward *temp = calloc(1,sizeof(PhoneForward));

    if(temp == NULL){
        return NULL;
    }

    temp->forwarding = NULL;
    temp->depth = 0;

    for(int i = 0;i<NUMBER_OF_DIGITS;i++){
        temp->children[i] = NULL;
    }

    return temp;
}

void phfwdDelete(PhoneForward *pf){
    if(pf == NULL){return;}

    for(int i = 0;i < NUMBER_OF_DIGITS; i++){
        if(pf->children[i] != NULL){
            phfwdDelete(pf->children[i]);
            free(pf->children[i]);
            pf->children[i] = NULL;
        }
    }
    
    if(pf->forwarding != NULL){
        free(pf->forwarding);
        pf->forwarding = NULL;
    }

    if(pf->depth == 0){
        free(pf);
    }
}

bool phfwdAdd(PhoneForward *pf, char const *num1, char const *num2){
    if(pf == NULL || !check_if_num(num1) || !check_if_num(num2)){return false;}
    if(num1 == NULL || num2 == NULL){return false;}

    size_t num1_length = num_length((char *)num1);
    size_t num2_length = num_length((char *)num2);

    if(num1_length == num2_length){
        bool spr = false;
        for(size_t i = 0;i < num1_length;i++){
            if(num1[i] != num2[i]){
                spr = true;
                break;
            }
        }
        if(!spr){
            return spr;
        }
    }
    
    for(size_t i = 0;i < num1_length;i++){
        int idx = return_idx(num1[i]);
        if(pf->children[idx] == NULL){

            pf->children[idx] = phfwdNew();

            if(pf->children[idx] == NULL){return false;}

            pf->children[idx]->depth = pf->depth+1;
        }
        pf = pf->children[idx];
    }
    
    char * temp = str_coppy((char *)num2);

    if(temp == NULL){
        return false;
    }

    if(pf->forwarding != NULL){free(pf->forwarding);}

    pf->forwarding = temp;

    return true;
}

void phfwdRemove(PhoneForward *pf, char const *num){
    
    if(num == NULL || !check_if_num(num) || num_length((char *)num) == 0){
        return;
    }
    
    while(pf != NULL && num[pf->depth+1] != '\0'){
        int idx = return_idx(num[pf->depth]);
        pf = pf->children[idx];
    }

    if(pf != NULL){
        int idx = return_idx(num[pf->depth]);
        phfwdDelete(pf->children[idx]);
        free(pf->children[idx]);
        pf->children[idx] = NULL;
    }
        
}

PhoneNumbers * phfwdGet(PhoneForward const *pf, char const *num){
    if(pf == NULL){return NULL;}

    PhoneNumbers * result = calloc(1,sizeof(PhoneNumbers));

    if(result == NULL){return NULL;}

    result = phnumNew(result);

    if(num == NULL || !check_if_num(num)){
        return result;
    }

    char * temp = NULL;
    char * forward = NULL;
    size_t i_forwarding = 0;
    size_t i = 0;

    while(is_digit(num[i]) && pf->children[return_idx(num[i])] != NULL){
        int idx = return_idx(num[i]);
        pf = pf->children[idx];
        if(pf->forwarding != NULL){
            forward = pf->forwarding;
            i_forwarding = i;
        }
        i++;
    }
    i_forwarding++;
    if(forward == NULL){
        temp = str_coppy((char *)num);
        if(temp == NULL){return NULL;}

        result = phnumAdd(result, temp);
        return result;
    }
    size_t length1 = num_length((char *)num);
    size_t length2 = num_length(forward);

    size_t sum = length1 + length2 - i_forwarding;
    temp = calloc((sum+1),sizeof(char));
    if(temp == NULL){return NULL;}

    i = 0;
    while(is_digit(forward[i])){
        temp[i] = forward[i];
        i++;        
    }
    
    while(num[i_forwarding] != '\0'){
        temp[i] = num[i_forwarding];
        i++;i_forwarding++;
    }
    temp[i] = '\0';
    result = phnumAdd(result, temp);
    return result;
}

void pom_phfwdReverse(PhoneForward const *pf, PhoneNumbers *result, char const * path_number, char const *num){
    
    if(pf->forwarding != NULL){
        if(check_if_prefix(pf->forwarding, (char *)num)){
            size_t actual_length = num_length((char *)path_number) + num_length((char *)num) - num_length(pf->forwarding);
            char * resultAdd = calloc(actual_length+2, sizeof(char));
            size_t i_length = num_length((char *)path_number);

            for(size_t i = 0;i < i_length;i++){
                resultAdd[i] = path_number[i];
            }
            
            size_t i_forwarding = num_length(pf->forwarding);

            while(num[i_forwarding] != '\0'){
                resultAdd[i_length] = num[i_forwarding];
                i_length++;
                i_forwarding++;
            }

            resultAdd[i_length] = '\0';
            
            bool spr = false;

            for(size_t i = 0;i < result->used;i++){
                spr = strings_equal(result->list[i], resultAdd);
            }
            if(!spr){
                result = phnumAdd(result, resultAdd);
            }
            else{
                free(resultAdd);
            }
        }
    }
    
    
    for(int i = 0;i < NUMBER_OF_DIGITS; i++){
        if(pf->children[i] != NULL){

            char temp_char = return_char(i);
            char * temp_number;
            if(path_number[0] == '\0'){
                temp_number = calloc(2, sizeof(char));
                temp_number[0] = temp_char;
                temp_number[1] = '\0';
            }
            else{
                temp_number = str_coppy((char *)path_number);
                size_t length = num_length(temp_number);
                temp_number = realloc(temp_number, (length+2)*sizeof(char));
                temp_number[length] = temp_char;
                temp_number[length + 1] = '\0';
            }
            
            pom_phfwdReverse(pf->children[i], result, temp_number, num);
            free(temp_number);
        }
    }
    
}

PhoneNumbers * phfwdReverse(PhoneForward const *pf, char const *num){

    if(pf == NULL){
        return NULL;
    }

    PhoneNumbers * result = calloc(1, sizeof(PhoneNumbers));
    result = phnumNew(result);

    if(!check_if_num((char *)num) || num == NULL){

        return result;
    }

    char * temp = str_coppy((char *)num);
    
    if(temp == NULL){
        return NULL;
    }

    result = phnumAdd(result, temp);

    char * pom = calloc(1, sizeof(char));
    pom[0] = '\0';

    pom_phfwdReverse(pf, result, pom, temp);

    free(pom);

    return result;
}

PhoneNumbers * phfwdGetReverse(PhoneForward const *pf, char const *num){

    if(pf == NULL){
        return NULL;
    }

    PhoneNumbers * result = calloc(1, sizeof(PhoneNumbers));
    result = phnumNew(result);

    if(!check_if_num((char *)num) || num == NULL){

        return result;
    }

    PhoneNumbers * pom = phfwdReverse(pf, num);

    for(size_t i = 0;i < pom->used;i++){
        PhoneNumbers * test = phfwdGet(pf, pom->list[i]);

        if(phnumGet(test, 0) != NULL){       
            char * stringComp = str_coppy((char *)phnumGet(test, 0));
            char * stringAdd = str_coppy((char *)phnumGet(pom, i));
            int idx = 0;
            while(stringComp[idx] != '\0' && num[idx] != '\0' && stringComp[idx] == num[idx]){
                idx++;
            }
            if(stringComp[idx] == '\0' && num[idx] == '\0'){
                result = phnumAdd(result, stringAdd);
            }
            else{
                free(stringAdd);
            }
            free(stringComp);
        }

        phnumDelete(test);
    }

    phnumDelete(pom);

    return result;
}

