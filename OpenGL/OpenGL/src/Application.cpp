#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "RendererGL.h"
//#include "VertexBufferLayout.h"


int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(2);

    if (glewInit() != GLEW_OK)
    {
        std::cout << "Error!" << std::endl;
    };

    // start GLEW extension handler
  // glewExperimental = GL_TRUE;
  // glewInit();

	std::cout << glGetString(GL_VERSION) << std::endl;
	{
		float positions[] = {
			-0.5f,-0.5f,
			 0.5f,-0.5f,
			 0.5f, 0.5f,
			-0.5f, 0.5f

		};

		unsigned int indicies[] = {
			0,1,2,
			2,3,0

		};

		VertexArray va;
		VertexBuffer vb(positions, 4 * 2 * sizeof(float));
		

		VertexBufferLayout layout;
		layout.Push<float>(2);
		va.AddBuffer(vb, layout);

		IndexBuffer ib(indicies, 6);

		

		Shader shader("res/shaders/Basic.shader");

		shader.Bind();

		shader.SetUniform4f("u_color", 0.8f, 0.3f, 0.8f, 1.0f);


		va.Unbind();
		shader.Unbind();

		vb.UnBind();
		ib.UnBind();

		RendererGL renderer;

		float r = 0.0f;
		float r1 = 0.5f;
		float r2 = 0.2f;
		float increment = 0.09f;
		float increment1 = 0.01f;
		float increment2 = 0.03f;
		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			/* Render here */

			renderer.clear();

			shader.Bind();
			shader.SetUniform4f("u_color", r, r1, r2, 1.0f);

			//va.Bind();
			//ib.Bind();
			
			renderer.Draw(va, ib, shader);

			//GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

			if (r > 1.0f) {
				r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
				r1 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
				r2 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
				increment = -0.09f;

			}

			if (r < 0.0f) {
				increment = 0.09f;
				r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
				r1 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
				r2 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			}


			r += increment;
			r1 += increment;
			r2 += increment;

			//glDrawArrays(GL_TRIANGLES, 0, 6);

			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();


		}

    }

    glfwTerminate();
    return 0;
}