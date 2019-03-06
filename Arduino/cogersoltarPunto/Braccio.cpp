/*
 Braccio.cpp - board library Version 2.0
 Written by Andrea Martino and Angelo Ferrante

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "Braccio.h"

_Braccio Braccio;

//Initialize Braccio object
_Braccio::_Braccio(int M1, int M2, int M3, int M4, int M5, int M6): 
  M1_(M1), M2_(M2), M3_(M3), M4_(M4), M5_(M5), M6_(M6){}

//MODIFICADORES
void _Braccio::M1(int valor){ ServoMovement(10,valor,M2_,M3_,M4_,M5_,M6_);}
void _Braccio::M2(int valor){ ServoMovement(10,M1_,valor,M3_,M4_,M5_,M6_);}
void _Braccio::M3(int valor){ ServoMovement(10,M1_,M2_,valor,M4_,M5_,M6_);}
void _Braccio::M4(int valor){ ServoMovement(10,M1_,M2_,M3_,valor,M5_,M6_);}
void _Braccio::M5(int valor){ ServoMovement(10,M1_,M2_,M3_,M4_,valor,M6_);}
void _Braccio::M6(int valor){ ServoMovement(10,M1_,M2_,M3_,M4_,M5_,valor);}

//OBSERVADORES
int _Braccio::M1() const{ return M1_;}
int _Braccio::M2() const{ return M2_;}
int _Braccio::M3() const{ return M3_;}
int _Braccio::M4() const{ return M4_;}
int _Braccio::M5() const{ return M5_;}
int _Braccio::M6() const{ return M6_;}

//MOSTRAR MOTORES
const char* _Braccio::cadena() const{
  static char motores[500];

  sprintf(motores, "M1:%d\nM2:%d\nM3:%d\nM4:%d\nM5:%d\nM6:%d\n",M1_,M2_,M3_,M4_,M5_,M6_);

  return motores;
}

//AGARRAR/SOLTAR OBJETO
void _Braccio::agarrar(){
  M6(73);
}

void _Braccio::soltar(){
  M6(10);
}
/**
 * Braccio initialization and set intial position
 * Modifing this function you can set up the initial position of all the
 * servo motors of Braccio
 * @param soft_start_level: default value is 0 (SOFT_START_DEFAULT)
 * You should set begin(SOFT_START_DISABLED) if you are using the Arm Robot shield V1.6
 * SOFT_START_DISABLED disable the Braccio movements
 */
unsigned int _Braccio::begin(int soft_start_level) {
	//Calling Braccio.begin(SOFT_START_DISABLED) the Softstart is disabled and you can use the pin 12
	if(soft_start_level!=SOFT_START_DISABLED){
		pinMode(SOFT_START_CONTROL_PIN,OUTPUT);
		digitalWrite(SOFT_START_CONTROL_PIN,LOW);
	}
  
	// initialization pin Servo motors
	base.attach(11);
	shoulder.attach(10);
	elbow.attach(9);
	wrist_rot.attach(6);
	wrist_ver.attach(5);
	gripper.attach(3);
        
	//For each step motor this set up the initial degree
  base.write(M1_);
  shoulder.write(M2_);
  elbow.write(M3_);
  wrist_ver.write(M4_);
  wrist_rot.write(M5_);
  gripper.write(M6_);

	if(soft_start_level!=SOFT_START_DISABLED)
    		_softStart(soft_start_level);
	return 1;
}

/*
Software implementation of the PWM for the SOFT_START_CONTROL_PIN,HIGH
@param high_time: the time in the logic level high
@param low_time: the time in the logic level low
*/
void _Braccio::_softwarePWM(int high_time, int low_time){
	digitalWrite(SOFT_START_CONTROL_PIN,HIGH);
	delayMicroseconds(high_time);
	digitalWrite(SOFT_START_CONTROL_PIN,LOW);
	delayMicroseconds(low_time); 
}

