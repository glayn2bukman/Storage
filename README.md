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


<hr>

##### Non Read/Write commands

###### `capacity()`
Returns the maximum memory in bytes eg for 1Kb, the method will return 1024
<hr>

##### Read commands
<hr>
<sub>
All read/write methods set the attribute ```ERROR``` to true/false indicating if an error happened(when ERROR is true) or not. This is especially usefull for methods that dont return ```bool```
</sub>

###### long searchAvailable(const uint bytes);
Searches the memory for "free space" and returns a position where ```bytes``` bytes can be stored contigiously. eg 
```cpp
char str[] = "this is a simple string";

long pos;
// search for where we can save the string
if(pos=store.searchAvailable(sizeof(str), !store.ERROR){/*a position was found where the entire string could fit*/}
else{/*failed to get a suitable position where to store the string*/}
```

###### byte readByte(const uint pos);
Reads a single byte in position. eg 
```cpp
char b;
if(b=store.readByte(15), store.ERROR){/*error occured eg position was out of memory range*/}
else{Serial.print("byte read: "); Serial.print(b);}
```

###### bool byteIs(const uint pos, const byte b);
Checks if the given byte ```b``` is the same as that at index ```pos``` in memory. eg 
```cpp
if(store.byteIs(15,'A')){/*byte at index 15 is 'A'*/}
else{/*error occured*/}
```

###### uint readBytes(byte arr[], uint bytes, uint offset);
Reads ```bytes``` bytes into array and returns the bytes read. eg
```cpp
char str[10];
if(!store.readBytes(str,8,0)){/*error occured eg position was out of memory range*/}
else{Serial.print("string: "); Serial.print(str);}
```

###### bool readObject(void *obj, size_t obj_size, uint offset);
Reads object from memory. eg
```cpp
struct {
  char name[10];
  int ID;
} obj;

if(store.readObject(&obj, sizeof(obj), 20)){/*object loaded from memory*/}
else{/*failed to load object from memory*/}
```

###### uint8_t readUint8_t(const uint pos);
read a ```uint8_t``` from index ```pos```. eg 
```cpp
uint8_t b;
if(b=store.readUint8_t(12), !store.ERROR){/*successully read uint8_t at index 12*/}
else{/*error occured*/}
```

###### uint16_t readUint16_t(const uint pos);

###### uint32_t readUint32_t(const uint pos);

###### uint64_t readUint64_t(const uint pos);

###### boolean readBoolean(const uint pos);

###### boolean readBool(const uint pos);

###### char readChar(const uint pos);

###### word readWord(const uint pos);

###### int readInt(const uint pos);

###### long readLong(const uint pos);

###### float readFloat(const uint pos);

###### double readDouble(const uint pos);

###### bool readArray(void *arr, const size_t length, const uint type_size, const uint pos);
Read array from memory. eg
```cpp
#define ARRAY_SIZE (20)

int marks[ARRAY_SIZE];
if(store.readArray(marks, ARRAY_SIZE, sizeof(int), 80)){
    Serial.print("done reading array: ");
    for(unsigned int i=0; i<ARRAY_SIZE; ++i){
        Serial.print(marks[i]);
        Serial.print(" ");
    }Serial.print("\n");
}else{
    Serial.println("failed to load array from memory");
}
```

###### bool readMultiArray(void *arr, const uint dimensions_product, const uint type_size, uint pos);
Read multi-dimentional array from memory. eg
```cpp
#define ROWS (4)
#define COLS (3)

int board[ROWS][COLS]; // 2d array
if(store.readMultiArray(board, ROWS*COLS, sizeof(int), 50)){
    Serial.print("done reading multi-dimensional array:\n");
}else{
    Serial.println("failed to load multi-dimensional array from memory");
}
```

<hr>

##### Write commands
<hr>

###### bool writeByte(const byte b, const uint pos);

###### uint writeBytes(const byte arr[], uint bytes, uint offset);

###### bool writeObject(const void *obj, size_t obj_size, uint offset);

###### bool writeUint8_t(const uint8_t value, const uint pos);

###### bool writeUint16_t(const uint16_t value, const uint pos);

###### bool writeUint32_t(const uint32_t value, const uint pos);

###### bool writeUint64_t(const uint64_t value, const uint pos);

###### bool writeBoolean(const boolean value, const uint pos);

###### bool writeBool(const bool value, const uint pos);

###### bool writeChar(const char value, const uint pos);

###### bool writeWord(const word value, const uint pos);

###### bool writeInt(const int value, const uint pos);

###### bool writeLong(const long value, const uint pos);

###### bool writeFloat(const float value, const uint pos);

###### bool writeDouble(const double value, const uint pos);

<hr>

##### Erase commands
<hr>

###### bool clearSection(const uint start, const uint end);
Clears a section of memory with ```start``` and ```end``` inclusive. eg
```cpp
if(store.clearSection(5,20)){/*cleared blocks from index 5 to 20*/}
else{/*failed to perform operation. are the limits within the memory bounds?*/}
```

###### bool clear();
Clears the entire memory(sets all bytes to zero)
