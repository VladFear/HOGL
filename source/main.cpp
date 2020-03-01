#include <fstream>
#include <iostream>
#include <string>
#include <memory>

#include <graphics/GlobalEngine.h>
#include <graphics/Model.h>
#include <graphics/ShaderProgram.h>
#include <graphics/GameScene.h>

int main(int argc, char** argv)
{
	try
	{
		std::shared_ptr<GlobalEngine> engine(new GlobalEngine(EngineAPI::OpenGL_API,
		                                                      "GlobalEngine",
		                                                      720,
		                                                      480));

		std::fstream vertex_shader_file("resources/shaders/vertexShader.glsl");

		std::shared_ptr<Shader> vshader = Shader::ShaderBuilder()
			.setSource(vertex_shader_file)
			.create(GL_VERTEX_SHADER);

		std::fstream fragment_shader_file("resources/shaders/fragmentShader.glsl");

		std::shared_ptr<Shader> fshader = Shader::ShaderBuilder()
			.setSource(fragment_shader_file)
			.create(GL_FRAGMENT_SHADER);

		ShaderProgram triangle1;
		ShaderProgram triangle2;

		//triangle1.attachShader(vshader);
		//triangle1.attachShader(fshader);
		//triangle1.compile();

		//triangle2.attachShader(vshader);
		//triangle2.attachShader(fshader);
		//triangle2.compile();

//		float vertices[] =
//		{
//			-1.0f,  0.0f, 0.0f, // Left
//			 0.5f,  0.0f, 0.0f, // Right
//			-0.25f, 1.0f, 0.0f  // Top
//		};
//
//		unsigned int indexes[] =
//		{
//			2, 0, 1
//		};
//
//		float vertices1[] =
//		{
//			-0.5f,  0.0f, 0.0f, // Left
//			 1.0f,  0.0f, 0.0f, // Right
//			 0.25f, 1.0f, 0.0f  // Top
//		};
//
//		std::shared_ptr<Model> model1 = Model::ModelBuilder()
//			.addVertexBuffer(vertices, sizeof(float))
//			.addIndexBuffer(indexes, sizeof(float))
//			.create();
//
//		std::shared_ptr<Model> model2 = Model::ModelBuilder()
//			.addVertexBuffer(vertices1, sizeof(float))
//			.addIndexBuffer(indexes, sizeof(float))
//			.create();

		GameScene * gameScene = new GameScene();

//		gameScene->addGameObject(model1.get());
//		gameScene->addGameObject(model2.get());

		engine->setGameScene(gameScene);

		engine->gameLoop();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what();
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
