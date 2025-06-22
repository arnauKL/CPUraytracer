//
// Created by depre on 04/02/2025.
//

#ifndef RANDOM_H
#define RANDOM_H


#include <random>

class Random {
public:
    Random() : gen(std::random_device{}()), dist(0.0, 1.0) {}

    // If no parameters are entered, returns value between 0 and 1
    double              rndDouble() { return dist(gen); }
    float               rndFloat()  { return static_cast<float>(dist(gen)); }
    float               rndFloat(const float min, const float max)  { return min + (max - min) * rndFloat(); }
    unsigned char       rndUchar()  { return static_cast<unsigned char>(dist(gen) * 256); }

private:
    std::mt19937 gen;
    std::uniform_real_distribution<> dist;
};



#endif //RANDOM_H
