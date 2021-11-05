#pragma once
#pragma once
#include<model/Model.h>
#include<material/Material.h>
#include<model/Mesh.h>
#include<shader/Shader.h>
#include<texture/Texture2D.h>
#include<texture/Texture.h>

class Plane :public Model
{

private:
    const int vertexCount = 6;
    const int coordsPerVertex = 8;
    float* vertexData{
        new float[vertexCount * coordsPerVertex] {
            -1.0f,-1.0f,0.0f, 0.0f,0.0f,-1.0f,0.0f,0.0f,
            1.0f,-1.0f,0.0f,  0.0f,0.0f,-1.0f,1.0f,0.0f,
            -1.0f,1.0f,0.0f,  0.0f,0.0f,-1.0f,0.0f,1.0f,
            -1.0f,1.0f,0.0f,  0.0f,0.0f,-1.0f,0.0f,1.0f,
            1.0f,-1.0f,0.0f,  0.0f,0.0f,-1.0f,1.0f,0.0f,
            1.0f,1.0f,0.0f,   0.0f,0.0f,-1.0f,1.0f,1.0f
        }
    };

    Shader* shader;
    Texture* texture;
    Material* material;
    Mesh* mesh;

public:
    Plane() :Model()
    {
        shader = new Shader("res/shaders/phong");
        texture = new Texture2D("res/textures/CRATE_DIFFUSED.png", "res/textures/CRATE_SPECULAR.png", "");
        material = new Material(shader, texture, 32);
        mesh = new Mesh(vertexData, vertexCount, coordsPerVertex);
        mesh->setMaterial(material);
        addMesh(mesh);
    }

    ~Plane()
    {
        delete shader;
        delete texture;
        delete material;
        delete mesh;
    }
};