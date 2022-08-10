/* Assignment: Greendine Technologies
Candidate: Nikhil Sekhar */

// Imports
#include <stdio.h>
#include <stdint.h>
//Global Definitions

uint8_t  g_ReadDIpinSts = 0b00100000;  //8 bits, each represents 1 of the 8 digital inputs.
uint8_t  g_AppDIpinSts  = 0b00000000; // This is to be updated via the ISR
uint8_t counter = 0;
/**
 * @brief Digital Input Sampling function
 * 
 * No arguments, updates global g_AppDIpinSts var to match g_ReadDIpinsSts
 * Runs every 100ms, 
 * updates values of 8 digital inputs, corresponding to 
 * 8 bits in g_AppDIpinSts.
 * Active bits in g_AppDIpinSts stays same (consistent) for 10 calls (reset on the 11th call)
 *  
 * Real time status of digital Pins in g_ReadDIpinSts (Assuming this is updated in some ISR, elsewhere)
 * 
 * 
 */



int ISR_DIsampling(){
    if (counter != 10){
       /**
         * 
         * Counter hasn't reached 10, therefore just 
         * update g_AppDIpinSts to match what is there in g_ReadDIpinSts
         * without overrighting currently set bits (1s) to 0.
         * 
         * Update counter, 
         *
         * Return
         */

        g_AppDIpinSts = g_AppDIpinSts | g_ReadDIpinSts;
        counter++; 
        return g_AppDIpinSts;

    }
    else {
         /*
        * 10 ISR calls made, reset g_AppDIpinSts and update it with real-time values
        */
       g_AppDIpinSts = g_AppDIpinSts & 0;              //Reseting all DI to zero
       g_AppDIpinSts = g_AppDIpinSts | g_ReadDIpinSts; // "Or-ing" the current values into the required 
       counter = 0;                                    //resetting counter
       return g_AppDIpinSts;                           //To conform to given prototype
       /*
       *Ideally for the function to be reentrant, we should avoid 
       accessing global variables, this should especially execised 
       within ISRs. However this function will adhere to the assignment
       requirements. Kindly send me feedback if I am wrong on this.
       */
    }
}
