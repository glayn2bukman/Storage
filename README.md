# Storage
Arduino Storage Library(EEPROM abstraction)

### Compatibility

#### All Arduino IDEs should be supported(the library only depends on EEPROM)

#### All Boards should be supported

```
Storage store;
```

### Installation
- Click on the 'Clone or download' button above the list of files on this <a href = "https://github.com/glayn2bukman/Storage/tree/master"> page </a>.
- Select Download ZIP. A .zip file will download to your computer.
- Unzip the archive and rename resulting folder to 'Storage'
- Move the folder to your libraries folder (~/sketches/libraries or ~/Arduino/libraries)

### Usage

- The library is called by declaring the```Storage store;``` constructor where 'store' can be replaced by a user constructor of choice.


###### `capacity()`
Returns the maximum memory in bytes eg for 1Kb, the method will return 1024

<hr>

##### Read commands
<hr>
<sub>
All read/write methods set the attribute ```ERROR``` to true/false indicating if an error happened(when ERROR is true) or not
</sub>

###### readAnything(address, value)
Reads _any type of variable/struct_ (any sized value) from a specific location. Takes the address (0-maxAddress) of the data and the variable/struct to write the data back to, as arguments.

###### readByte(address)
Reads a _byte_ (unsigned 8 bit value) from a specific location. Takes the address (0-maxAddress) of the byte as an argument.

###### readChar(address)
Reads a _char_ (signed 8 bit value) from a specific location. Takes the address (0-maxAddress) of the char as an argument.

###### readWord(address)
Reads a _word_ (unsigned 16 bit value) from a specific location. Takes the address (0-maxAddress) of the word as an argument.

###### readShort(address)
Reads a _short_ (signed 16 bit value) from a specific location. Takes the address (0-maxAddress) of the short as an argument.

###### readULong(address)
Reads an _unsigned long_ (unsigned 32 bit value) from a specific location. Takes the address (0-maxAddress) of the unsigned long as an argument.

###### readLong(address)
Reads a _long_ (signed 32 bit value) from a specific location. Takes the address (0-maxAddress) of the long as an argument.

###### readFloat(address)
Reads a _float_ (decimal value) from a specific location. Takes the address (0-maxAddress) of the float as an argument.

###### readStr(address, outputStr)
Reads a _string_ (String Object) from a specific location to an outputStr variable. Takes the address (0-maxAddress) of the String and a String as arguments.

###### readAnything(address, value)
Reads _any type of variable/struct_ (any sized value) from a specific location. Takes the address (0-maxAddress) of the data and the variable/struct to write the data to, as arguments.
<hr>

##### Write commands
<hr>
<sub>
All write commands take a boolean last argument 'errorCheck'. This argument defaults to TRUE, but when set to FALSE will more than double the writing speed. This however comes at the cost of checking for writing errors. Use with care.
</sub>

<sub> All write commands only take a 32-bit address variable instead of the optional 16-bit page number & 8-bit offset variables in previous versions of the library (< v3.0.0) </sub>

###### writeByte(address, data)
Writes a byte of data to a specific location. Takes the address (0-maxAddress) of data byte and one byte of data as arguments.

###### writeChar(address, data)
Writes a _char_ (signed 8 bit value) to a specific location. Takes the address (0-maxAddress) of the char and one char of data  as arguments.

###### writeWord(address, data)
Writes a _word_ (unsigned 16 bit value) to a specific location. Takes the address (0-maxAddress) of the word and one word of data as arguments.

###### writeShort(address, data)
Writes a _short_ (signed 16 bit value) to a specific location. Takes the address (0-maxAddress) of the short and one short of data as arguments.

###### writeULong(address, data)
Writes an _unsigned long_ (unsigned 32 bit value) to a specific location. Takes the address (0-maxAddress) of the unsigned long and one unsigned long of data as arguments.

###### writeLong(address, data)
Writes a _long_ (signed 32 bit value) to a specific location. Takes the address (0-maxAddress) of the long and one long of data as arguments.

