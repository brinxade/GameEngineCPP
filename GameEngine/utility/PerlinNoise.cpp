#include "PerlinNoise.h"

void PerlinNoise::heightMap(int size, float variance, bool applyFBM, float* noise)
{
	variance /= size;
	for (int x = 0; x < size; x++)
		for (int y = 0; y < size; y++)
			noise[(x * size + y)] = noise2d(x, y, size, variance);

	if (applyFBM)
	{
		for (int fbmPass = 2; fbmPass <= 32; fbmPass *= 2)
		{
			float fbmScale = fbmPass * variance;
			for (int x = 0; x < size; x++)
				for (int y = 0; y < size; y++)
					noise[(x * size + y)] += fractalMotion(x, y, size, variance, fbmPass, fbmScale);
		}
	}
}

float PerlinNoise::fractalMotion(float x, float y, int size, float variance, int fbmPass, float fbmScale)
{
	float x_variated = (float)x * fbmScale;
	float y_variated = (float)y * fbmScale;

	int x_perm = std::floor(x_variated);
	int y_perm = std::floor(y_variated);
	x_perm %= PERMUTATION_SIZE;
	y_perm %= PERMUTATION_SIZE;

	float xf = x_variated - std::floor(x_variated);
	float yf = y_variated - std::floor(y_variated);

	// Position Vectors for 4 corners of the permutation Grid Square
	glm::vec2 posBottomLeft = glm::vec2(xf, yf);
	glm::vec2 posBottomRight = glm::vec2(xf - 1, yf);
	glm::vec2 posTopRight = glm::vec2(xf - 1, yf - 1);
	glm::vec2 posTopLeft = glm::vec2(xf, yf - 1);

	// Permutation Values for the permutation Grid Square
	int pBottomLeft = permutation[permutation[x_perm] + y_perm];
	int pBottomRight = permutation[permutation[x_perm + 1] + y_perm];
	int pTopRight = permutation[permutation[x_perm + 1] + y_perm + 1];
	int pTopLeft = permutation[permutation[x_perm] + y_perm + 1];

	// Dot Products of Constant Vectors and Position vectors of the permutation Grid Square
	float dBottomLeft = glm::dot(posBottomLeft, constVec(pBottomLeft));
	float dBottomRight = glm::dot(posBottomRight, constVec(pBottomRight));
	float dTopRight = glm::dot(posTopRight, constVec(pTopRight));
	float dTopLeft = glm::dot(posTopLeft, constVec(pTopLeft));

	// Lerp factors
	float u = fade(xf);
	float v = fade(yf);

	return lerp(u,
		lerp(v, dBottomLeft, dTopLeft),
		lerp(v, dBottomRight, dTopRight)) * size * variance / (fbmPass * log(fbmPass));
}

float PerlinNoise::noise2d(int x, int y, int size, float variance)
{
	float x_variated = (float)x * variance;
	float y_variated = (float)y * variance;

	int x_perm = std::floor(x_variated);
	int y_perm = std::floor(y_variated);
	x_perm %= PERMUTATION_SIZE;
	y_perm %= PERMUTATION_SIZE;

	float xf = x_variated - std::floor(x_variated);
	float yf = y_variated - std::floor(y_variated);

	// Position Vectors for 4 corners of the permutation Grid Square
	glm::vec2 posBottomLeft = glm::vec2(xf, yf);
	glm::vec2 posBottomRight = glm::vec2(xf - 1, yf);
	glm::vec2 posTopRight = glm::vec2(xf - 1, yf - 1);
	glm::vec2 posTopLeft = glm::vec2(xf, yf - 1);

	// Permutation Values for the permutation Grid Square
	int pBottomLeft = permutation[permutation[x_perm] + y_perm];
	int pBottomRight = permutation[permutation[x_perm + 1] + y_perm];
	int pTopRight = permutation[permutation[x_perm + 1] + y_perm + 1];
	int pTopLeft = permutation[permutation[x_perm] + y_perm + 1];

	// Dot Products of Constant Vectors and Position vectors of the permutation Grid Square
	float dBottomLeft = glm::dot(posBottomLeft, constVec(pBottomLeft));
	float dBottomRight = glm::dot(posBottomRight, constVec(pBottomRight));
	float dTopRight = glm::dot(posTopRight, constVec(pTopRight));
	float dTopLeft = glm::dot(posTopLeft, constVec(pTopLeft));

	// Lerp factors
	float u = fade(xf);
	float v = fade(yf);

	return lerp(u,
		lerp(v, dBottomLeft, dTopLeft),
		lerp(v, dBottomRight, dTopRight)) * variance * size;
}

float PerlinNoise::lerp(float t, float x, float y)
{
	return x + t * (y - x);
}

float PerlinNoise::fade(float t)
{
	return ((6 * t - 15) * t + 10) * t * t * t;
}

glm::vec2 PerlinNoise::constVec(int permutationVal)
{
	int h = permutationVal % 4;
	glm::vec2 result;
	if (h == 0)
		result = { 1,1 };
	else if (h == 1)
		result = { -1,1 };
	else if (h == 2)
		result = { 1,-1 };
	else
		result = { -1,-1 };
	return result;
}