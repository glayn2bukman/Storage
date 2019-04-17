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

        uint readBytes(byte arr[], uint bytes, uint offset);
        uint writeBytes(const byte arr[], uint bytes, uint offset);

        bool readObject(void *obj, size_t obj_size, uint offset);        
        bool writeObject(const void *obj, size_t obj_size, uint offset);
        
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
        // carefull when trying to store arrays os pointers, only do this if you understand object serialisation
        // for multidimensional arrays, the concenpt is simple; all arrays are stored in contigous memory
        // hence the multidimensional array can be treated as a byte 1d array whose size is the product of all the
        // dimesntions multiplied by the type size eg
        //      int A[M][N]; is seen as
        //      byte A[M*N*sizeof(int)];
        //
        // NB: when using reading or writting arrays, always cast your array to (byte*)
        bool readArray(byte *arr, const size_t length, const uint type_size, const uint pos);
        bool readMultiArray(byte *arr, const uint dimensions_product, const uint type_size, uint pos);

        bool writeArray(byte *arr, const size_t length, const uint type_size, const uint pos);
        bool writeMultiArray(byte *arr, const uint dimensions_product, const uint type_size, uint pos);
};

#endif