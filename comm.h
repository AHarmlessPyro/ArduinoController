#ifndef COMM_H
#define COMM_H
#endif

#include <avr/io.h>
#include <avr/interrupt.h>

#define printMenu() sendString("A,a,E,e,G,g,M,m\r\n");

//Length of output bufer used for serial communication
#define OUTPUT_BUFFER_LENGTH 300
//Length of input buffer used to store user configuration option
#define RECEIVE_BUFFER_LENGTH 4

//static volatile char output_buffer[OUTPUT_BUFFER_LENGTH];
static volatile char recv_buffer[RECEIVE_BUFFER_LENGTH];
//volatile unsigned int *user_token;

//Global constant string specifying menu options:
static char *menu ;

char sensor[1];

char orient[1];

extern void handleInput();

extern void setupUART(void);

extern void sendString(char *s);
