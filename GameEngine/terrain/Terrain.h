#pragma once
#include<iostream>
#include<glm/glm.hpp>
#include<vector>
#include<glm/glm.hpp>
#include<utility/PerlinNoise.h>

class Terrain
{
private:
	int size;
	float* vertexData;
	float* height;
	unsigned int coordsPerVertex, triangleCount;
	float variance, scale;

public:
	Terrain(int size, float scale, float variance)
	{
		this->size = size;
		this->scale = scale;
		this->coordsPerVertex = 8;
		this->vertexData = new float[size * size * 2 * 3 * coordsPerVertex];
		this->triangleCount = size * size * 2;
		this->variance = variance;
		this->height = new float[(size + 1) * (size + 1)];

		PerlinNoise perlin;
		perlin.heightMap(size + 1, variance, true, this->height);

		generate();
	}

	~Terrain()
	{
		delete[] vertexData;
		delete[] height;
	}

	void generate();
	float getHeightAt(float x, float y);
	int getSize();
	float getScale();
	unsigned int getCoordsPerVertex();
	unsigned int getVertexCount();
	float* getVertexData();
};