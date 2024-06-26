#pragma once
#include <dark_core.h>
//#include <RenderSystem/Data/IndexBuffer.h>
//#include <RenderSystem/Data/VertexBuffer.h>
#include <unordered_map>
#include <vector>
#include <string>
#include <memory>

namespace dark {

	/*
	 * Define an operator for the comparison of Vertex objects
	 * 	This set of functions allows us to take a vertex struct instance and hash it, for use by an unordered map key
	 *	This allows us to create index buffers which only contain unique vertices
	 */
	// from: https://stackoverflow.com/a/57595105
	template <typename T, typename... Rest>
	void hashCombine(std::size_t& seed, const T v, const Rest&... rest) {
		seed ^= std::hash<T>{}(v)+0x9e3779b9 + (seed << 6) + (seed >> 2);
		(hashCombine(seed, rest), ...);
	};


	class Model3D
	{

	public:

		struct Vertex {
			// These 4 items get packed into our vertex buffers
			glm::vec3 position{};		// Position of the vertex
			glm::vec3 color{};			// color at this vertex
			glm::vec3 normal{};			// surface norms
			//glm::vec2 texCoord{};		// 2d texture coordinates

			// This is used with our hashing function to generate keys in our ordered map of vertices
			bool operator==(const Vertex& other) const
			{
				return position == other.position && color == other.color && normal == other.normal; // && texCoord == other.texCoord;
			}

		};

		// Vertex and index information to be sent to the model's vertex and index buffer memory
		// TODO Observe Builder's destructor if it's a class. Make sure it's being deallocated after createModelFromFile returns
		struct Builder {
			std::vector<Vertex> vertices{};
			std::vector<uint32_t> indices{};

			void loadModel(const std::string& filepath);
		};

		//Model3D(EngineDevice& device, const Model3D::Builder& builder);
		Model3D(std::vector<Model3D::Vertex> vertices, std::vector<uint32_t> indices);
		Model3D(const Model3D&) = delete;
		Model3D& operator=(const Model3D&) = delete;
		~Model3D();

		inline unsigned int getNumVertices() { return vertices.size(); }
		inline unsigned int getNumIndices() { return indices.size(); }
		inline void* getVerticesv() { return &vertices.front(); }
		inline unsigned int* getIndicesv() { return &indices.front(); }

		static std::unique_ptr<Model3D> createModelFromFile(const std::string& filepath);

	private:

		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;

	};

}