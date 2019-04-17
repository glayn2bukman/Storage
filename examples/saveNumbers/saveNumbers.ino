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
