#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wiringPi.h>
  
#define GPIO_SER 27
// GPIO_CLKはデバッグ用
#define GPIO_CLK 22

#define DLY_A  delayMicroseconds(10)
#define DLY_B  delayMicroseconds(50)

#define SER_H digitalWrite(GPIO_SER, 1)
#define SER_L digitalWrite(GPIO_SER, 0)

void usage(char *name) {
	printf("USAGE:\n");
	printf("  %s set [value]\n",name);
	printf("  %s get\n",name);
	printf("  %s blinker\n",name);
}

void blinker() {
	printf("BLINKER\n");
	pinMode(GPIO_CLK, OUTPUT);
	while(1) {
	    digitalWrite(GPIO_CLK, 0);
	    delay(50);
	    digitalWrite(GPIO_CLK, 1);
	    delay(50);
	}
	digitalWrite(GPIO_CLK, 0);
}

void debug_bit() {
	digitalWrite(GPIO_CLK,1);
	delayMicroseconds(1);
	digitalWrite(GPIO_CLK,0);
	delayMicroseconds(1);
}

int data_set(char *data) {
	short unsigned int num = atoi(data);
	pinMode(GPIO_CLK, OUTPUT); // FIXME
	pinMode(GPIO_SER, OUTPUT);
	pullUpDnControl(GPIO_SER, PUD_OFF);

	printf("SET: 0x%02x(%02d)\n",num,num);

	debug_bit();
	SER_L; DLY_B; // 割込
	debug_bit();
	debug_bit();
	SER_H; DLY_B; // タイミング
	debug_bit();
	SER_L; DLY_B; // Write Bit
	debug_bit();
	SER_H; DLY_B; // 終了

	int i=8;
	while(i--) {
		SER_L; DLY_A; // 開始
		SER_H; DLY_A;
		SER_L; DLY_A; // 送信
		digitalWrite(GPIO_CLK,1);
		if((num >> i) & 1) {
			SER_H;
		} else {
			SER_L;
		}
		DLY_A;
		digitalWrite(GPIO_CLK,0);
		SER_H; DLY_B; // 終了
	}
	SER_L; DLY_A; // 終了
	SER_H; DLY_A;
	return 0;
}

int data_get() {
	pinMode(GPIO_CLK, OUTPUT); // FIXME
	pinMode(GPIO_SER, OUTPUT);
	pullUpDnControl(GPIO_SER, PUD_OFF);


	SER_L; DLY_B; // 割込
	SER_H; DLY_B; // タイミング
	SER_H; DLY_B; // Read Bit
	SER_H; DLY_B; // 完了パルス
	SER_L; DLY_A; 
	SER_H; DLY_A; 

	pinMode(GPIO_SER, INPUT);
	pullUpDnControl(GPIO_SER, PUD_UP);

	while(digitalRead(GPIO_SER) == 0);

	while(digitalRead(GPIO_SER) == 1);

	short unsigned int num=0;
	int i=8;
	while(i--) {
		// Low
		while(digitalRead(GPIO_SER) == 0);
		// High
		while(digitalRead(GPIO_SER) == 1);
		// Low
		delayMicroseconds(10+8);	

		// Data
		digitalWrite(GPIO_CLK,1);
		if( digitalRead(GPIO_SER) ) num |= (1<<i);
		digitalWrite(GPIO_CLK,0);
		delayMicroseconds(10+5);	

		// High
		while(digitalRead(GPIO_SER) == 1);
	}
	// High
	while(digitalRead(GPIO_SER) == 1);

	pinMode(GPIO_SER, OUTPUT);
	pullUpDnControl(GPIO_SER, PUD_OFF);
	digitalWrite(GPIO_SER,1);

	printf("GET: 0x%02x(%02d)\n",num,num);
	return 0;
}

int main(int argc,char *argv[]) {
    if(wiringPiSetupGpio() == -1) return 1;

	if(argc == 1 || argc > 3) {
		usage(argv[0]);
		return 1;
	}

	if(strcmp(argv[1],"set") == 0) {
		return data_set(argv[2]);

	} else if(strcmp(argv[1],"get") == 0) {
		return data_get();

	} else if(strcmp(argv[1],"blinker") == 0) {
		blinker();
		return 0;

	} else {
		usage(argv[0]);
		return 0;
	}
    return 0;
}
