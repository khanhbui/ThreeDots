#ifndef __RANDOM_H__
#define __RANDOM_H__

class Random
{
    static unsigned int x;
    static unsigned int y;
    static unsigned int z;
    static unsigned int w;
    
    static unsigned bit_rol(unsigned int num, unsigned int cnt);
public:
    Random();
    ~Random();
    
    static void setSeeds(unsigned int seeds[]);
    static float get();
    static unsigned int getUInt32();
};

#endif // __RANDOM_H__
