#ifndef COMM_H
#include "comm.h"
#endif

#include <stdio.h>

#define SPEED 250000 // define as 250 thousand as it means error in conversion is zero. Refer to https://cache.amobbs.com/bbs_upload782111/files_22/ourdev_508497.html

volatile uint8_t recv_buffer_ptr;// = 0;
volatile unsigned int user_command_ready;// = 0;

//Serial communication output buffer

void handleInput() {

    char command;
    char orientation;

    // only accepting a command character with optional orientation value
    sscanf(recv_buffer,"%c%c",&command, &orientation);

    switch(command) {
      // Acceleration
      case 'A':
      case 'a':
        break;       
      // Everything 
      case 'E':        
      case 'e':
        break;
      // Gyroscope
      case 'G':
      case 'g':
        break;
      // Magnetometer
      case 'M':        
      case 'm':
        break;
    }

    // reset the buffer
    recv_buffer_ptr = 0;
    //memset(recv_buffer, 0, RECEIVE_BUFFER_LENGTH);
    recv_buffer[0] = 0;
    recv_buffer[1] = 0;
    recv_buffer[2] = 0;
    recv_buffer[3] = 0;

    // set flag that ready for more
    user_command_ready = 0;
}
//Function that takes care of configurating the serial communication
void setupUART(void) {
  
  recv_buffer_ptr = 0;
  user_command_ready = 0;
  *menu = "MENU\n\r";

  
  UBRR1 = ((F_CPU/(16*SPEED)) - 1);

  UCSR1C |= (1 << UCSZ11) | (1 << UCSZ10);    // 8 bit char size
  UCSR1B |= (1 << TXEN1);   // enable transmit

  UCSR1B |= (1 << RXEN1);     // enable receive
  UCSR1B |= (1 << RXCIE1);     // enable interrupt on data receipt
}

void sendChar(char c) {
  while((UCSR1A & (1<<UDRE1)) == 0);  // wait while data register is NOT empty
  UDR1 = c;
}

void sendString(char *s) {
  while(*s != 0x00) {
    sendChar(*s);
    s++;
  }
  sendChar('\r');
}

ISR(USART1_RX_vect) {

    // BE CAREFUL with this. It is an ISR and will interfere with your
    // PCINT if it takes too long.

    uint8_t ch = UDR1;

    //Is user pressed 'Enter' it means that the user has finished typing the command
    if (ch == 13 || (recv_buffer_ptr >= RECEIVE_BUFFER_LENGTH)) {
        user_command_ready = 1;
    }

    //User deletes a character - not a case for machine input
    /*else if (ch == 8) {
        if (recv_buffer_ptr >= 1)
            --recv_buffer_ptr;
        recv_buffer[recv_buffer_ptr] = 0;
    }*/

    //Only store alphanumeric symbols, space, the dot, plus and minus sign 
    // not required for machine input as values will be always pre known and correct, so reduce delay on embedded device end
    /*else if
    ( (ch == ' ') || (ch == '.') || (ch == '+') || (ch == '-') ||
    ((ch >= '0') && (ch <= '9')) ||
    ((ch >= 'A') && (ch <= 'Z')) ||
    ((ch >= 'a') && (ch <= 'z')) ) {
        recv_buffer[recv_buffer_ptr] = ch;
        ++recv_buffer_ptr;
    }*/
}
