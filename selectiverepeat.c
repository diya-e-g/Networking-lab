#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define LOSS 20

int send(int frame)
{
    printf("Sender: Sending frame %d..\n",frame);
    sleep(1);
    int random=rand()%100;
    if(random<LOSS)
    {
        printf("Frame %d lost during transmission..\n",frame);
        return 0;
    }
    else{
        printf("Frame %d successfully sent..\n",frame);
        return 1;
    }
}

int send_ack(int frame)
{
    printf("Receiver: Sending ACK for frame %d..\n",frame);
    sleep(1);
    int random=rand()%100;
    if(random<LOSS)
    {
        printf("ACK for frame %d lost during transmission..\n",frame);
        return 0;
    }
    else{
        printf("ACK for frame %d successfully sent..\n",frame);
        return 1;
    }
}

int main()
{
    srand(time(0));
    int no_of_frames, window;
    
    printf("Enter the total number of frames to be sent:");
    scanf("%d",&no_of_frames);
    int sent_frames[no_of_frames];
    int receive_ack[no_of_frames];
    for(int i=0;i<no_of_frames;i++)
    {
        sent_frames[i]=0;
        receive_ack[i]=0;

    }
    printf("Enter the window size: ");
    scanf("%d",&window);
    int base=0;
    while(base<no_of_frames)
    {
        for(int i=base;i<base+window && i<no_of_frames;i++)
        {
            if(!sent_frames[i])
            {
                sent_frames[i]=send(i);
            }
        }
        for(int i=base;i<base+window && i<no_of_frames;i++)
        {
            if(sent_frames[i] && !receive_ack[i])
            {
                receive_ack[i]=send_ack(i);
            }
        }

        while(base<no_of_frames && receive_ack[base])
        {
            printf("Sliding window forward. %d fully acknowledged.\n",base);
            base++;
        }
    }
    printf("All the frames are sent and acknowledged");

    return 0;
}
