/*
* Inter-Integreated Circuit 
* I2C
* Two Wire Interface[SDA-SCL]
* TWI
*/
// SCL [serial clock] >> for synchronizing data transfer between the master and the slave.
//SDA [serial data] >> the data line.

/*
operation modes
1- Master Transmitter 
2- Master  Receiver
3- Slave Transmitter 
4- Slave  Receiver
*/

/*
 * Transmitter >>     the device which sends data to the Bus.
 * Receiver >>        the device which receives data from the Bus.
 * Master >>          the device which initiates a transfer, generates clock signals and terminates a transfer.
 * Slave >>           the device addressed by a master.
 * Multi-master >>    more than one master can attempt to control the bus at the same time without corrupting the message.
 * Arbitration >>     procedure to ensure that, if more than one master simultaneously tries to control the bus, only one is allowed to do so and the winning message is not corrupted.
 * Synchronization >> procedure to synchronize the clock signals of two or more devices.

*/

// Transactions are initiated and completed by the master.
// ALL messages have an address frame and data frame.
// Data is placed on the SDA line after SCL goes low, and it is sampled after the SCL line goes high.
//
 

/*
    _________________________________________________________________________
   | start | slave    address       |R/W|ACK|      DATA (n-bytes) |ACK|STOP |
   |_______|________________________|___|___|_____________________|___|_____|
   
(1)The Protocol - START an STOP

[#] All transactions begin with START and are terminated by STOP.
[#] A HIGH to LOW transition on the SDA line while SCL is HIGH defines a START condition.
[#] A LOW to HIGH transition on the SDA line while SCL is HIGH defines a STOP condition.
[#] START and STOP conditions are always generated by the master. 
[#] The bus is considered to be free again a certain time after the STOP condition.
[#] The bus stays busy if a repeated START is generated instead of a STOP condition.

(2)The Protocol - BYTE Format

[#] Any information transmitted on the SDA line must be eight bits long.
[#] The number of bytes that can be transmitted per transfer is unrestricted.
[#] Each byte must be followed by an Acknowledge (ACK) bit. 
[#] Data is transferred with the Most Significant Bit (MSB) first.

(3)The Protocol - Address Frame

[#] The address frame is first in any new communication sequence.
[#] For a 7-bit address, the address is sent out significant bit (MSB) first,
    followed by a R/W bit indicating whether this is a read (1) or write (0) operation.
	
	
(4) The Protocol - Data Frame
 
[#] The data frame begins transmission after the address frame is sent.
[#] The master will simply continue generating clock pulses on SCL at a regular interval,
    and the data will be placed on SDA by either the master or the slave,
	depending on whether the R/W bit indicated a read or write operation.
*/

//===============================================

//12C Clock Speed
/* 
 - This is the speed of the 12C interface and should correspond with the bus speeds defined in the 12C specification.
 
 The specification defines the following modes:

[#] Standard-mode    : 100 KHz max
[#] Fast-mode        : 400 KHz max
[#] Fast-mode Plus   : 1 MHz
[#] High-speed mode  : 3.4 MHz

*/
//===============================================
//12C Duty Cycle
/*
[#] Specifies the ratio between tow and tHIGH of the I2C SCL line.
[#] Possible values:
                   I2C_DUTYCYCLE_2    = 2:1
                   I2C_DUTYCYCLE_16_9 = 16:9
 
[#] By choosing the appropriate duty cycle we can pre-scale the peripheral clock to achieve the desired 12C speed.

*/
//===============================================
//Difference between 12C and SPI
/*
[#] 12C is half duplex communication and SPI is full duplex communication.
[#] 12C supports multi master and multi slave and SPI supports single master.
[#] 12C is a two wire protocol and SPI is a four wire protocol. 
[#] 12C supports clock stretching and SPI does not have clock stretching.
[#] 12C is slower than SPI.SPI Max speed is FPclk/2. In STM Microcontrollers max seed is just 400 KHz. 
    Data rate from sender to receiver in 1 Sec is very much lesser in 12C compared to SPI.
[#] 12C has extra overhead start and stop bits and SPI does not have any start and stop bits.
[#] 12C has an acknowledgment bit after every byte of transfer.
[#] 12C has a pullup resistor requirement.

*/
//===============================================
//Procedure if Master Wants to Access Slave
/*
(1) Suppose a master wants to send data to a slave:
[#]  Master-transmitter sends a START condition and addresses the slave-receiver.
[#]  Master-transmitter sends data to slave-receiver.
[#]  Master-transmitter terminates the transfer with a STOP condition.


(2) If a master wants to receive/read data from a slave:
[#]  Master-receiver sends a START condition and addresses the slave-transmitter.
[#]  Master-receiver sends the requested register to read to slave-transmitter.
[#]  Master-receiver receives data from the slave-transmitter.
[#]  Master-receiver terminates the transfer with a STOP condition.
*/