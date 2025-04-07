#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define FAIL 30
int main()
{
    int no_of_frames, window;
    printf("Enter the number of frames to be sent: ");
    scanf("%d",&no_of_frames);
    printf("Enter the window size:");
    scanf("%d",&window);
    int base=1;
    while(base<=no_of_frames)
    {
        for(int i=base;i<no_of_frames && i<base+window;i++)
        {
            printf("Sender: Frame %d is sent.\n",i);
            sleep(1);
        }
        int failed_frame=0;
        for(int i=base;i<no_of_frames && i<base+window;i++)
        {
            if(rand()%100>FAIL)
            {
                printf("Receiver: ACK for frame %d received\n",i);
            }
            else{
                printf("Receiver: ACK for frame %d is lost. Go back n triggered\n",i);
                failed_frame=i;
                break;
            }
        }
        if(failed_frame)
        {
            base=failed_frame;
            printf("Retransmitting from frame %d\n",base);
            sleep(1);
        }
        else{
            base+=window;
            printf("Sliding window to %d\n",base);
        }
    }
    printf("All the frames are successfully sent.\n");
    return 0;

}
