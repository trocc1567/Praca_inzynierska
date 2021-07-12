
======================
RTC32 driver
======================
The RTC32 peripheral is a 32-bit counter that typically runs continuously to keep track of time even in low power sleep modes. 

NOTE: Reference clock is typically a 1Hz prescaled output from a high accuracy crystal of 32.768kHz.

Features
--------
* Initialization

Applications
------------
* Compare/Overflow Interrupt
* Delayed Applications

Dependencies
------------
* CLK for clocks
* EVSYS for events
* CPUINT/PMIC for Interrupt
* JTAG/PDI/UPDI for debug

Note
----
* ISR will be generated only when Global Interrupt checkbox and driver_isr Harness checkbox are enabled

Concurrency
-----------
N/A

Limitations
-----------
N/A

Knows issues and workarounds
----------------------------
N/A

