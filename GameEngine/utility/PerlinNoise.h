#pragma once
#include<vector>
#include<random>
#include<algorithm>
#include<numeric>
#include<iostream>
#include<glm/glm.hpp>

class PerlinNoise
{
private:
	const int PERMUTATION_SIZE = 256;
	std::vector<int> permutation;

	glm::vec2 constVec(int permutationVal);
	float lerp(float t, float x, float y);
	float fade(float t);
	float fractalMotion(float x, float y, int size, float variance, int fbmPassCount, float fbmScale);

public:
	PerlinNoise()
	{
		srand(NULL);
		permutation.resize(PERMUTATION_SIZE);
		std::iota(permutation.begin(), permutation.end(), 0);
		std::default_random_engine rng(rand());
		std::shuffle(permutation.begin(), permutation.end(), rng);
		permutation.insert(permutation.end(), permutation.begin(), permutation.end());
	}

	void heightMap(int size, float variance, bool applyFBM, float* noise);
	float noise2d(int x, int y, int size, float variance);
};

