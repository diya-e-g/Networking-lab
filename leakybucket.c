#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define WINDOW_SIZE 4
#define TOTAL_FRAMES 10
#define LOSS_PROBABILITY 20

int send_frame(int frame_number) {
    printf("Sending frame %d...\n", frame_number);
    sleep(1);
    int rand_value = rand() % 100;
    if (rand_value < LOSS_PROBABILITY) {
        printf("Frame %d lost during transmission!\n", frame_number);
        return 0;
    }
    printf("Frame %d sent successfully.\n", frame_number);
    return 1;
}

int receive_ack(int frame_number) {
    printf("Receiving acknowledgment for frame %d...\n", frame_number);
    sleep(1);
    int rand_value = rand() % 100;
    if (rand_value < LOSS_PROBABILITY) {
        printf("Acknowledgment for frame %d lost!\n", frame_number);
        return 0;
    }
    printf("Acknowledgment for frame %d received.\n", frame_number);
    return 1;
}

void go_back_n_arq() {
    int base = 0;

    while (base < TOTAL_FRAMES) {
        int i;
        for (i = base; i < base + WINDOW_SIZE && i < TOTAL_FRAMES; i++) {
            if (!send_frame(i)) {
                printf("Retransmitting from frame %d due to loss.\n", base);
                break;
            }
        }
        
        for (int j = base; j < i; j++) {
            if (!receive_ack(j)) {
                printf("Acknowledgment lost for frame %d, retransmitting from frame %d.\n", j, base);
                break;
            }
            base++;
        }
    }
    printf("All frames sent and acknowledged successfully.\n");
}

int main() {
    srand(time(0));
    go_back_n_arq();
    return 0;
}
