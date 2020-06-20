# ATTiny13A USART 送信・受信

USARTの送受信

処理中に受信があれば、delay終了後にプロンプトを出し入力を受け付ける。(割込から直接入力を受け付けるとコードサイズが大きくなる)

	AVR Memory Usage
	----------------
	Device: attiny13
	
	Program:     344 bytes (33.6% Full)
	(.text + .data + .bootloader)
	
	Data:          1 bytes (1.6% Full)
	(.data + .bss + .noinit)

