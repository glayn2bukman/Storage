#include <Storage.h>

#define ROWS (4)
#define COLS (3)

void setup() {Serial.begin(9600);}

Storage store;

// this offset could be anything but this value was carefully chosen so that the other examples
// in this library could not be affected
const uint8_t OFFSET = 50;

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

    // storage array methods take a byte* so we cast board to byte*
    if(store.readMultiArray((byte*)board, ROWS*COLS, sizeof(int), OFFSET+2)){
      Serial.print("done reading multi-dimensional array:\n");
      print2dArray(board);
    }else{
      Serial.println("failed to load multi-dimensional array from memory");
    }
    
  }else{
    Serial.println("signature not found, saving array now...");

    // first clear the needed spaces...
    store.clearSection(OFFSET,OFFSET+2+sizeof(int)*sizeof(board));
    
    // write the signature...
    store.writeByte(SIGNATURE[0], OFFSET);
    store.writeByte(SIGNATURE[1], OFFSET+1);

    int arr[ROWS][COLS] = {{1,2,3},{4,5,6},{7,8,9},{5,1,3}};

    // storage array methods take a byte* so we cast arr to byte*
    if(store.writeMultiArray((byte*)arr, ROWS*COLS, sizeof(int), OFFSET+2)){
      Serial.print("done saving multi-dimensional array: ");
    }else{
      Serial.println("failed to save multi-dimensional array to memory");
    }
  }

  Serial.println();

  delay(2000);
}
