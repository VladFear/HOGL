#include <fstream>
#include <iostream>
#include <string>
#include <memory>

#include <GlobalEngine.h>
#include <graphics/ShaderProgram.h>
#include <graphics/GameScene.h>
#include <Entity.h>
#include <graphics/ValidationDefaultStrategy.h>

int main([[maybe_unused]]int argc, [[maybe_unused]]char** argv)
{
	try
	{
		std::shared_ptr<GE::GlobalEngine> engine =
			std::make_shared<GE::GlobalEngine>(GE::EngineAPI::OpenGL);

		std::shared_ptr<GE::Shader> vshader = GE::Shader::ShaderBuilder()
			.setSource("resources/shaders/vertexShader.glsl")
			.create(GL_VERTEX_SHADER);

		std::shared_ptr<GE::Shader> fshader = GE::Shader::ShaderBuilder()
			.setSource("resources/shaders/fragmentShader.glsl")
			.create(GL_FRAGMENT_SHADER);

		std::shared_ptr<GE::ShaderProgram> triangle = std::make_shared<GE::ShaderProgram>();
		triangle->attachShader(vshader);
		triangle->attachShader(fshader);
		triangle->setValidationStrategy(std::make_shared<GE::ValidationDefaultStrategy>());
		triangle->compile();

		float vertices[] =
		{
			-0.75f, 0.0f, 0.0f, // Left
			-0.25f, 0.0f, 0.0f, // Right
			-0.50f, 0.5f, 0.0f  // Top
		};

		unsigned int indexes[] =
		{
			2, 0, 1
		};

		float vertices1[] =
		{
			 0.25f, 0.0f, 0.0f, // Left
			 0.75f, 0.0f, 0.0f, // Right
			 0.50f, 0.5f, 0.0f  // Top
		};

		std::shared_ptr<GE::Model> model1 = GE::Model::ModelBuilder()
			.addVertexBuffer(vertices, std::size(vertices))
			.addIndexBuffer(indexes, std::size(indexes))
			.create();

		std::shared_ptr<GE::Model> model2 = GE::Model::ModelBuilder()
			.addVertexBuffer(vertices1, std::size(vertices1))
			.addIndexBuffer(indexes, std::size(indexes))
			.create();

		engine->addGameObject(std::make_unique<GE::Entity>(model1, triangle, glm::vec3(-0.5f, 0.25f, -1.5f),
		                                                                     glm::vec3(0.f),
		                                                                     glm::vec3(1.f)));
		engine->addGameObject(std::make_unique<GE::Entity>(model2, triangle, glm::vec3(-0.25f, 0.25f, -1.5f),
		                                                                     glm::vec3(0.f),
		                                                                     glm::vec3(1.f)));

		engine->startGameLoop();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what();
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
