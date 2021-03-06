/* 
 * File:   part2_1.c
 * Author: Jose
 *
 * Created on April 28, 2021, 7:26 PM
 */

#include <stdio.h>
#include <stdlib.h>

#include "BOARD.h"
#include "Oled.h"
#include "PING.h"
#include "timers.h"
#include "ToneGeneration.h"

/*
 * 
 */
int main(void)
{
    //initializations
    BOARD_Init();
    OledInit();
    PING_Init();
    TIMERS_Init();
    ToneGeneration_Init();
    
    unsigned int tf; //time of flight variable
    unsigned int d; //distance variable
    char oled_str[100]; //oled_str
    unsigned int t; //time variable
    unsigned int h_buff[50]; //distance buffer
    unsigned int h_avg; //average distance from distance buffer
    unsigned int ph_avg; //previous h_avg value
    unsigned int d_p; //previous distance value
    int h_i = 0; //d_buff index variable
    int h; //variable to store frequency
    int h_p; //previous Hertz variable
    
    while(1){
        OledClear(OLED_COLOR_BLACK);
        ToneGeneration_ToneOn();
        t = TIMERS_GetMilliSeconds();
        
        //get time of flight and distance according to PING sensor
        tf = PING_GetTimeofFlight();
        d = PING_GetDistance();
        
        //if(d > 2000){ //2000mm is our max distance
        //    d = 2000;
        //}
        
        if(((abs(d - d_p)) < 10)){// || ((abs(d - d_p)) > 1000)){//don't track changes less than 10mm in distance
            d = d_p; 
        }
        d_p = d;
        
        //convert distance to frequency
        h = (d*1000)/2000;
        if(h > 1000){ // frequency ceiling
            h = 1000;
        }
            
        if(((abs(h - h_p)) < 10)){//|| ((abs(h - h_p)) > 500)){ //if our change in Hz is greater than 500
            h = h_p;
        }
        h_p = h;
        
        //software filtering
        h_buff[h_i%50] = h; //store current frequency into H_buff
        h_i++; //increment h_buff index variable
        int i; //declare i index to iterate through h_buff
        for(i = 0; i < 50; i++){ //add up all values in h_buff
            h_avg = h_avg + h_buff[i];
        }
        h_avg = h_avg/50; //take average of h_buff values
        
        if(h_avg > 1000){ //h_avg ceiling 
            h_avg = 1000;
        }
        
        if((abs(h_avg - ph_avg)) < 5){ //if our change in Hz is greater than 500
            h_avg = ph_avg;
        }
        ph_avg = h_avg;
        
        ToneGeneration_SetFrequency(h_avg); //set tone frequency
        
        printf("ToF: %u us, D: %u mm\n", tf, d);
        printf("Hz: %d, Avg Hz: %d\n", h, h_avg);
        
        sprintf(oled_str, 
                "ToF: %u us, D: %u mm\n"
                "H: %d, H_avg: %d\n"
                , tf, d, h, h_avg);
        OledDrawString(oled_str);
        OledUpdate();
        
        //wait for a tenth of a second
        while((t%100) != 0){
            t = TIMERS_GetMilliSeconds();
        }
    }
    
    while(1);
}


