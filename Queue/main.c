#include <stdio.h>

#include "queue.h"

int main (int argc, char **argv) {
    Queue_Init (DEFAULT_QUEUE_SIZE);

    uint8_t message[4] = { 0x09, 0x90, 0x00, 0x40 };
    Enqueue (message);

    message[0] = 0x08;
    message[1] = 0x80;
    message[2] = 0x00;
    message[3] = 0x40;
    Enqueue (message);

    Print_Queue ();

    Dequeue ();
    printf ("\n\n");
    Print_Queue ();

    return 0;
}
