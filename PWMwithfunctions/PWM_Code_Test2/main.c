/*
 * PWM_Code_Test.c
 *
 * Created: 11/3/2021 10:06:02 AM
 * Author : dbarrosmedina
 */ 

#define  F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <math.h>


volatile int i;
volatile int x;

#define NUM_POS 36
#define NUM2_POS 5

void move_to_top();
void half_way();
void open_arm();
void close_arm();
void initial_scan();
void position16();
void position15();
void position14();
void position13();
void position12();
void position11();
void position10();
void position9();
void position8();
void position7();
void position6();
void position5();
void position4();
void position3();
void position2();
void position1();
uint32_t getPulseWidth();
void calc_angle();


//    ************ function for user interface ************
//    ask user if they would like to run initial scan
//     stop if object is detected
// connect to distance measurement
//       > minimal distance
//      <  maximal distance
//     calculate the position by doing an over and under for the positions
//     determine which position would be ideal
//      pick up object
//      lift object
// ask user where to place it to place it
// angle and distance.   angle determines the position of the base servo: servo 1, distance determines rough distance "1-16"

// send info back to servos

/*
float Angle_A;
float Angle_B;


uint16_t shoulderTilt;
uint16_t elbowTilt;
*/

uint16_t positions_1[NUM_POS] = {1000,1100,1200,1300,1400,1500,1600,1700,1800,1900,2000,2100,2200,2300,2400,2500,2600,2700,2800,2900,
3000,3100,3200,3300,3400,3500,3600,3700,3800,3900,4000,4100,4200,4300,4400,4500};

