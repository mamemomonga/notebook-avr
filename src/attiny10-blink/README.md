# Blink

Lチカ、500msごとに点滅する

# 動作クロックの設定

ATtiny10では、以下のようにクロックを設定する。
CCPレジスタは重要な設定の設定変更プロテクト。
CLKMSR, CLKPSR, WDTCSRなどを設定する前に設定する。

	// internal 8MHz
	CCP = 0xD8;
	CLKMSR = 0;

	// no prescale
	CCP = 0xD8;
	CLKPSR = 0;

# 配線

PB5に1KΩの抵抗を介してLEDを接続する

