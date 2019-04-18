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
