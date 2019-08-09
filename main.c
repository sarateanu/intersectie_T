/*
 * intersectie.c
 *
 * Created: 4/20/2018 10:55:06 AM
 * Author : Mircea.Sarateanu
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 1000000


unsigned int traficA = 0;
unsigned int traficB = 0;

unsigned int tick1 = 0;
unsigned int tick2 = 0;
unsigned int fazare = 0;


static unsigned int baleiaj = 0;
//static unsigned int potentiometru = 0;

static unsigned int trafic_principal;
static unsigned int trafic_secundar;

static unsigned int durata = 0;

static unsigned int trafic1 = 0;
static unsigned int trafic2 = 0;


void afisare_LCD(unsigned int numar1, unsigned int numar2, unsigned int digit)
{
	unsigned int separat[2];
	unsigned int unitati, zeci;
	unsigned int valoare, count, aux;
	valoare = numar1;
	count = 0;
	aux = 0;
	separat[0] = separat[1] = 0;
	while(valoare!=0)
	{
		aux = valoare % 10;
		valoare = valoare / 10;
		separat[count] = aux;
		count ++;
		
	}//END WHILE
	
	zeci = separat[1];
	unitati = separat[0];//Separa numarul in componente numar1
	
	
	unsigned int vector1[2];
	unsigned int zeci2, unitati2;
	unsigned int valoare2, count2, aux2;
	
	valoare2 = numar2;
	count2 = 0;
	aux2 = 0;
	
	vector1[0] = vector1[1] = 0;
	
	while(valoare2 !=0){
		
		aux2 = valoare2 % 10;
		valoare2 = valoare2 / 10;
		vector1[count2] = aux2;
		count2 ++;
		
		
	}//END WHILE
	
	zeci2 = vector1[1];
	unitati2 = vector1[0];
	
	
	
	if(digit == 0){
		PORTC |= (1<<PC3);
		PORTC &= ~((1<<PC2)|(1<<PC1)|(1<<PC0));
	switch(unitati2){
		
		case 0 : PORTD = 0b00000010;  break;
		case 1 : PORTD = 0b10011110;  break;
		case 2 : PORTD = 0b00100100;  break;
		case 3 : PORTD = 0b00001100;  break;
		case 4 : PORTD = 0b10011000;  break;
		case 5 : PORTD = 0b01001000;  break;
		case 6 : PORTD = 0b01000000;  break;
		case 7 : PORTD = 0b00011110;  break;
		case 8 : PORTD = 0b00000000;  break;
		case 9 : PORTD = 0b00001000;  break;
		
			
		
	}
	
	}//END IF
	
	
	if(digit == 1){
		PORTC |=(1<<PC2);
		PORTC &= ~((1<<PC3)|(1<<PC1)|(1<<PC0));
		switch(zeci2){
			
			case 0 : PORTD = 0b00000010;  break;
			case 1 : PORTD = 0b10011110;  break;
			case 2 : PORTD = 0b00100100;  break;
			case 3 : PORTD = 0b00001100;  break;
			case 4 : PORTD = 0b10011000;  break;
			case 5 : PORTD = 0b01001000;  break;
			case 6 : PORTD = 0b01000000;  break;
			case 7 : PORTD = 0b00011110;  break;
			case 8 : PORTD = 0b00000000;  break;
			case 9 : PORTD = 0b00001000;  break;
			
			
			
		}
		
		
		
	}//END IF
	
	if(digit == 2){
		PORTC |=(1<<PC1);
		PORTC &= ~((1<<PC3)|(1<<PC2)|(1<<PC0));
		switch(unitati){
			
			case 0 : PORTD = 0b00000010;  break;
			case 1 : PORTD = 0b10011110;  break;
			case 2 : PORTD = 0b00100100;  break;
			case 3 : PORTD = 0b00001100;  break;
			case 4 : PORTD = 0b10011000;  break;
			case 5 : PORTD = 0b01001000;  break;
			case 6 : PORTD = 0b01000000;  break;
			case 7 : PORTD = 0b00011110;  break;
			case 8 : PORTD = 0b00000000;  break;
			case 9 : PORTD = 0b00001000;  break;
			
			
			
		}
		
		
		
	}//END IF
	
	
	if(digit == 3){
		PORTC |= (1<<PC0);
		PORTC &= ~((1<<PC3)|(1<<PC2)|(1<<PC1));
		switch(zeci){
			
			case 0 : PORTD = 0b00000010;  break;
			case 1 : PORTD = 0b10011110;  break;
			case 2 : PORTD = 0b00100100;  break;
			case 3 : PORTD = 0b00001100;  break;
			case 4 : PORTD = 0b10011000;  break;
			case 5 : PORTD = 0b01001000;  break;
			case 6 : PORTD = 0b01000000;  break;
			case 7 : PORTD = 0b00011110;  break;
			case 8 : PORTD = 0b00000000;  break;
			case 9 : PORTD = 0b00001000;  break;
			
			
			
		}
		
		
		
	}
}//END FUNCTION


void initializare_ADC()
{
	ADMUX = 0;
	ADMUX |= (1<<REFS0);//Vezi pagina 211 din datasheet Atmega16
	ADCSRA |= (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);//Enable ADC si stabilire factor divizare frecventa core cu 128
	
	
}


unsigned int citeste_ADC(int intrare)
{
	
	
	unsigned int rezultat;
	ADMUX = 0;
	ADMUX = (1<<REFS0);
	
	if(intrare == 0)
	{
		ADMUX |=(1<<REFS0);
		ADCSRA |= (1<<ADSC);
		while((ADCSRA & (1<<ADIF))==0)
		{
			//Asteapta sfarsitul conversiei
			
		}
		
		rezultat = ADCL + (ADCH*256);
	}
	
	
	if(intrare == 1)
	{
		ADMUX |=(1<<REFS0)|(1<<MUX0);
		ADCSRA |= (1<<ADSC);
		while((ADCSRA & (1<<ADIF))==0)
		{
			//Asteapta sfarsitul conversiei
			
		}
		
		rezultat = ADCL + (ADCH*256);
	
	}
	
	
	return rezultat;
}

ISR(TIMER0_OVF_vect){
	
	
	afisare_LCD(trafic_principal, trafic_secundar, baleiaj);
	baleiaj = baleiaj + 1;
	if(baleiaj == 4){baleiaj = 0;}
	
	
	
}

ISR(TIMER2_OVF_vect){
	
	//trafic1 = citeste_ADC(0);
	//trafic2 = citeste_ADC(1);
	trafic1 = 120;
	trafic2 = 600;
	trafic_principal = trafic1/10;
	trafic_secundar = trafic2/10;
	
	//trafic_principal = 11;
	//trafic_secundar = 17;
	
}

void initializare_semafor()
{
	
	PORTA |= (1<<PA2)|(1<<PA5);
	PORTA &= ~((1<<PA3)|(1<<PA4));
	
}

void schimba_semafor(unsigned int faza)
{
	
	//Faza estte o variabila binara 0 si 1 , 0 - trafic principal liber, 1- trafic secundar liber
	
	if(faza == 0){
		PORTA |=(1<<PA3)|(1<<PA4);
		PORTA &= ~((1<<PA2)|(1<<PA5));
		
	}
	
	else{
		PORTA &= ~((1<<PA3)|(1<<PA4));
		PORTA |= (1<<PA2)|(1<<PA5);
		
		
	}
		
		
	}
	
	


int main(void)
{
	DDRD = 0xFF;
	PORTD = 0;
	
	DDRC = 0xFF;
	PORTC = 0;
	
	
	DDRA = 0;
	DDRA |=(1<<PA2)|(1<<PA3)|(1<<PA4)|(1<<PA5);
	////PA2 - LED ROSU Pentru drum principal
	////PA3 - LED VERDE Pentru drum principal
	////PA4 - LED ROSU Pentru drum secundar
	////PA5 - LED VERDE Pentru drum secundar
	initializare_ADC();
    ///* Replace with your application code */
	sei();
	//
	TIMSK |= (1<<TOIE0)|(1<<TOIE2);
	TCCR0 = 0;
	TCCR0 |= (1<<CS01)|(1<<CS00);//SETARE CLK/8 si atunci 1.000.000 / 8 = 125.000  si 125.000 / 255 = 490 HZ
	////Se implementeaza astfel sistemul de afisare
	TCCR2 = 0;
	TCCR2 |= (1<<CS21)|(1<<CS20);
	////Se implementeza sistemul de citire al potentiometrelor
	////Am implementat citirea potentiometrilor pe ADC, sistemul de afisare
	TIMSK |= (TOIE1);
	TCCR1A = 0;
	TCCR1B |= (1<<CS12)|(1<<CS10);
	
	//
	initializare_semafor();
    while (1) 
    {
		
		if((trafic_principal>= 0)&&(trafic_principal<= 9)){traficA = 30;}
		if((trafic_principal>=10)&&(trafic_principal<=19)){traficA = 40;}
		if((trafic_principal>=20)&&(trafic_principal<=29)){traficA = 50;}
		if((trafic_principal>=30)&&(trafic_principal<=39)){traficA = 60;}
		if((trafic_principal>=40)&&(trafic_principal<=49)){traficA = 70;}
		if((trafic_principal>=50)&&(trafic_principal<=59)){traficA = 80;}
		if((trafic_principal>=60)&&(trafic_principal<=69)){traficA = 90;}
		if((trafic_principal>=70)&&(trafic_principal<=79)){traficA = 100;}
		if((trafic_principal>=80)&&(trafic_principal<=89)){traficA = 130;}
		if((trafic_principal>=90)&&(trafic_principal<=99)){traficA = 230;}	
			
		if((trafic_secundar>= 0)&&(trafic_secundar<=9)){traficB = 30;}
		if((trafic_secundar>= 10)&&(trafic_secundar<=19)){traficB = 40;}
		if((trafic_secundar>= 20)&&(trafic_secundar<=29)){traficB = 50;}
		if((trafic_secundar>= 30)&&(trafic_secundar<=39)){traficB = 60;}
		if((trafic_secundar>= 40)&&(trafic_secundar<=49)){traficB = 70;}
		if((trafic_secundar>= 50)&&(trafic_secundar<=59)){traficB = 80;}
		if((trafic_secundar>= 60)&&(trafic_secundar<=69)){traficB = 90;}
		if((trafic_secundar>= 70)&&(trafic_secundar<=79)){traficB = 100;}
		if((trafic_secundar>= 80)&&(trafic_secundar<=89)){traficB = 130;}
		if((trafic_secundar>= 90)&&(trafic_secundar<=99)){traficB = 230;}
																			
		
		if((traficA>=30)&&(traficA<=70)&&(traficB>=70)&&(traficB<=230)){//trafic scazut pe principal
				durata = 200;//durata mai mica principal
		
					}
					
		if((traficA>=80)&&(traficA<=230)&&(traficB>=30)&&(traficB<=70))
			{
			durata = 1000;	
			}
			
			
			while(tick1 < 32000 ){tick1 = tick1 + 1;}
				tick1 = 0;
			while (tick2 < 32000 - durata ){tick2 = tick2 + 1;}
				tick2 = 0;
				fazare = ~ fazare;
					
			schimba_semafor(fazare);
				
				
    }
}