###### writeFloat(address, data)
Writes a _float_ (decimal value) to a specific location. Takes the address (0-maxAddress) of the float and one float of data as arguments.

###### writeStr(address, data)
Writes a _string_ (String Object) to a specific location. Takes the address (0-maxAddress) of the String and a String as arguments.

###### writeAnything(address, value)
Writes _any type of variable/struct_ (any sized value) from a specific location. Takes the address (0-maxAddress) of the data and the variable/struct to write the data from, as arguments.
<hr>

##### Continuous read/write commands
<sub>
All write commands take a boolean last argument 'errorCheck'. This argument defaults to TRUE, but when set to FALSE will more than double the writing speed. This however comes at the cost of checking for writing errors. Use with care.
</sub>
<hr>

###### readByteArray(address, *data_buffer, bufferSize)
Reads an array of bytes starting from a specific address Takes the address (0-maxAddress) & a data_buffer - i.e. an array of bytes to be read from the flash memory - and size of the array as arguments. ```uint8_t data_buffer[n];``` The data buffer **must** be an array of n **bytes**. 'n' is determined by the amount of RAM available on the Arduino board.

###### writeByteArray(address, *data_buffer, bufferSize)
Writes an array of bytes starting from a specific address. Takes the address (0-maxAddress) & a data_buffer - i.e. an array of bytes to be written to the flash memory - and size of the array as arguments. ```uint8_t data_buffer[n];``` The data buffer **must** be an array of 'n' **bytes**. The number of bytes - 'n' - is determined by the amount of RAM available on the Arduino board.

###### readCharArray(address, *data_buffer, bufferSize)
Reads an array of chars starting from a specific address. Takes the address (0-maxAddress) & a data_buffer - i.e. an array of chars to be read from the flash memory - and size of the array as arguments. ```char data_buffer[n];``` The data buffer **must** be an array of n **chars**. 'n' is determined by the amount of RAM available on the Arduino board.

###### writeCharArray(address, *data_buffer, bufferSize)
Writes an array of chars starting from a specific address. Takes the address (0-maxAddress) & a data_buffer - i.e. an array of chars to be written to the flash memory - and size of the array as arguments. ```char data_buffer[n];``` The data buffer **must** be an array of 'n' **chars**. The number of chars - 'n' - is determined by the amount of RAM available on the Arduino board.
<hr>

##### Erase commands
<sub>
All erase commands only take a 32-bit address variable instead of the optional 16-bit page number & 8-bit offset variables in previous versions of the library (< v3.0.0)
</sub>
<hr>

###### eraseSector(address)
Erases one 4KB sector - 16 pages - containing the address to be erased. The sectors are numbered 0 - 255 containing 16 pages each.
Page 0-15 --> Sector 0; Page 16-31 --> Sector 1;......Page 4080-4095 --> Sector 255, and so on...

###### eraseBlock32K(address)
Erases one 32KB block - 128 pages - containing the address to be erased. The blocks are numbered 0 - 31 containing 128 pages each.
Page 0-127 --> Block 0; Page 128-255 --> Block 1;......Page 3968-4095 --> Block 31, and so on...

###### eraseBlock64K(address)
Erases one 64KB block - 256 pages - containing the address to be erased. The blocks are numbered 0 - 15 containing 256 pages each.
// Page 0-255 --> Block 0; Page 256-511 --> Block 1;......Page 3840-4095 --> Block 15, and so on...

###### eraseChip()
Erases entire chip. Use with care.

###### eraseSection(address, sizeOfData)
Erases the specific number of blocks/sectors to fit data (size defined by the sizeOfData arguement) into. When a user requires a large and variable (between writes) amount of data to be written to the flash memory on the fly and to have the correct amount of space erased to fit the data, this function will automatically calculate and erase the right amount of space to fit the data.

