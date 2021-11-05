#include"Terrain.h"
#include<GLFW/glfw3.h>

void Terrain::generate()
{
	unsigned int vertexModifier[6] = { 0,10,1,11,1,10 };
	int quad[] = { 0,0 };
	float tScale = 5;

	for (int z = 0; z < size; z++)
	{
		for (int x = 0; x < size; x++)
		{
			int currentSquare = (x * size + z) * coordsPerVertex * 3 * 2;
			float textureX = quad[0] % (int)tScale;
			float textureY = quad[1] % (int)tScale;

			glm::vec3 p2 = glm::vec3(x + 1,		height[(x + 1) * (size + 1) + z],		z);
			glm::vec3 p1 = glm::vec3(x,			height[(x) * (size + 1) + z],			z);
			glm::vec3 p3 = glm::vec3(x,			height[(x) * (size + 1) + z + 1],		z + 1);
			glm::vec3 p4 = glm::vec3(x + 1,		height[(x + 1) * (size + 1) + z + 1],	z + 1);

			glm::vec3 v1 = p2 - p1;
			glm::vec3 v2 = p3 - p2;
			glm::vec3 v3 = p4 - p3;

			glm::vec3 normal[2] = { glm::cross(v2, v1),glm::cross(v2, v3) };

			for (int i = 0; i < 6; i++)
			{
				int indexOffset = currentSquare + (i * coordsPerVertex);

				vertexData[indexOffset + 0] = (x + vertexModifier[i] / 10) * scale;
				vertexData[indexOffset + 1] = height[(x + vertexModifier[i] / 10) * (size+1) + (z + vertexModifier[i] % 10)] * scale;
				vertexData[indexOffset + 2] = (z + vertexModifier[i] % 10) * scale;

				vertexData[indexOffset + 3] = normal[i / 3].x;
				vertexData[indexOffset + 4] = normal[i / 3].y;
				vertexData[indexOffset + 5] = normal[i / 3].z;

				vertexData[indexOffset + 6] = textureX / tScale + vertexModifier[i] / 10 / tScale;
				vertexData[indexOffset + 7] = textureY / tScale + vertexModifier[i] % 10 / tScale;
			}
			quad[1]++;
		}
		quad[0]++;
	}
}

float Terrain::getHeightAt(float x, float y)
{
	return height[(int)x * (size+1) + (int)y];
}

unsigned int Terrain::getCoordsPerVertex()
{
	return coordsPerVertex;
}

unsigned int Terrain::getVertexCount()
{
	return triangleCount*3;
}

float* Terrain::getVertexData()
{
	return vertexData;
}

float Terrain::getScale()
{
	return scale;
}

int Terrain::getSize()
{
	return size;
}