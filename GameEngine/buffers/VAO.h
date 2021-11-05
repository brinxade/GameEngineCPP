#pragma once
#include<glad/glad.h>

class VAO
{
private:
	unsigned int vbo, ID;

	void getOffsets(unsigned int coordsPerVertex, unsigned int* textureOffset, unsigned int* normalOffset)
	{
		*normalOffset = coordsPerVertex >= 6?12:0;
		*textureOffset = coordsPerVertex >= 8?24:0;
	}

public:
	VAO(float* vertexData, int vertexCount, int coordsPerVertex)
	{
		glGenBuffers(1, &vbo);
		glGenVertexArrays(1, &ID);

		glBindVertexArray(ID);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexCount * coordsPerVertex, vertexData, GL_STATIC_DRAW);

		unsigned int textureOffset, normalOffset;
		getOffsets(coordsPerVertex,  &textureOffset, &normalOffset);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * coordsPerVertex, (void*)0);
		glEnableVertexAttribArray(0);
		
		if (normalOffset)
		{
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * coordsPerVertex, (void*)normalOffset);
			glEnableVertexAttribArray(1);
		}

		if (textureOffset)
		{
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * coordsPerVertex, (void*)textureOffset); 
			glEnableVertexAttribArray(2);
		}
	}

	void bind()
	{
		glBindVertexArray(ID);
	}

	unsigned int getID()
	{
		return ID;
	}
};