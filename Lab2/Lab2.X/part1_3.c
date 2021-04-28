/* 
 * File:   part1_3.c
 * Author: Jose
 *
 * Created on April 27, 2021, 2:04 AM
 */

#include <stdio.h>
#include <stdlib.h>

#include "BOARD.h"
#include "Oled.h"
#include "pwm.h"
#include "QEI.h"
#include "timers.h"

#define RED_PIN PWM_PORTY04
#define GREEN_PIN PWM_PORTY12
#define BLUE_PIN PWM_PORTZ06

/*
 * 
 */
int main(void)
{
    //initializations
    BOARD_Init();
    OledInit();
    PWM_Init();
    QEI_Init();
    TIMERS_Init();
    
    //set PWM to light led
    PWM_AddPins(RED_PIN); //pin 9 (RED)
    PWM_AddPins(GREEN_PIN); //pin 5 (GREEN)
    PWM_AddPins(BLUE_PIN); //pin 3 (BLUE)
    
    //integers to store Duty Cycle of RGB
    int R_DC = 0;
    int G_DC = 0;
    int B_DC = 1000;
    int q; //store QEI_count
    int d; //store degrees corresponding to QEI_count
    char oled_str[100];
    float R;
    float G;
    float B;

    while(1){ //infinite loop
        OledClear(OLED_COLOR_BLACK);
        q = QEI_GetPosition(); //QEI_count
        d = abs((q*15)%360); //angle of revolution of QEI
        
        //check degrees and set color accordingly
        if(d == 0){ //yellow
            R_DC = 0;
            G_DC = 0;
            B_DC = 1000;
        }else if(d == 15){ //yellow-green
            R_DC = 250;
            G_DC = 0;
            B_DC = 1000;
        }else if(d == 30){ //spring green
            R_DC = 500;
            G_DC = 0;
            B_DC = 1000;
        }else if(d == 45){
            R_DC = 750;
            G_DC = 0;
            B_DC = 1000;
        }else if(d == 60){ //green
            R_DC = 1000;
            G_DC = 0;
            B_DC = 1000;
        }else if(d == 75){
            R_DC = 1000;
            G_DC = 0;
            B_DC = 750;
        }else if(d == 90){ //turquoise
            R_DC = 1000;
            G_DC = 0;
            B_DC = 500;
        }else if(d == 105){
            R_DC = 1000;
            G_DC = 0;
            B_DC = 250;
        }else if(d == 120){ //cyan
            R_DC = 1000;
            G_DC = 0;
            B_DC = 0;
        }else if(d == 135){
            R_DC = 1000;
            G_DC = 250;
            B_DC = 0;
        }else if(d == 150){ //ocean
            R_DC = 1000;
            G_DC = 500;
            B_DC = 0;
        }else if(d == 165){
            R_DC = 1000;
            G_DC = 750;
            B_DC = 0;
        }else if(d == 180){ //blue
            R_DC = 1000;
            G_DC = 1000;
            B_DC = 0;
        }else if(d == 195){
            R_DC = 750;
            G_DC = 1000;
            B_DC = 0;
        }else if(d == 210){ //violet
            R_DC = 500;
            G_DC = 1000;
            B_DC = 0;
        }else if(d == 225){
            R_DC = 250;
            G_DC = 1000;
            B_DC = 0;
        }else if(d == 240){ //magenta
            R_DC = 0;
            G_DC = 1000;
            B_DC = 0;
        }else if(d == 255){ 
            R_DC = 0;
            G_DC = 1000;
            B_DC = 250;
        }else if(d == 270){ //raspberry
            R_DC = 0;
            G_DC = 1000;
            B_DC = 500;
        }else if(d == 285){
            R_DC = 0;
            G_DC = 1000;
            B_DC = 750;
        }else if(d == 300){ //red
            R_DC = 0;
            G_DC = 1000;
            B_DC = 1000;
        }else if(d == 315){
            R_DC = 0;
            G_DC = 750;
            B_DC = 1000;
        }else if(d == 330){ //orange
            R_DC = 0;
            G_DC = 500;
            B_DC = 1000;
        }else if(d == 345){
            R_DC = 0;
            G_DC = 250;
            B_DC = 1000;
        }else if(d == 360){ //yellow
            R_DC = 0;
            G_DC = 0;
            B_DC = 1000;
        } 
        
        //active low since we are sinking current through LED
        PWM_SetDutyCycle(RED_PIN, R_DC); //R
        PWM_SetDutyCycle(GREEN_PIN, G_DC); //G
        PWM_SetDutyCycle(BLUE_PIN, B_DC); //B
        
        R = R_DC/1000;
        G = G_DC/1000;
        B = B_DC/1000;
        
        sprintf(oled_str, 
                "RGB: %.2f %.2f %.2f\n"
                "QEI degrees: %d\n"
                , R, G, B, d);
        
        OledDrawString(oled_str);
        OledUpdate();
    }

    while(1);
}

