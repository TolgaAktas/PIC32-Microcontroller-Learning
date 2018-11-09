#include "uart_communication.h"


void initUART(){


}

unsigned int readUART(char* msg, int length){
    char data = 0;
  int complete = 0, num_bytes = 0;
  
  while (!complete) {                           // loop until newline
    if (U3STAbits.URXDA) { // if data is available
      data = U3RXREG;      // read the data
      if ((data == '\n') || (data == '\r')) {
        complete = 1;
      } else {
        msg[num_bytes] = data;
        ++num_bytes;
        // roll over if the array is too small
        if (num_bytes >= length) {
          num_bytes = 0;
        }
      }
    }
  }
  // end the string
  message[num_bytes] = '\0';

}

unsigned int writeUART(const char* string){
    
 while (*string != '\0') {
    while (U3STAbits.UTXBF) {
      ; // wait until tx buffer isn't full
    }
    U1TXREG = *string;
    ++string;
  }
    
}
