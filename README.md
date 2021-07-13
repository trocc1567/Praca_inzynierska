# Patryk_Troc_praca_inzynierska

Wersja programu: 1.0

Peryferia:

- RTC32

- USART0 (komunikacja po USB) konfiguracja: baud rate 9600, Even parity, 8 bits

- Dipswitch: bity 1-4 - address, bit 5 - tryb slave/master

Działanie:

Urządzenie na początku za pomocą USART wysyła dane o ustawionym na dipswitchu trybie działania (0 - Slave, 1 - Master) oraz adresie (liczba z zkresu 0-31). Potem przechodzi 
w tryb uśpienia (IDLE) i wybudza się po czasie obliczonym według wzoru: 5*address. Odpowiednio informuje o poszczególnych trybach działania za pomocą komend wysyłanych przez USART:

- "I go to sleep" - urządzenie przechodzi w tryb snu

- "I woke up" - urządzenie przechodzi w tryb działania

Urządzenie zczytuje i zapisuje do zegara wartości dipswitcha jedynie na początku działania, więc aby zmienić czas trybu uśpienia, po zmianie wartości na dipswitchu należy
zresetować urządzenie.
