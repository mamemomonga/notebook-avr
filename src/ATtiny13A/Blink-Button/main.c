#include "main.h"

// スリープが有功な間は1
uint8_t sleep_enable=1;

// INT0割り込みがあったらスリープ開始
// ISR_BLOCK: STATUSレジスタをクリア
ISR(INT0_vect,ISR_BLOCK) {

	// スリープが有功でなかったら処理スキップ
	if(!sleep_enable) {
		return;
	}

	// スリープ処理開始
	sleep_enable=0;

	// 停止処理
	LED1_L; LED2_L;
	_delay_ms(500);

	// 割込許可
	sei();

	// 入眠
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);
	sleep_enable();
	sleep_cpu();

	// 起床開始
	_delay_ms(500);
	sleep_enable=1;

	// mainの最初から始める
	__asm__ __volatile__ (
		"rjmp main\n\t"
	);

}

int main(void) {

	// 割込禁止
	cli();

	// 初期化
	BTN1_INIT;
	BTN2_INIT;
	LED1_INIT;
	LED2_INIT;

	// 起動直後は一秒間両方店頭する
	LED1_H; LED2_H; _delay_ms(1000);

	// INT0がLOWのときに割込発生
	// Power-downモードから復帰可能なのはこのモードのみ
	MCUCR &=~ (1<<ISC01);
	MCUCR &=~ (1<<ISC00);

	// INT0割り込み有効
	GIMSK |=  (1<<INT0);

	// LED状態を初期化
	LED1_H; LED2_L;

	// 割込許可
	sei();

	// メインループ
    for(;;){
		// BTN2が押されていない間は交互に点滅する
		if(BTN2_IS_H) {
			LED1_I; LED2_I;

			// c99記法なのでMakefileのコンパイルオプションに-std=gnu99の追加が必要	
			for(uint8_t i=0;i<5;i++) {
				_delay_ms(10);
			}
		}
    }
    return 0;
}

