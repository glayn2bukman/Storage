#include <Storage.h>
void setup() {Serial.begin(6900);}

Storage store;

// this offset could be anything but this value was carefully chosen so that the other examples
// in this library could not be affected
const uint8_t OFFSET = 50;

const uint8_t SIGNATURE[] = {14,17};

float factors[5];

void loop() {
  Serial.print("max memory capacity: ");
  Serial.print(store.capacity());  
  Serial.print(" bytes\n");  

  if(store.byteIs(OFFSET,SIGNATURE[0]) && store.byteIs(OFFSET+1,SIGNATURE[1])){
    // signature is present, we have to load the array from memory...
    Serial.println("signature found, loading array from memory...");

    // storage array methods take a byte* so we cast factors to byte*
    if(store.readArray((byte*)factors, sizeof(factors), sizeof(float), OFFSET+2)){
      Serial.print("done reading array: ");
      for(unsigned int i=0; i<5; ++i){
        Serial.print(factors[i]);
        Serial.print(" ");
      }Serial.print("\n");
    }else{
      Serial.println("failed to load array from memory");
    }
    
  }else{
    Serial.println("signature not found, saving array now...");

    // first clear the needed spaces...
    store.clearSection(OFFSET,OFFSET+2+sizeof(float)*sizeof(factors));
    
    // write the signature...
    store.writeByte(SIGNATURE[0], OFFSET);
    store.writeByte(SIGNATURE[1], OFFSET+1);

    float _facs[] = {1.7,2.9,3.6,4.1,2.8};

    // storage array methods take a byte* so we cast _facs to byte*
    if(store.writeArray((byte*)_facs, 5, sizeof(float), OFFSET+2)){
      Serial.print("done saving array: ");
    }else{
      Serial.println("failed to save array to memory");
    }
  }

  Serial.println();

  delay(2000);
}