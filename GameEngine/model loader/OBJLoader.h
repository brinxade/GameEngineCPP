#pragma once
#include<string>
#include<iostream>
#include<fstream>
#include<sstream> 
#include<cstdint>
#include<vector>
#include<math/Vec2.h>
#include<math/Vec3.h>

class OBJLoader
{
private:
	std::string filename;
	std::vector<int> indexes;
	std::vector<float> vertexData;
	std::vector<Vec3> vertices, normals;
	std::vector<Vec2> uv;
	uint32_t vertexCount, normalCount, uvCount, faceCount, drawVertexCount;

	void load()
	{
		std::ifstream file(filename);
		if (file.is_open())
		{
			std::string line, token, face;
			float v1 = 0, v2 = 0, v3 = 0, n1 = 0, n2 = 0, n3 = 0, t1 = 0, t2 = 0;
			uint32_t f_vertex = 0, f_uv = 0, f_normal = 0;

			while (std::getline(file, line))
			{
				std::istringstream iss(line);
				std::getline(iss, token, ' ');

				if (token == "#")
					continue;

				if (token == "v")
				{
					iss >> v1 >> v2 >> v3;
					vertices.push_back(Vec3(v1, v2, v3));
					++vertexCount;
				}
				else if (token == "vn")
				{
					iss >> n1 >> n2 >> n3;
					normals.push_back(Vec3(n1, n2, n3));
					++normalCount;
				}
				else if (token == "vt")
				{
					iss >> t1 >> t2;
					uv.push_back(Vec2(t1, t2));
					++uvCount;
				}
				else if (token == "f")
				{
					++faceCount;

					// n-vertices in a face
					while (!iss.eof())
					{
						iss >> face;
						std::istringstream face_vertex_iss(face);
						std::string face_vertex_attrib;

						while (std::getline(face_vertex_iss, face_vertex_attrib, '/'))
						{
							bool is_empty = face_vertex_attrib.empty();

							if (!is_empty)
								indexes.push_back(std::stoi(face_vertex_attrib) - 1);
						}
					}
				}
			}
		}
	}

	void compileData()
	{
		bool hasUV = uv.size() > 0;
		bool hasNormals = normals.size() > 0;

		int vertexCount = getDrawVertexCount();
		int coordsPerVertex = getCoordsPerVertex();
		int vertexOffset = vertexCount * coordsPerVertex;

		vertexData.resize(vertexCount * coordsPerVertex);

		/* FACE INDEX OFFSETS */
		int f_stride = 3;

		int f_vOffset = 0;
		int f_tOffset = 1;
		int f_nOffset = 2;

		if (!hasUV)
		{
			--f_stride;
			--f_nOffset;
		}

		if (!hasNormals)
		{
			--f_stride;
		}

		int i = 0;	// Buffer Offset
		for (int f = f_vOffset; f < indexes.size(); f += f_stride)
		{
			Vec3 vertex = vertices[indexes[f]];
			vertexData[i] = vertex.x;
			vertexData[i + 1] = vertex.y;
			vertexData[i + 2] = vertex.z;

			i += coordsPerVertex;
		}

		i = 3;
		if (hasNormals)
		{
			for (int f = f_nOffset; f < indexes.size(); f += f_stride)
			{
				std::cout << "   I: " << i << "\n";
				Vec3 normal = normals[indexes[f]];
				vertexData[i] = normal.x;
				vertexData[i + 1] = normal.y;
				vertexData[i + 2] = normal.z;

				i += coordsPerVertex;
			}
		}

		i = 6;
		if (hasUV)
		{
			for (int f = f_tOffset; f < indexes.size(); f += f_stride)
			{
				Vec2 texCoord = uv[indexes[f]];
				vertexData[i] = texCoord.x;
				vertexData[i + 1] = texCoord.y;

				i += coordsPerVertex;
			}
		}
	}

public:
	OBJLoader(std::string filename)
	{
		this->filename = filename;
		this->vertexCount = 0;
		this->normalCount = 0;
		this->uvCount = 0;
		this->faceCount = 0;
		this->drawVertexCount = 0;

		load();
		compileData();
	}

	void show()
	{
		for (float x : vertexData)
			std::cout << x << " ";
	}

	float* getVertexData()
	{
		return vertexData.data();
	}

	uint32_t getCoordsPerVertex()
	{
		int coordsPerVertex = 8;
		if (normals.size() == 0)
			coordsPerVertex -= 3;

		if (uv.size() == 0)
			coordsPerVertex -= 2;

		return coordsPerVertex;
	}

	uint32_t getFaceCount()
	{
		return faceCount;
	}

	uint32_t getDrawVertexCount()
	{
		return faceCount * 3;
	}

	uint32_t getVertexCount()
	{
		return vertexCount;
	}

	uint32_t getNormalCount()
	{
		return normalCount;
	}

	uint32_t getUVCount()
	{
		return uvCount;
	}
};