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