Please note that if the the amount of data being written is consistently the same size, the pre-existing 'flash.eraseSector()', 'flash.eraseBlock32K()' and 'flash.eraseBlock64K()' functions will operate a lot faster.
<hr>

##### Suspend/Resume commands
<hr>

###### suspendProg()
Suspends current Block Erase/Sector Erase/Page Program. Does not suspend chipErase(). Page Program, Write Status Register, Erase instructions are not allowed. Erase suspend is only allowed during Block/Sector erase. Program suspend is only allowed during Page/Quad Page Program

###### resumeProg()
Resumes previously suspended Block Erase/Sector Erase/Page Program.
<hr>

##### Power operation commands
<hr>

###### powerDown()
Puts device in low power state. Useful for battery powered operations. Typical current consumption during power-down is 1mA with a maximum of 5mA. (Datasheet 7.4). In powerDown() the chip will only respond to powerUp()

###### powerUp()
Wakes chip from low power state.
<hr>

##### Error codes explained

* **0x00**    -    Action completed successfully. No Error.
* **0x01**    -    *constructor_of_choice*.begin() was not called in void setup()
* **0x02**    -    Unable to identify chip. Are you sure this is a Winbond Flash chip? Please raise an issue [here](http://www.github.com/Marzogh/SPIMemory/issues) with your chip type and I will try to add support to your chip
* **0x03**    -    Unable to identify capacity. Please raise an issue [here](http://www.github.com/Marzogh/SPIMemory/issues) with your chip type and I will work on adding support to your chip
* **0x04**    -    Chip is busy. Make sure all pins have been connected properly. If it still doesn't work,please raise an issue [here](http://www.github.com/Marzogh/SPIMemory/issues) with the details of what your were doing when this error occurred
* **0x05**    -    Page overflow has been disabled and the address called exceeds the memory
* **0x06**    -    Unable to Enable Writing to chip. Please make sure the HOLD & WRITEPROTECT pins are connected properly to VCC & GND respectively. If you are still facing issues, please raise an issue [here](http://www.github.com/Marzogh/SPIMemory/issues) with the details of what your were doing when this error occurred
* **0x07**    -    This sector already contains data. Please make sure the sectors being written to are erased. If you are still facing issues, please raise an issue [here](http://www.github.com/Marzogh/SPIMemory/issues) with the details of what your were doing when this error occurred.
* **0x08**    -    You are running low on SRAM. Please optimise your program for better RAM usage
* **0x09**    -    Unable to suspend/resume operation.
* **0x0A**    -    Write Function has failed errorcheck.
* **0x0B**    -    Check your wiring. Flash chip is non-responsive.
* **0x0C**    -    This function is not supported by the flash memory hardware.
* **0x0D**    -    Unable to enable 4-byte addressing.
* **0x0E**    -    Unable to disable 4-byte addressing.
* **0xFE**    -    Unknown error. Please raise an issue [here](http://www.github.com/Marzogh/SPIMemory/issues) with the details of what your were doing when this error occurred
<hr>

###### How to get data off Flash memory via Serial
<sub>(Works only for Unix based Operating Systems)</sub>

 - Make sure you include code to let you dump entire flash memory/specific address' content to Serial (Refer to the code in the _TestFlash.h_ for details on how to do this)
 - Connect your Arduino board to the computer.
 - Open the Arduino IDE, the IDE's Serial Monitor, and an OSX POSIX terminal.
 - Type the following command into the terminal window. ```% tail -f /dev/tty.usbmodem1411 > FlashDump.txt``` Make sure to replace the _/dev/tty.usbmodem1411_ with the port your arduino is connected to. (You can find this in Tools --> Ports in Arduino IDE 1.6.x)
 - Then type the command to read all pages into the Serial console. If you use my code from the example file the command is ```read_all_pages```
 - Wait a few seconds before typing ```Ctrl+C``` to end the tail process
 - Check that you have actually received all the data by typing ```% cat FlashDump.txt```. This should output the entire text file into your terminal window.
