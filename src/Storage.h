#ifndef _bukman_STORAGE_H
#   define _bukman_STORAGE_H

#include <Arduino.h>
#include <EEPROM.h>

typedef uint8_t byte;
typedef unsigned int uint;

class Storage{
    uint size;
    
    public:
        byte ERROR; // attribute to indicate if an operation went ok or not
        
        Storage();

        byte readByte(const uint pos);
        bool writeByte(const byte b, const uint pos);

        uint readBytes(byte arr[], uint bytes, uint offset=0);
        uint writeBytes(const byte arr[], uint bytes, uint offset=0);

        bool readObject(void *obj, size_t obj_size, uint offset=0);        
        bool writeObject(const void *obj, size_t obj_size, uint offset=0);
        
        bool byteIs(const uint pos, const byte b);
        
        long searchAvailable(const uint bytes);
        
        bool clearSection(const uint start, const uint end);
        bool clear();
        
        uint capacity()const;
        
        // interface to deal with common arduino types...
        // methods described here should work for both unsigned and signed types
        // NB: for these methods, check storage.ERROR to know if the operation was sucessfull or not

        // uintX_t are the base types for all other types and will be called by the other readType methods
        uint8_t readUint8_t(const uint pos);
        uint16_t readUint16_t(const uint pos);
        uint32_t readUint32_t(const uint pos);
        uint64_t readUint64_t(const uint pos);

        boolean readBoolean(const uint pos);
        boolean readBool(const uint pos);
        char readChar(const uint pos);
        word readWord(const uint pos);
        int readInt(const uint pos);
        long readLong(const uint pos);
        float readFloat(const uint pos);
        double readDouble(const uint pos);

        bool writeUint8_t(const uint8_t value, const uint pos);
        bool writeUint16_t(const uint16_t value, const uint pos);
        bool writeUint32_t(const uint32_t value, const uint pos);
        bool writeUint64_t(const uint64_t value, const uint pos);

        bool writeBoolean(const boolean value, const uint pos);
        bool writeBool(const bool value, const uint pos);
        bool writeChar(const char value, const uint pos);
        bool writeWord(const word value, const uint pos);
        bool writeInt(const int value, const uint pos);
        bool writeLong(const long value, const uint pos);
        bool writeFloat(const float value, const uint pos);
        bool writeDouble(const double value, const uint pos);

        // and now the arrays...
        bool readArray(void *arr, const size_t arr_size, const uint unit_element_size, const uint pos);
};

#endif