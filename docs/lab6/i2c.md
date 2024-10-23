# The I<sup>2</sup>C Bus Protocol
## Oscilloscope/Logic Analyzer Settings
* Bus Protocol: I2C
* Bus Format: Hex or ASCII
* SCL Signal:
  * Channel: C1
  * Threshold: 1.5V-2V
* SDA Signal:
  * Channel: C2
  * Threshold: 1.5V-2V
* Include R/W Bit: Off
* Protocol Copy: Copy Protocol to Trigger

## Acknowledge (ACK)
Each byte of transferred data (including the address byte) is followed by one ACK bit from the receiver. The ACK bit allows the receiver to communicate to the transmitter that the byte was successfully received and another byte may be sent.[<sup>1</sup>][1]

Before the receiver can send an ACK, the transmitter must release the SDA line. To send an ACK bit, the receiver shall pull down the SDA line during the low phase of the ACK/NACK-related clock period (period 9), so that the SDA line is stable low during the high phase of the ACK/NACK-related clock period. Setup and hold times must be taken into account.[<sup>1</sup>][1]

Because the SDA line must be released by the transmitter before the receiver can send an ACK, if the receiver is delayed in taking over, the SDA line will immediately begin rising back to its idle pulled-up state, only to be pulled straight back down to ground by the receiver for the ACK. This results in a transient spike on the SDA line following the falling edge of the clock signal at the end of a byte, but because the spike starts and ends all while the clock is pulled low, the transient spike does not actually cause any communication errors.

## Not Acknowledge (NACK)
When the SDA line remains high during the ACK/NACK-related clock period, this is interpreted as a NACK. There are several conditions that lead to the generation of a NACK:
1. The receiver is unable to receive or transmit because it is performing some real-time function and is
not ready to start communication with the master.
2. During the transfer, the receiver gets data or commands that it does not understand.
3. During the transfer, the receiver cannot receive any more data bytes.
4. A master-receiver is done reading data and indicates this to the slave through a NACK. The slave will then release control of the SDA line so that the master can send a STOP.

[1]: <https://www.ti.com/lit/an/slva704/slva704.pdf?ts=1729603996619>
