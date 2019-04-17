
#include "Storage.h"

Storage::Storage():size(EEPROM.length()){}

byte Storage::readByte(const uint pos){
    // read single byte from position
    if(pos>=size){
        ERROR=1;
        return 0;
    }
    
    ERROR=0;
    return EEPROM.read(pos);
}

uint Storage::readBytes(byte arr[], uint bytes, uint offset){
    // this method is NOT safe as it does not check array bounds!
    uint bytes_read = 0;
    for(uint pos=offset; (bytes_read<bytes) && (pos<size); ++pos, ++bytes_read){
        arr[bytes_read] = EEPROM.read(pos);
    }
    
    ERROR = (bytes_read==bytes)?0:1;
    
    return bytes_read;
}

bool Storage::readObject(void *obj, size_t obj_size, uint offset){
    // read any data type from the permanent storage;
    
    if(obj_size>size || ((offset+obj_size)>=size)){ERROR=1; return false;}
    
    if(readBytes((byte*)obj,obj_size,offset)!=obj_size){ERROR=1; return false;}

    ERROR=0;
    return true;
}

bool Storage::writeByte(const byte b, const uint pos){
    // write single bye to position
    if(pos>=size){ERROR=1;return false;}
    
    EEPROM.write(pos,b);
    
    ERROR=0;
    return true;
}


uint Storage::writeBytes(const byte arr[], uint bytes, uint offset){
    // this method is NOT safe as it does not check array bounds!

    if((offset+bytes)>=size){ERROR=1; return 0;} // abort if data will go outside memory bounds
    
    uint bytes_written = 0;
    for(uint pos=offset, arr_pos=0; (bytes_written<bytes) && (pos<size); ++pos, ++arr_pos, ++bytes_written){
        EEPROM.write(pos,arr[arr_pos]);
    }

    ERROR = (bytes_written==bytes)?0:1;
    return bytes_written;
}

bool Storage::writeObject(const void *obj, size_t obj_size, uint offset){
    if(obj_size>size || ((offset+obj_size)>=size)){ERROR=1; return false;}
    
    if(writeBytes((byte*)obj,obj_size,offset)!=obj_size){ERROR=1; return false;}

    ERROR=0;
    return true;
}


bool Storage::byteIs(const uint pos, const byte b){
    // check if byte in position pos is b. This provides a simple interface for checking file signatures
    if (pos>=size){ERROR=1; return false;}
    
    ERROR=0;
    return EEPROM.read(pos)==b;
}


long Storage::searchAvailable(const uint bytes){
    // search in memory and see if there are `bytes` contigous cells all set to 0
    // notice the return value is signed as the function will return -1 if the space wasnt found
    long location = -1;

    if(!bytes || (bytes>size)){ERROR=1; return location;}

    uint start=0, end=0;
    byte last_byte = 1, current_byte;
    
    for(uint pos=0; (end-start)<bytes && pos<size; ++pos){
        current_byte = EEPROM.read(pos);
        
        if(current_byte){
            if(!last_byte){
                end = pos;
            }
        }else{
            if(last_byte){
                start = pos;
                end = pos;
            }else{++end;}
        }
        
        last_byte = current_byte;
    }
    
    if((end-start)>=bytes){location=start;}

    ERROR=0;
    return location;
}

bool Storage::clear(){
    for(uint pos=0; pos<size; ++pos){
        EEPROM.write(pos,0);
    }

    ERROR=0;
    return true;
}

bool Storage::clearSection(const uint start, const uint end){
    // clear section of store ie re-write everything here with 0
    // the cells starting from `start` to `end`(both inclusive) are wiped
    if ((start>=end)||(end>=size)){ERROR=1; return false;}

    for(uint pos=0; pos<=end; ++pos){
        EEPROM.write(pos,0);
    }

    ERROR=0;
    return true;
}


uint Storage::capacity()const{
    return size;
}

////////////////////////////////////////////////READ SPECIFIC TYPES///////////////////////////////////////////////

uint8_t Storage::readUint8_t(const uint pos){
    uint8_t cell = readByte(pos);
    return cell;
}
uint16_t Storage::readUint16_t(const uint pos){
    uint16_t block;
    readBytes((byte*)&block,2,pos);
    return block;
}
uint32_t Storage::readUint32_t(const uint pos){
    uint32_t block;
    readBytes((byte*)&block,4,pos);
    return block;
}
uint64_t Storage::readUint64_t(const uint pos){
    uint64_t block;
    readBytes((byte*)&block,8,pos);
    return block;
}

boolean Storage::readBoolean(const uint pos){return readByte(pos);}
boolean Storage::readBool(const uint pos){return readByte(pos);}
char Storage::readChar(const uint pos){return readByte(pos);}
word Storage::readWord(const uint pos){
    word block;
    readBytes((byte*)&block, sizeof(block), pos);
    return block;
}
int Storage::readInt(const uint pos){
    int block;
    readBytes((byte*)&block, sizeof(block), pos);
    return block;
}
long Storage::readLong(const uint pos){
    long block;
    readBytes((byte*)&block, sizeof(block), pos);
    return block;
}
float Storage::readFloat(const uint pos){
    float block;
    readBytes((byte*)&block, sizeof(block), pos);
    return block;
}
double Storage::readDouble(const uint pos){
    double block;
    readBytes((byte*)&block, sizeof(block), pos);
    return block;
}

bool Storage::writeUint8_t(const uint8_t value, const uint pos){return writeByte(value,pos);}
bool Storage::writeUint16_t(const uint16_t value, const uint pos){return writeBytes((byte*)&value,sizeof(value),pos);}
bool Storage::writeUint32_t(const uint32_t value, const uint pos){return writeBytes((byte*)&value,sizeof(value),pos);}
bool Storage::writeUint64_t(const uint64_t value, const uint pos){return writeBytes((byte*)&value,sizeof(value),pos);}

bool Storage::writeBoolean(const boolean value, const uint pos){return writeBytes((byte*)&value,sizeof(value),pos);}
bool Storage::writeBool(const bool value, const uint pos){return writeBytes((byte*)&value,sizeof(value),pos);}
bool Storage::writeChar(const char value, const uint pos){return writeBytes((byte*)&value,sizeof(value),pos);}
bool Storage::writeWord(const word value, const uint pos){return writeBytes((byte*)&value,sizeof(value),pos);}
bool Storage::writeInt(const int value, const uint pos){return writeBytes((byte*)&value,sizeof(value),pos);}
bool Storage::writeLong(const long value, const uint pos){return writeBytes((byte*)&value,sizeof(value),pos);}
bool Storage::writeFloat(const float value, const uint pos){return writeBytes((byte*)&value,sizeof(value),pos);}
bool Storage::writeDouble(const double value, const uint pos){return writeBytes((byte*)&value,sizeof(value),pos);}

bool Storage::readArray(byte *arr, const size_t length, const uint type_size, const uint pos){
    size_t bytes = length*type_size;
    
    return readBytes(arr,bytes,pos);
}
bool Storage::writeArray(byte *arr, const size_t length, const uint type_size, const uint pos){
    size_t bytes = length*type_size;

    writeBytes(arr,bytes,pos);
    
    return !ERROR;
}

bool Storage::readMultiArray(byte *arr, const uint dimensions_product, const uint type_size, uint pos){
    return readArray(arr,dimensions_product,type_size,pos);
}

bool Storage::writeMultiArray(byte *arr, const uint dimensions_product, const uint type_size, uint pos){
    return writeArray(arr,dimensions_product,type_size,pos);
}
