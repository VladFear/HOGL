#include <fstream>
#include <iostream>
#include <string>
#include <graphics/globalengine.h>
#include <graphics/model.h>
#include <graphics/shaderprogram.h>
#include <graphics/vertexshader.h>
#include <graphics/fragmentshader.h>

int main(int argc, char** argv)
{
	GlobalEngine engine;

	try
	{
		engine.initialize();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what();
		return EXIT_FAILURE;
	}

	std::fstream vertex_shader_file("resources/shaders/vertexShader.glsl");
	VertexShader vshader(vertex_shader_file);

	std::fstream fragment_shader_file("resources/shaders/fragmentShader.glsl");
	FragmentShader fshader(fragment_shader_file);

	ShaderProgram triangle1;
	ShaderProgram triangle2;

	try
	{
		vshader.compile();
		fshader.compile();

		triangle1.attachShader(vshader);
		triangle1.attachShader(fshader);
		triangle1.compile();

		triangle2.attachShader(vshader);
		triangle2.attachShader(fshader);
		triangle2.compile();
	}
	catch (const std::exception & e)
	{
		std::cerr << e.what();
	}

	GLFWwindow* window = engine.window();

	float vertices[] =
	{
		-1.0f,  0.0f, 0.0f, // Left
		 0.5f,  0.0f, 0.0f, // Right
		-0.25f, 1.0f, 0.0f  // Top
	};

	unsigned int indexes[] =
	{
		2, 0, 1
	};

	float vertices1[] =
	{
		-0.5f,  0.0f, 0.0f, // Left
		 1.0f,  0.0f, 0.0f, // Right
		 0.25f, 1.0f, 0.0f  // Top
	};

	Model model1(vertices, sizeof(vertices) / sizeof(vertices[0]),
		indexes, sizeof(indexes) / sizeof(indexes[0]));
	Model model2(vertices1, sizeof(vertices1) / sizeof(vertices1[0]),
		indexes, sizeof(indexes) / sizeof(indexes[0]));

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Poll for and process events */
		engine.pollEvents();
		engine.clear();

		/* Render here */
		glUseProgram(triangle1.value());
		engine.render(model1);

		glUseProgram(triangle2.value());
		engine.render(model2);
		/* Swap front and back buffers */
		engine.swapBuffers();
	}

	return EXIT_SUCCESS;
}
