#pragma once
#include<model/Model.h>

class Triangle
{

public:
    const int vertexCount = 3;
    float* vertexData{
        new float[vertexCount * 8] {
             -1,-1,0, 0,0,0, 0,0,
             1,-1,0 ,0,0,0, 1,0,
             0,1,0, 0,0,0, 0.5f,1.0f
        }
    };

    Triangle()
    {

    }
};