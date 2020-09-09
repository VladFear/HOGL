#include <fstream>
#include <iostream>
#include <string>
#include <memory>

#include <graphics/GlobalEngine.h>
#include <graphics/ShaderProgram.h>
#include <graphics/GameScene.h>
#include <Entity.h>
#include <graphics/ValidationDefaultStrategy.h>

int main([[maybe_unused]]int argc, [[maybe_unused]]char** argv)
{
	try
	{
		std::shared_ptr<GlobalEngine> engine =
			std::make_shared<GlobalEngine>(EngineAPI::OpenGL_API,
			                               "GlobalEngine",
			                               720,
			                               480);

		std::shared_ptr<Shader> vshader = Shader::ShaderBuilder()
			.setSource("resources/shaders/vertexShader.glsl")
			.create(GL_VERTEX_SHADER);

		std::shared_ptr<Shader> fshader = Shader::ShaderBuilder()
			.setSource("resources/shaders/fragmentShader.glsl")
			.create(GL_FRAGMENT_SHADER);

		std::shared_ptr<ShaderProgram> triangle = std::make_shared<ShaderProgram>();
		triangle->attachShader(vshader);
		triangle->attachShader(fshader);
		triangle->setValidationStrategy(std::make_shared<ValidationDefaultStrategy>());
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

		std::shared_ptr<Model> model1 = Model::ModelBuilder()
			.addVertexBuffer(vertices, sizeof(vertices) / sizeof(vertices[0]))
			.addIndexBuffer(indexes, sizeof(indexes) / sizeof(indexes[0]))
			.create();

		std::shared_ptr<Model> model2 = Model::ModelBuilder()
			.addVertexBuffer(vertices1, sizeof(vertices1) / sizeof(vertices1[0]))
			.addIndexBuffer(indexes, sizeof(indexes) / sizeof(indexes[0]))
			.create();

		engine->addGameObject(std::make_unique<Entity>(model1, triangle));
		engine->addGameObject(std::make_unique<Entity>(model2, triangle));

		engine->gameLoop();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what();
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
