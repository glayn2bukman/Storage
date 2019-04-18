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
if(pos=store.searchAvailable(sizeof(str)), !store.ERROR){/*a position was found where the entire string could fit*/}
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
if(store.readArray(marks, ARRAY_SIZE, sizeof(marks[0]), 80)){
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
if(store.readMultiArray(board, ROWS*COLS, sizeof(board[0]), 50)){
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

###### bool writeArray(void *arr, const size_t length, const uint type_size, const uint pos);
```cpp
#define ARRAY_SIZE (5)

float factors[ARRAY_SIZE] = {2,6,3,7,9};
if(store.writeArray(factors, ARRAY_SIZE, sizeof(factors[0]), 80)){
    Serial.print("done saving array");
}else{
    Serial.println("failed to save array from memory");
}
```

###### bool writeMultiArray(void *arr, const uint dimensions_product, const uint type_size, uint pos);
```cpp
#define ROWS (4)
#define COLS (3)

int board[ROWS][COLS] = {{1,2,3},{4,5,6},{7,8,9},{5,1,3}};
if(store.writeMultiArray(board, ROWS*COLS, sizeof(board[0]), 50)){
    Serial.print("done saving multi-dimensional array:\n");
}else{
    Serial.println("failed to save multi-dimensional array from memory");
}
```

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

### Examples

#### Save/Load Numbers
```cpp
/*
  simple read/write operations for numbers. notice the use of the comma operator in read* operations to check if error
  occured
*/
#include<Storage.h>
void setup() {
  Serial.begin(9600);
}

int   I=0;
float F=0.0;
char  C='\0';

// this offset could be anything but this value was carefully chosen so that the other examples
// in this library could not be affected
const uint8_t OFFSET = 17;

const uint8_t SIGNATURE[] = {12,11};

Storage store;

void loop() {
  Serial.print("max memory capacity: ");
  Serial.print(store.capacity());  
  Serial.print(" bytes\n");  
  
  if(store.byteIs(OFFSET,SIGNATURE[0]) && store.byteIs(OFFSET+1,SIGNATURE[1])){
    // signature is present, we have to load the numbers from memory...
    Serial.println("signature found, loading numbers from memory...");

    if(I = store.readInt(OFFSET+2), !store.ERROR){
      Serial.print("done reading int:: ");
      Serial.print(I);
      Serial.print("\n");
    }else{
      Serial.println("failed to load int from memory");
    }

    if(F = store.readFloat(OFFSET+2+sizeof(I)), !store.ERROR){
      Serial.print("done reading float:: ");
      Serial.print(F);
      Serial.print("\n");
    }else{
      Serial.println("failed to load float from memory");
    }

    if(C = store.readChar(OFFSET+2+sizeof(I)+sizeof(F)), !store.ERROR){
      Serial.print("done reading character:: ");
      Serial.print(C);
      Serial.print("\n");
    }else{
      Serial.println("failed to load character from memory");
    }
    
  }else{
    Serial.println("signature not found, saving numbers now...");

    // first clear the needed spaces...
    store.clearSection(OFFSET,OFFSET+2+sizeof(I)+sizeof(F)+sizeof(C));
    
    // write the signature...
    store.writeByte(SIGNATURE[0], OFFSET);
    store.writeByte(SIGNATURE[1], OFFSET+1);

    if(!store.writeInt(2589,OFFSET+2)){
      Serial.println("failed to write the int to memory!");
    }else{
      Serial.println("written int to memory...");
    }

    if(!store.writeFloat(9.16,OFFSET+2+sizeof(I))){
      Serial.println("failed to write the float to memory!");
    }else{
      Serial.println("written float to memory...");
    }

    if(!store.writeChar('K',OFFSET+2+sizeof(I)+sizeof(F))){
      Serial.println("failed to write the character to memory!");
    }else{
      Serial.println("written character to memory...");
    }  
  }

  Serial.println();

  delay(2000);
}
```

#### Save/Load String
```cpp
/*
check if signature(first bytes are 13 & 11) is present.
  * if present: load string from memory
  * otherwise:  write string to memory

  methods used here:
    bool byteIs(const uint pos, const byte b);
    bool readObject(void *obj, size_t obj_size, uint offset=0);
    bool writeObject(const void *obj, size_t obj_size, uint offset=0);

    Note: for this example, storage.readBytes could be interchanged with storage.readObject and the same
          applies to storage.writeBytes and storage.writeObject
*/

#include <Storage.h>

Storage store;

void setup() {
  Serial.begin(9600);
}

const char _str[] = "sample string!";
char str[15];

const uint8_t SIGNATURE[]={13,11};

const uint8_t OFFSET=0;

void loop() {
  Serial.print("max memory capacity: ");
  Serial.print(store.capacity());  
  Serial.print(" bytes\n");  

  if(store.byteIs(OFFSET,SIGNATURE[0])&&store.byteIs(OFFSET+1,SIGNATURE[1])){
    // signature is present, we have to load the string from memory...
    Serial.println("signature found, loading string from memory...");

    if(store.readObject(str,sizeof(str),OFFSET+2)){
      Serial.print("done reading string:: ");
      Serial.print(str);
      Serial.print("\n\n");
    }else{
      Serial.println("failed to load string from memory");
    }
  }else{
    Serial.println("signature not found, creating string now...");

    // first clear the needed spaces...
    store.clearSection(OFFSET,OFFSET+sizeof(_str)+1);
    
    // write the signature...
    store.writeByte(SIGNATURE[0], OFFSET);
    store.writeByte(SIGNATURE[1], OFFSET+1);

    if(!store.writeObject(_str,sizeof(_str),OFFSET+2)){
      Serial.println("failed to write the string to memory!");
    }else{
      Serial.println("written string to memory...");
    }
  }

  delay(2000);
}
```

#### Save/Load Objects
```cpp
#include <Storage.h>

#define ROWS (4)
#define COLS (3)

void setup() {Serial.begin(9600);}

Storage store;

// this offset could be anything but this value was carefully chosen so that the other examples
// in this library could not be affected
const uint8_t OFFSET = 100;

const uint8_t SIGNATURE[] = {9,7};

typedef struct {
  char name[10];
  int ID;
} Type;

Type obj;

void printObject(Type &t){
  Serial.print("object; name=\"");Serial.print(t.name);Serial.print("\", ID=");Serial.print(t.ID);
  Serial.println();
}

void loop() {
  Serial.print("max memory capacity: ");
  Serial.print(store.capacity());  
  Serial.print(" bytes\n");  

  if(store.byteIs(OFFSET,SIGNATURE[0]) && store.byteIs(OFFSET+1,SIGNATURE[1])){
    // signature is present, we have to load the array from memory...
    Serial.println("signature found, loading object from memory...");

    if(store.readObject(&obj, sizeof(obj), OFFSET+2)){
      Serial.print("done reading object:\n");
      printObject(obj);
    }else{
      Serial.println("failed to load object from memory");
    }
    
  }else{
    Serial.println("signature not found, saving object now...");

    // first clear the needed spaces...
    store.clearSection(OFFSET,OFFSET+2+sizeof(obj));
    
    // write the signature...
    store.writeByte(SIGNATURE[0], OFFSET);
    store.writeByte(SIGNATURE[1], OFFSET+1);

    Type _obj{"first obj", 9};

    if(store.writeObject(&_obj, sizeof(_obj), OFFSET+2)){
      Serial.print("done saving object: ");
    }else{
      Serial.println("failed to save object to memory");
    }
  }

  Serial.println();

  delay(2000);
}
```

#### Save/Load Array
```cpp
#include <Storage.h>

#define ARRAY_SIZE (5)

void setup() {Serial.begin(6900);}

Storage store;

// this offset could be anything but this value was carefully chosen so that the other examples
// in this library could not be affected
const uint8_t OFFSET = 50;

const uint8_t SIGNATURE[] = {14,17};

float factors[ARRAY_SIZE];

void loop() {
  Serial.print("max memory capacity: ");
  Serial.print(store.capacity());  
  Serial.print(" bytes\n");  

  if(store.byteIs(OFFSET,SIGNATURE[0]) && store.byteIs(OFFSET+1,SIGNATURE[1])){
    // signature is present, we have to load the array from memory...
    Serial.println("signature found, loading array from memory...");

    if(store.readArray(factors, ARRAY_SIZE, sizeof(factors[0]), OFFSET+2)){
      Serial.print("done reading array: ");
      for(unsigned int i=0; i<ARRAY_SIZE; ++i){
        Serial.print(factors[i]);
        Serial.print(" ");
      }Serial.print("\n");
    }else{
      Serial.println("failed to load array from memory");
    }
    
  }else{
    Serial.println("signature not found, saving array now...");

    // first clear the needed spaces...
    store.clearSection(OFFSET,OFFSET+2+sizeof(factors));
    
    // write the signature...
    store.writeByte(SIGNATURE[0], OFFSET);
    store.writeByte(SIGNATURE[1], OFFSET+1);

    float _facs[] = {1.7,2.9,3.6,4.1,2.8};

    if(store.writeArray(_facs, ARRAY_SIZE, sizeof(_facs[0]), OFFSET+2)){
      Serial.print("done saving array: ");
    }else{
      Serial.println("failed to save array to memory");
    }
  }

  Serial.println();

  delay(2000);
}
```

#### Save/Load Miltidimensional array
```cpp
#include <Storage.h>

#define ROWS (4)
#define COLS (3)

void setup() {Serial.begin(9600);}

Storage store;

// this offset could be anything but this value was carefully chosen so that the other examples
// in this library could not be affected
const uint8_t OFFSET = 70;

const uint8_t SIGNATURE[] = {15,9};

int board[ROWS][COLS]; // 2d array

void print2dArray(int arr[ROWS][COLS]){
  for(int r=0; r<ROWS; ++r){
    Serial.print("\nrow ");
    Serial.print(r+1);
    Serial.print(":: ");

    for(int c=0; c<COLS; ++c){
      Serial.print(arr[r][c]);
      Serial.print(" ");
    }
  }Serial.println();
}

void loop() {
  Serial.print("max memory capacity: ");
  Serial.print(store.capacity());  
  Serial.print(" bytes\n");  

  if(store.byteIs(OFFSET,SIGNATURE[0]) && store.byteIs(OFFSET+1,SIGNATURE[1])){
    // signature is present, we have to load the array from memory...
    Serial.println("signature found, loading array from memory...");

    if(store.readMultiArray(board, ROWS*COLS, sizeof(board[0]), OFFSET+2)){
      Serial.print("done reading multi-dimensional array:\n");
      print2dArray(board);
    }else{
      Serial.println("failed to load multi-dimensional array from memory");
    }
    
  }else{
    Serial.println("signature not found, saving array now...");

    // first clear the needed spaces...
    store.clearSection(OFFSET,OFFSET+2+sizeof(board));
    
    // write the signature...
    store.writeByte(SIGNATURE[0], OFFSET);
    store.writeByte(SIGNATURE[1], OFFSET+1);

    int arr[ROWS][COLS] = {{1,2,3},{4,5,6},{7,8,9},{5,1,3}};

    if(store.writeMultiArray(arr, ROWS*COLS, sizeof(board[0]), OFFSET+2)){
      Serial.print("done saving multi-dimensional array: ");
    }else{
      Serial.println("failed to save multi-dimensional array to memory");
    }
  }

  Serial.println();

  delay(2000);
}
```

### Bug Reports
Please report any bugs or issues/concerns/suggested-updates to **glayn2bukman@gmail.com**