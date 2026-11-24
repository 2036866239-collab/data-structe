#include <stdio.h>
int weight[] = {2,3,4}
int n = sizeof(weight) / sizeof(weight[0]);

int canfill(int i,int rest){

    if (rest ==0){
        return 1;
    }

    if(i == n){
        return 0;
    }

    if(canfill(i+1,rest)){
        return 1;
    }

    if(weight[i] <=rest){
        if(canfill(i+1,rest-weight[i])){
            return 1;
        }
    }
    return 0;
}