/*
* This function, used only with the Braccio Shield V4 and greater,
* turn ON the Braccio softly and save it from brokes.
* The SOFT_START_CONTROL_PIN is used as a software PWM
* @param soft_start_level: the minimum value is -70, default value is 0 (SOFT_START_DEFAULT)
*/
void _Braccio::_softStart(int soft_start_level){      
	long int tmp=millis();
	while(millis()-tmp < LOW_LIMIT_TIMEOUT)
		_softwarePWM(80+soft_start_level, 450 - soft_start_level);   //the sum should be 530usec	

	while(millis()-tmp < HIGH_LIMIT_TIMEOUT)
		_softwarePWM(75 + soft_start_level, 430 - soft_start_level); //the sum should be 505usec

	digitalWrite(SOFT_START_CONTROL_PIN,HIGH);
}

/**
 * This functions allow you to control all the servo motors
 * 
 * @param stepDelay The delay between each servo movement
 * @param vBase next base servo motor degree
 * @param vShoulder next shoulder servo motor degree
 * @param vElbow next elbow servo motor degree
 * @param vWrist_ver next wrist rotation servo motor degree
 * @param vWrist_rot next wrist vertical servo motor degree
 * @param vgripper next gripper servo motor degree
 */
int _Braccio::ServoMovement(int stepDelay, int vBase, int vShoulder, int vElbow,int vWrist_ver, int vWrist_rot, int vgripper) {

	// Check values, to avoid dangerous positions for the Braccio
  if (stepDelay > 30) stepDelay = 30;
	if (stepDelay < 10) stepDelay = 10;
	if (vBase < 0) vBase=0;
	if (vBase > 180) vBase=180;
	if (vShoulder < 15) vShoulder=15;
	if (vShoulder > 165) vShoulder=165;
	if (vElbow < 0) vElbow=0;
	if (vElbow > 180) vElbow=180;
	if (vWrist_ver < 0) vWrist_ver=0;
	if (vWrist_ver > 180) vWrist_ver=180;
	if (vWrist_rot > 180) vWrist_rot=180;
	if (vWrist_rot < 0) vWrist_rot=0;
  if (vgripper < 10) vgripper = 10;
	if (vgripper > 73) vgripper = 73;

	int exit = 1;

	//Until the all motors are in the desired position
	while (exit) 
	{			
		//For each servo motor if next degree is not the same of the previuos than do the movement		
		if (vBase != M1_) 
		{			
			base.write(M1_);
			//One step ahead
			if (vBase > M1_)
				++M1_;
			
			//One step beyond
			if (vBase < M1_)
				--M1_;
		}

		

		

		if (vWrist_ver != M4_) 
		{
			wrist_rot.write(M4_);
			//One step ahead
			if (vWrist_ver > M4_)
				++M4_;				
			
			//One step beyond
			if (vWrist_ver < M4_)
				--M4_;
		}

		if (vWrist_rot != M5_)
		{
			wrist_ver.write(M5_);
			//One step ahead
			if (vWrist_rot > M5_)
				++M5_;
        
			//One step beyond
			if (vWrist_rot < M5_)
				M5_;
		}

    if (vElbow != M3_){
      elbow.write(M3_);
      //One step ahead
      if (vElbow > M3_)
        ++M3_;
      
      //One step beyond
      if (vElbow < M3_)
        --M3_;
    }

    if (vShoulder != M2_)  
    {
      shoulder.write(M2_);
      //One step ahead
      if (vShoulder > M2_)
        ++M2_;
      
      //One step beyond
      if (vShoulder < M2_)
        --M2_;
    }

    

		if (vgripper != M6_)
		{
			gripper.write(M6_);
			if (vgripper > M6_)
				++M6_;
	
			//One step beyond
			if (vgripper < M6_)
				--M6_;
		}
		Braccio.M2();
		//delay between each movement
		delay(stepDelay);
		
		//It checks if all the servo motors are in the desired position 
		if ((vBase == M1_) && (vShoulder == M2_)
				&& (vElbow == M3_) && (vWrist_ver == M4_)
				&& (vWrist_rot == M5_) && (vgripper == M6_)) {
			M1_ = vBase;
			M2_ = vShoulder;
			M3_ = vElbow;
			M4_ = vWrist_ver;
			M5_ = vWrist_rot;
			M6_ = vgripper;
			exit = 0;
		} else {
			exit = 1;
		}
	}
}