int main(void)
{
	DDRD = 0xff;
	DDRB = 0x0f;
	
	/*
		servo 5(grabber) = pinD0
		servo 2 = pinD1
		servo 3 = pinB2
		servo 4 = pinB1
		servo Base = pinD2
		
		// PINOUTS FROM 12/7
		
	*/	
	//Servo 1
	
	//DDRD |= (1 << 0);
	TCCR3A |= (1 << COM3A1 | (0b10) << WGM30);
	TCCR3B |= ((0b11) << WGM32 | (0b010) <<CS30 | 1 << ICNC3);
	OCR3A |= 0000;
	ICR3 = 50000;
	
	//Servo 4
	
	//DDRB |= (1 << 0b00000001);
	TCCR1A |= (1 << COM1A1 | (0b10) << WGM10);
	TCCR1B |= ((0b11) << WGM12 | (0b010) <<CS10 | 1 << ICNC1);
	OCR1A |= 50000;
	ICR1 = 0000;
	
	//Servo 3
	
	//DDRB |= (1 << 0b00000010);
	TCCR1A |= (1 << COM1B1 | (0b10) << WGM10);
	TCCR1B |= ((0b11) << WGM12 | (0b010) <<CS10 |  1 << ICNC1);
	OCR1B |= 0000;
	ICR1 = 50000;
	
	//Servo 2
	//DDRD |= (1 << 0b00000001);
	TCCR4A |= (1 << COM4A1 | (0b10) << WGM40);
	TCCR4B |= ((0b11) << WGM42 | (0b010) << CS40 |  1 << ICNC4);
	OCR4A |= 0000;
	ICR4 = 50000;
	/*
	//Servo 5
	//DDRB |= (1 << 0b00000011);
	TCCR2A |= (1 << COM2A1 | (0b11) << WGM20);
	TCCR2B |= ((0b1) << WGM22 | (0b010) <<CS20);
	OCR2A |= 50000;
	//ICR2 = 50000;
	*/
	
	
	
	
	/* Replace with your application code */
	i=0;
	x = 0;
	uint32_t distance;
	while (1)
	{
		
		
		if (distance > 300){
			printf("Object too far")
			
		}
		
		else if (299 > distance && distance > 270){
			position16();
		}
		else if (269 > distance && distance > 250){
			position15();
		}	
		else if (249 > distance && distance > 230){
			position14();
		}		
		else if (229 > distance && distance > 210){
			position13();
		}
	//.
	//.	
	//.	
		//move_to_top();
		//half_way();
		//open_arm();
		//position1();
		//close_arm();
		//move_to_top();
		//half_way();
		//position5();
		//position1();
		

		//open_arm();
		//initial_scan();
		
		/*
		// Code going from quadrant 1 to quadrant 16
		
		// move to top
		//servo 2
		OCR4A = positions_1[22];
		_delay_ms(500);
		// servo 3
		OCR1B = positions_1[35];
		_delay_ms(500);
		//servo 4
		OCR1A = positions_1[22];
		_delay_ms(2000);
		
			//position 1
		// initial grab 
		OCR3A = positions_1[18]; // release
		_delay_ms(500);
		//servo 2
			OCR4A = positions_1[20];
		_delay_ms(500);
		// servo 3
		OCR1B = positions_1[15];
		_delay_ms(500);
		//servo 4
		OCR1A = positions_1[0];
		_delay_ms(500);
		//servo grabber
		//servo 1
		OCR3A = positions_1[0];  // grab
		_delay_ms(2000);
		/*
		//position 4
		// initial grab 
		OCR3A = positions_1[18]; // release
		_delay_ms(500);
		//servo 2
			OCR4A = positions_1[22];
		_delay_ms(500);
		// servo 3
		OCR1B = positions_1[20];
		_delay_ms(500);
		//servo 4
		OCR1A = positions_1[0];
		_delay_ms(500);
		//servo grabber
		//servo 1
		OCR3A = positions_1[0];  // grab
		_delay_ms(2000);
		
		
	// move to top 
	//servo 2
			OCR4A = positions_1[22];
		_delay_ms(500);
		// servo 3
		OCR1B = positions_1[35];
		_delay_ms(500);
		//servo 4
		OCR1A = positions_1[22];
		_delay_ms(2000);
		
		//position16();
		// position 16
		//servo 2
		OCR4A = positions_1[33];
		_delay_ms(500);
		// servo 3
		OCR1B = positions_1[30];
		_delay_ms(500);
		//servo 4
		OCR1A = positions_1[15];
		_delay_ms(500);
		//servo grabber
		//servo 1
		
		
		OCR3A = positions_1[18]; // release 
			_delay_ms(2000);
		
		// move to top
		//servo 2
		OCR4A = positions_1[22];
		_delay_ms(500);
		// servo 3
		OCR1B = positions_1[35];
		_delay_ms(500);
		//servo 4
		OCR1A = positions_1[22];
		_delay_ms(2000);
			

	
		
		/*
		//servo 1
		OCR3A = positions_1[3];
		_delay_ms(500);
		//Servo 4
		OCR1A = positions_1[4];
		_delay_ms(1000);
		
		//servo 3
		OCR1B = positions_1[2];
		_delay_ms(1000);
		//servo 2
		OCR4A = positions_1[4];
		_delay_ms(1000);
		//OCR4A = positions_1[3];
		//_delay_ms(1000);
		
		//servo 1
		OCR3A = positions_1[4];
		_delay_ms(500);
		//servo 3
		OCR1B = positions_1[4];
		_delay_ms(1000);
		/*
		//servo 5
		OCR4B = positions_1[3];
		_delay_ms(1000);
		OCR4B = positions_1[5];
		_delay_ms(1000);
		
		//servo2
		OCR4A = positions_1[2];
		_delay_ms(1000);
		
		//Servo 4
		OCR1A = positions_1[2];
		_delay_ms(1000);
			
		//servo 1 
		OCR3A = positions_1[0];
		_delay_ms(1000);
		
		*/
		/*
		//Servo 1
		int a;
		for (a=0;a<=8;a++)
		{
			OCR1A=positions_1[i++];
			if(i==NUM_POS)i=0;
			_delay_ms(1000);
		}
		
		//Servo 2
		int b;
		for (b=0;b<3;b++)
		{
			OCR1B=positions_2[x++];
			if(x==NUM2_POS)x=0;
			_delay_ms(1000);
		}
		*/
		/*
		uint32_t  difference;
		difference = getPulseWidth();
		distance = difference/1000;
while (distance >= 55)
{
	initial_scan(); 
}
distance= getPulseWidth(); */
		
	//calc_angle();
		
	}
}
/*
void calc_angle()
{

	//double  A = 21.323; // length in cm of shoulder joint
	float  A = 8.395; // length in in of shoulder joint

	//double  B = 8.783; // length in cm of elbow joint
	float  B = 3.458; // length in in of elbow joint

	//double  C = 13.97; // this is the target distance, test position []
	float  C = 6.5; // this is the target distance, test position []

	
	// "Kinematics" using the triangle arm shape and SSS triangle formula to get angle of arm w/ hard-coded positions 
	float Angle_A = (90 + ((acos(((powf(B,2))+(powf(C,2))-(powf(A,2))) / (2*B*C)))*180)/M_PI)/5.14;  // servo 2 => 4.3
    //float Angle_B = (((acos(((powf(A,2))+(powf(C,2))-(powf(B,2))) / (2*B*C)))*180)/M_PI)/5.14;  
	float Angle_C = (45 + ((acos(((powf(A,2))+(powf(B,2))-(powf(C,2))) / (2*B*A)))*180)/M_PI)/5.14;  // servo 3 => 9


	uint16_t shoulderTilt = Angle_A;
	uint16_t elbowTilt = Angle_C;

	//servo 2
	OCR4A = positions_1[shoulderTilt];
	_delay_ms(500);

	// servo 3
	OCR1B = positions_1[elbowTilt];
	_delay_ms(500);
}
*/


