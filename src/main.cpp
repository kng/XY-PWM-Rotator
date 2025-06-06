#include <Arduino.h>
#include <VarSpeedServo.h> 
#include "config.h"
#define BUF_SIZE 16 // max receiving buffer, only needs to fit one command

// Subset of GS-232B compatible protocol implemented

VarSpeedServo servo_x, servo_y;
char buf[BUF_SIZE], resp[BUF_SIZE], *ptr;
int pos=0;
float req_el=90, req_az=180, rads=0.01745329, degs=57.29578, req_speed=SPEED;

void setup() {
  Serial.begin(9600);
  servo_x.attach(X_PIN, X_MIN, X_MAX);  
  servo_y.attach(Y_PIN, Y_MIN, Y_MAX);
  servo_x.write(90); // point straight up
  servo_y.write(90);
}

void parse_command(){
  if(buf[0] == 'w' || buf[0] == 'W'){ // set position
    ptr = strtok(buf+1, " ");
    if(ptr == NULL){ // only az
      req_az = atof(buf+1);
      req_el = 0;
    }else{ // az & el
      req_az = atof(buf+1);
      ptr = strtok(NULL, " ");
      req_el = atof(ptr);
    }
    servo_x.write((sin(req_az*rads)*cos(max(req_el,EL_MIN)*rads)) * 90 + 90, req_speed);
    servo_y.write((cos(req_az*rads)*cos(max(req_el,EL_MIN)*rads)) * 90 + 90, req_speed);
    Serial.println();
  }else if(buf[0] == 'c' || buf[0] == 'C'){ // get position
    if(buf[1] == '2'){ // az & el
      sprintf(resp,"AZ=%03dEL=%03d", int(req_az), int(req_el));
    }else{ // only az
      sprintf(resp,"AZ=%03d", int(req_az));
    }
    Serial.println(resp);
  }else if(buf[0] == 'b' || buf[0] == 'B'){ // get el
    sprintf(resp,"EL=%03d", int(req_el));
    Serial.println(resp);
  }else if(buf[0] == 's' || buf[0] == 'S' || buf[0] == 'e' || buf[0] == 'E'){ // all/az stop
    servo_x.stop();
    servo_y.stop();
    Serial.println();
  }else if(buf[0] == 'z' || buf[0] == 'Z'){ // N/S center
    Serial.println("N Center"); // fixed
  }else if(buf[0] == 'x' || buf[0] == 'x'){ // set speed
    int s=buf[1] - '0';
    if(s>0 && s<5){
      req_speed=s*SPEED/4;
      sprintf(resp,"Speed X%1i", s);
      Serial.println(resp);
    }else{
      Serial.println("?>");
    }
  }else{
    Serial.println("?>");
  }
}

void loop(){
  if(Serial.available()>0){
    buf[pos]=(char)Serial.read();
    if((buf[pos] == '\r' || buf[pos] == '\n')){ // only 0x0D in the manual
      buf[pos]=0; // asciiz instead of linefeed
      if(pos>0)
        parse_command();
      pos=0;
    }else{
      pos++;
      if(pos==BUF_SIZE){
        Serial.println("?>");
        pos=0; // overflow, start over
      }
    }
  }
}
