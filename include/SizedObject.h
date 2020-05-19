#ifndef __sized_object_h__
#define __sized_object_h__

template <size_t BYTES>
class SizedObject
{
public:

    void SetNthByte(size_t n, char val)
    {
        data[n] = val;
    }

    char GetNthByte(size_t n) const
    {
        return data[n];
    }

private:
    char data[BYTES];
};

#endif