void open_arm()
{
		_delay_ms(500);

	OCR3A = positions_1[18]; // release
	_delay_ms(2000);
}

void close_arm()
{
	OCR3A = positions_1[0]; // release
	_delay_ms(2000);
}

void move_to_top()
{
	// move to top
	//servo 2
	OCR4A = positions_1[22];
	_delay_ms(500);
	// servo 3
	OCR1B = positions_1[20];
	_delay_ms(500);
	//servo 4
	//OCR1A = positions_1[22];
	//_delay_ms(2000);
}

void half_way()
{
	// move to top
//servo 4
//OCR1A = positions_1[15];
//_delay_ms(500);
	//servo 2
	OCR4A = positions_1[0];
	_delay_ms(500);
		// servo 3
	OCR1B = positions_1[2];
	_delay_ms(500);
	
}
// define position 12
// define position 13
// define position 14
// define position 15
// define position 16
void position16()
{
	//	_delay_ms(500);

	// position 16
	//servo 2
	OCR4A = positions_1[32];
	_delay_ms(500);
	// servo 3
	OCR1B = positions_1[27];
	_delay_ms(500);
	//servo 4
	//OCR1A = positions_1[15];
	//_delay_ms(500);

}
void position15()
{
	// position 16
	//servo 2
	OCR4A = positions_1[30];
	_delay_ms(500);
	// servo 3
	OCR1B = positions_1[24];
	_delay_ms(500);
	//servo 4
	//OCR1A = positions_1[8];
	//_delay_ms(500);

}
void position14()
{
	// position 16
	//servo 2
	OCR4A = positions_1[27];  // shoulder
	_delay_ms(500);  
	// servo 3
	OCR1B = positions_1[19]; // 
	_delay_ms(500);
	//servo 4
	//OCR1A = positions_1[8];
	//_delay_ms(500);

}
void position13()
{
	// position 16
	//servo 2
	OCR4A = positions_1[26];
	_delay_ms(500);
	// servo 3
	OCR1B = positions_1[18];
	_delay_ms(500);
	//servo 4
	//OCR1A = positions_1[6];
	//_delay_ms(500);

}
void position12()
{
	// position 16
	//servo 2
	OCR4A = positions_1[26];
	_delay_ms(500);
	// servo 3
	OCR1B = positions_1[16];
	_delay_ms(500);
	//servo 4
	//OCR1A = positions_1[32];
	//_delay_ms(500);
}

void position11()
{
	// position 16
	//servo 2
	OCR4A = positions_1[26];
	_delay_ms(500);
	// servo 3
	OCR1B = positions_1[14];
	_delay_ms(500);
	//servo 4
	//OCR1A = positions_1[30];
	//_delay_ms(500);
}

