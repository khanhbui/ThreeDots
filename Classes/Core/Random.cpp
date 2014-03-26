#include "Random.h"
#include "cocos2d.h"

unsigned int Random::x = 123456789;
unsigned int Random::y = 362436069;
unsigned int Random::z = 521288629;
unsigned int Random::w = 88675123;

void Random::setSeeds(unsigned int seeds[4]) {
    x = (!seeds[0]) ? 123456789 : seeds[0];
    y = (!seeds[1]) ? 362436069 : seeds[1];
    z = (!seeds[2]) ? 521288629 : seeds[2];
    w = (!seeds[3]) ? 88675123 : seeds[3];

    CCASSERT((x | y | z | w) != 0, "seeds are wrong");
}

float Random::get() {
    return Random::getUInt32() / 4294967296.0;
}

unsigned int Random::getUInt32() {
    unsigned int t = x ^ (x << 11);
    
    cocos2d::log("%u, %u, %u, %u, %u", x, y, z, w, t);
    
    Random::x = Random::y;
    Random::y = Random::z;
    Random::z = Random::w;
    
    Random::w = (Random::w ^ Random::bit_rol(Random::w, 19)) ^ (t ^ Random::bit_rol(t, 8));
    
    cocos2d::log("--> %u, %u, %u, %u, %u, %u", x, y, z, w, t, Random::bit_rol(Random::w, 0));
    
    return Random::bit_rol(Random::w, 0);
}

unsigned int Random::bit_rol(unsigned int num, unsigned int cnt)
{
    cocos2d::log("bit_rol num = %u, cnt= %u", num, cnt);
	unsigned int & unsigned_num = reinterpret_cast< unsigned int & >(num);
	unsigned_num = (unsigned_num >> cnt);
    cocos2d::log("--> bit_rol num = %u, cnt = %u, u = %u", num, cnt, unsigned_num);
	return unsigned_num;
}