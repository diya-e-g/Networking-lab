#include <stdio.h>

void leaky_bucket(int bucket_capacity, int leak_rate, int num_of_packets, int packets[])
{
    int bucket = 0;
    printf("Time\tIncoming\tBucket\t\tLeaked\tRemaining\n");

    for (int i = 0; i < num_of_packets; i++)
    {
        printf("%d\t%d\t\t", i + 1, packets[i]);
        bucket += packets[i];

        if (bucket > bucket_capacity)
        {
            printf("%d (Overflowed, Dropped %d)\t", bucket_capacity, bucket - bucket_capacity);
            bucket = bucket_capacity;
        }
        else
        {
            printf("%d\t\t", bucket);
        }

        int leaked = (bucket >= leak_rate) ? leak_rate : bucket;
        bucket -= leaked;

        printf("%d\t%d\n", leaked, bucket);
    }

    int time = num_of_packets + 1;
    while (bucket > 0)
    {
        int leaked = (bucket >= leak_rate) ? leak_rate : bucket;
        printf("%d\t%d\t\t%d\t\t%d\t%d\n", time, 0, bucket, leaked, bucket - leaked);
        bucket -= leaked;
        time++;
    }
}

int main()
{
    int num_of_packets, bucket_capacity, leak_rate;

    printf("Enter the total number of packets: ");
    scanf("%d", &num_of_packets);

    printf("Enter the bucket capacity: ");
    scanf("%d", &bucket_capacity);

    printf("Enter the leak rate: ");
    scanf("%d", &leak_rate);

    int packets[num_of_packets];

    printf("Enter the packet sizes:\n");
    for (int i = 0; i < num_of_packets; i++)
    {
        scanf("%d", &packets[i]);
    }

    leaky_bucket(bucket_capacity, leak_rate, num_of_packets, packets);

    return 0;
}