void position10()
{
	// position 16
	//servo 2
	OCR4A = positions_1[24];
	_delay_ms(500);
	// servo 3
	OCR1B = positions_1[12];
	_delay_ms(500);
	//servo 4
	//OCR1A = positions_1[32];
	//_delay_ms(500);

}

void position9()
{
	// position 16
	//servo 2
	OCR4A = positions_1[22];
	_delay_ms(500);
	// servo 3
	OCR1B = positions_1[12];
	_delay_ms(500);
	//servo 4
	//OCR1A = positions_1[30];
	//_delay_ms(500);

}

void position8()
{
	// position 16
	//servo 2
	OCR4A = positions_1[22];
	_delay_ms(500);
	// servo 3
	OCR1B = positions_1[11];
	_delay_ms(500);
	//servo 4
	//OCR1A = positions_1[34];
	//_delay_ms(500);

}

void position7()
{
	// position 16
	//servo 2
	OCR4A = positions_1[20];
	_delay_ms(500);
	// servo 3
	OCR1B = positions_1[11];
	_delay_ms(500);
	//servo 4
	//OCR1A = positions_1[35];
	//_delay_ms(500);

}


void position6()
{
	// position 16
	//servo 2
	OCR4A = positions_1[19];
	_delay_ms(500);
	// servo 3
	OCR1B = positions_1[9];
	_delay_ms(500);
	//servo 4
	//OCR1A = positions_1[35];
	//_delay_ms(500);

}


void position5()
{
	// position 16
	//servo 2
	OCR4A = positions_1[18];
	_delay_ms(500);
	// servo 3
	OCR1B = positions_1[8];
	_delay_ms(500);
	//servo 4
	//OCR1A = positions_1[35];
	//_delay_ms(500);

}

void position4()
{
	
	//servo 2
	OCR4A = positions_1[17];
	_delay_ms(500);
	// servo 3
	OCR1B = positions_1[6];
	_delay_ms(500);
	//servo 4
	//OCR1A = positions_1[7];
	//_delay_ms(500);

}
void position3()
{
	
	//servo 2
	OCR4A = positions_1[15];
	_delay_ms(500);
	// servo 3
	OCR1B = positions_1[5];
	_delay_ms(500);
	//servo 4
	//OCR1A = positions_1[7];
	//_delay_ms(500);
}

void position2()
{
	
	//servo 2
	OCR4A = positions_1[13];
	_delay_ms(500);
	// servo 3
	OCR1B = positions_1[3];
	_delay_ms(500);
	//servo 4
	//OCR1A = positions_1[7];
	//_delay_ms(500);
}

void position1()
{
		_delay_ms(500);
	//servo 2
	OCR4A = positions_1[11];
	_delay_ms(500);
	// servo 3
	OCR1B = positions_1[2];
	_delay_ms(500);
	//servo 4
	//OCR1A = positions_1[7];
	//_delay_ms(500);
}

void initial_scan()
{
	//servo 4 base*
	OCR1A = positions_1[0];
	_delay_ms(2500);
	OCR1A = positions_1[35];
	_delay_ms(2500);
}

/*
uint32_t getPulseWidth()
{
	uint16_t timeOne,timeTwo;
	uint32_t diff;
	//generate trigger pulse
	PORTD |= (1<<2);
	_delay_us(20);
	PORTD |= 0;
	// find rising edge
	TCCR3B |= (1<<ICES3);
	while ((TIFR3 & (1<<ICF3))==0);
	timeOne = ICR3;
	TIFR3 = (1<<ICF3); //clear the flag
	
	//find falling edge
	TCCR3B &= ~(1<<ICES3);
	while ((TIFR3 & (1<<ICF3))==0);
	timeTwo = ICR3;
	TIFR3 = (1<<ICF3); //clear the flag
	
	//uint16_t diff, timeOne,timeTwo;
	diff = timeTwo-timeOne;
	return diff*680; // micrometers
} */


