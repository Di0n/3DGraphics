#include "Game.hpp"
#include <list>
#include <iostream>
#include <GL\freeglut.h>

#include "Camera.hpp"
#include "GameObject.h"
#include "CubeComponent.h"
#include "PlayerComponent.h"
#include "CameraComponent.hpp"
#include "OBJ_Loader.h"


namespace Game
{
	int windowWidth, windowHeight;
	bool keys[256];

	// Active world camera
	Camera camera;
	std::list<GameObject*> objects;
	GameObject* player;
	objl::Loader loader;
	
	std::vector < objl::Vertex> vertices;
	std::vector <objl::Mesh> meshes;
	std::vector <objl::Material> materials;
	std::vector<unsigned int> indices;

	std::vector < objl::Vertex> verticesSky;
	std::vector <objl::Mesh> meshesSky;
	std::vector <objl::Material> materialsSky;
	std::vector<unsigned int> indicesSky;

	// Sky_CONE.obj
	void loadContent()
	{
		ZeroMemory(keys, sizeof(keys));
		
		camera = Camera(0, 4, 0, 0);
		GameObject* o = new GameObject();
		o->addComponent(new CubeComponent(0.5));

		o->position = Vec3f(0, 4, 0);
		player = new GameObject();
		player->addComponent(new PlayerComponent());
		//player->addComponent(new CameraComponent(Camera(0, -4, 0, 0)));
		//camera = player->getComponent<CameraComponent>()->getCamera();

		player->position = Vec3f(0, 0, 0);
		
		objects.push_back(o);
		objects.push_back(player);

		

		bool loaded = loader.LoadFile("D:\\Libraries\\Documents\\GitHub\\3DGraphics\\BowlingAlley\\Objects\\Venue01.obj");

		if (loaded)
		{
			std::ofstream file("e1Out.txt");

			// Go through each loaded mesh and out its contents
			for (int i = 0; i < loader.LoadedMeshes.size(); i++)
			{
				// Copy one of the loaded meshes to be our current mesh
				objl::Mesh curMesh = loader.LoadedMeshes[i];

				// Print Mesh Name
				file << "Mesh " << i << ": " << curMesh.MeshName << "\n";

				// Print Vertices
				file << "Vertices:\n";

				// Go through each vertex and print its number,
				//  position, normal, and texture coordinate
				for (int j = 0; j < curMesh.Vertices.size(); j++)
				{
					file << "V" << j << ": " <<
						"P(" << curMesh.Vertices[j].Position.X << ", " << curMesh.Vertices[j].Position.Y << ", " << curMesh.Vertices[j].Position.Z << ") " <<
						"N(" << curMesh.Vertices[j].Normal.X << ", " << curMesh.Vertices[j].Normal.Y << ", " << curMesh.Vertices[j].Normal.Z << ") " <<
						"TC(" << curMesh.Vertices[j].TextureCoordinate.X << ", " << curMesh.Vertices[j].TextureCoordinate.Y << ")\n";
				}

				// Print Indices
				file << "Indices:\n";

				// Go through every 3rd index and print the
				//	triangle that these indices represent
				for (int j = 0; j < curMesh.Indices.size(); j += 3)
				{
					file << "T" << j / 3 << ": " << curMesh.Indices[j] << ", " << curMesh.Indices[j + 1] << ", " << curMesh.Indices[j + 2] << "\n";
				}

				// Print Material
				file << "Material: " << curMesh.MeshMaterial.name << "\n";
				file << "Ambient Color: " << curMesh.MeshMaterial.Ka.X << ", " << curMesh.MeshMaterial.Ka.Y << ", " << curMesh.MeshMaterial.Ka.Z << "\n";
				file << "Diffuse Color: " << curMesh.MeshMaterial.Kd.X << ", " << curMesh.MeshMaterial.Kd.Y << ", " << curMesh.MeshMaterial.Kd.Z << "\n";
				file << "Specular Color: " << curMesh.MeshMaterial.Ks.X << ", " << curMesh.MeshMaterial.Ks.Y << ", " << curMesh.MeshMaterial.Ks.Z << "\n";
				file << "Specular Exponent: " << curMesh.MeshMaterial.Ns << "\n";
				file << "Optical Density: " << curMesh.MeshMaterial.Ni << "\n";
				file << "Dissolve: " << curMesh.MeshMaterial.d << "\n";
				file << "Illumination: " << curMesh.MeshMaterial.illum << "\n";
				file << "Ambient Texture Map: " << curMesh.MeshMaterial.map_Ka << "\n";
				file << "Diffuse Texture Map: " << curMesh.MeshMaterial.map_Kd << "\n";
				file << "Specular Texture Map: " << curMesh.MeshMaterial.map_Ks << "\n";
				file << "Alpha Texture Map: " << curMesh.MeshMaterial.map_d << "\n";
				file << "Bump Map: " << curMesh.MeshMaterial.map_bump << "\n";

				// Leave a space to separate from the next mesh
				file << "\n";
			}

			// Close File
			file.close();

			vertices = loader.LoadedVertices;
			meshes = loader.LoadedMeshes;
			indices = loader.LoadedIndices;
			materials = loader.LoadedMaterials;
		}
		else
			std::cout << "Failed to load model\n";

		loader.LoadFile("D:\\Libraries\\Documents\\GitHub\\3DGraphics\\BowlingAlley\\Objects\\Sky_CONE.obj");

		indicesSky = loader.LoadedIndices;
		materialsSky = loader.LoadedMaterials;
		meshesSky = loader.LoadedMeshes;
		verticesSky = loader.LoadedVertices;
	}
	void update(float deltaTime)
	{
		for (const auto& o : objects)
			o->update(deltaTime);
	}
	void draw()
	{
		//Camera* camera = player->getComponent<CameraComponent>()->getCamera();
		glRotatef(camera.rotX, 1, 0, 0);
		glRotatef(camera.rotY, 0, 1, 0);
		glTranslatef(camera.posX, 0, camera.posY);


		glEnable(GL_TEXTURE_2D);
		
		for (const auto& m : meshes)
		{
			glBegin(GL_TRIANGLES);
			for (int i = 0; i < m.Vertices.size(); i++)
			{
				glNormal3f(m.Vertices[i].Normal.X, m.Vertices[i].Normal.Y, m.Vertices[i].Normal.Z);
				glTexCoord2f(m.Vertices[i].TextureCoordinate.X, m.Vertices[i].TextureCoordinate.Y);
				glVertex3f(m.Vertices[i].Position.X, m.Vertices[i].Position.Y, m.Vertices[i].Position.Z);
			}
			glEnd();
		}

		for (const auto& m : meshesSky)
		{
			glBegin(GL_TRIANGLES);
			for (int i = 0; i < m.Vertices.size(); i++)
			{
				glNormal3f(m.Vertices[i].Normal.X, m.Vertices[i].Normal.Y, m.Vertices[i].Normal.Z);
				glTexCoord2f(m.Vertices[i].TextureCoordinate.X, m.Vertices[i].TextureCoordinate.Y);
				glVertex3f(m.Vertices[i].Position.X, m.Vertices[i].Position.Y, m.Vertices[i].Position.Z);
			}
			glEnd();
		}
		
		glDisable(GL_TEXTURE_2D);
		// Floor
		//glColor3f(0.1f, 1.0f, 0.2f);
		//glBegin(GL_QUADS);
		//glVertex3f(-15, -1, -15);
		//glVertex3f(15, -1, -15);
		//glVertex3f(15, -1, 15);
		//glVertex3f(-15, -1, 15);
		//glEnd();

		//glColor3f(0.5f, 0.8f, 0.2f);
		//for (const auto& o : objects)
		//	o->draw();



		//glBegin(GL_QUADS);
		//glVertex3f(-15, -1, -15);
		//glVertex3f(15, -1, -15);
		//glVertex3f(15, -1, 15);
		//glVertex3f(-15, -1, 15);
		//glEnd();
	}

	void onKey(Key key)
	{
		keys[key] = true;
	}

	void onKeyUp(Key key)
	{
		keys[key] = false;

		switch (key)
		{
		case VK_ESCAPE:
			glutLeaveMainLoop();
			break;
		default:
			break;
		}
	}

	void onMouseMove(int x, int y)
	{
		return;
		static bool justMoved = false;

		if (justMoved)
		{
			justMoved = false;
			return;
		}
		int dx = x - windowWidth / 2;
		int dy = y - windowHeight / 2;
		if ((dx != 0 || dy != 0) && abs(dx) < 400 && abs(dy) < 400)
		{
			camera.rotY += dx / 10.0f;
			camera.rotX += dy / 10.0f;
			glutWarpPointer(windowWidth / 2, windowHeight / 2);
			justMoved = true;
		}
	}

	void onResize(int w, int h)
	{
		windowWidth = w;
		windowHeight = h;
	}

	void onClose()
	{
		std::cout << "Cleaning up game\n";
		for (auto& o : objects)
			delete o;
		objects.clear();

		std::cout << "Closing game.\n";
	}
}