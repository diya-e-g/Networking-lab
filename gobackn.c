#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define LOSS_PROB 60
#define WINDOW 5


int send(int i){
    printf("Sending frame%d....\n", i);
    sleep(1);
    
    if(LOSS_PROB > rand()%100){
        printf("Frame lost\n");
        return 0;
    }
    printf("Send frame%d successfully\n", i);
}

int ack(int i){
    printf("Sending ack%d....\n", i);
    sleep(1);
    
    if(LOSS_PROB > rand()%100){
        printf("Ack lost\n");
        return 0;
    }
    printf("Send ack%d successfully\n", i);
}

int main(){
    int n = 10;
    int base = 0;
    int ackd[n];
    memset(ackd, 0, sizeof(ackd));
    while(base<n){
        for(int i=base; i<base+WINDOW && i < n; i++){
            if(send(i) && ack(i)){
                ackd[i] = 1;
            }
        }
        
        while(base<n && ackd[base]) base++;
    }
}
