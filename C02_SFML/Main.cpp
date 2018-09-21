#include "Main.h"

// Shader sources
const GLchar* vertexShader = R"glsl(
	#version 330
	in vec3 positionBuffer;
	void main()
	{
		gl_Position = vec4( positionBuffer, 1.0 );
	}
)glsl";
const GLchar* fragmentShader = R"glsl(
	#version 330
	out vec4 fragment;
	void main()
	{
		fragment = vec4( 1.0, 1.0, 1.0, 1.0 );
		return;
	}
)glsl";

int main()
{
	// create the window
	sf::Window window(sf::VideoMode(800, 600), "SFML_Toolkit", sf::Style::Default, sf::ContextSettings(32));
	window.setVerticalSyncEnabled(true);

	// Initialize GLEW
	glewExperimental = GL_TRUE;
	glewInit(); //run glew setup

	glEnable(GL_BLEND);	//Enable pixel blend
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //type of the blend function

	glEnable(GL_DEPTH_TEST);// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);	// The Type Of Depth Testing To Do

	glEnable(GL_CULL_FACE);	//Don't show faces from behind

	// load resources, initialize the OpenGL states, ...
	sf::Vector2u size = window.getSize();
	sf::Vector2i pos = window.getPosition();

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

#pragma region Shader Initialization
	// Create and compile the vertex shader
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderID, 1, &vertexShader, NULL);
	glCompileShader(vertexShaderID);

	// Create and compile the fragment shader
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderID, 1, &fragmentShader, NULL);
	glCompileShader(fragmentShaderID);

	// Link the vertex and fragment shader into a shader program
	GLuint shaderProgramID = glCreateProgram();
	glAttachShader(shaderProgramID, vertexShaderID);
	glAttachShader(shaderProgramID, fragmentShaderID);
	//glBindFragDataLocation(shaderProgramID, 0, "fragment");
	glLinkProgram(shaderProgramID);
	//Check the program
	GLint result = GL_FALSE;
	GLint log = GL_FALSE;
	glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &result);
	glGetProgramiv(shaderProgramID, GL_INFO_LOG_LENGTH, &log);
	if (log > 0) {
		std::vector<char> ProgramErrorMessage(log + 1);
		glGetProgramInfoLog(shaderProgramID, log, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}
	glUseProgram(shaderProgramID);
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
#pragma endregion
	//---------------------------------------------------------------------------------------------------------
#pragma region Shape Initialization
	// Create Vertex Array Object
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLfloat positions[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};
	// Create Vertex Buffer Object
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), &positions, GL_STATIC_DRAW);
	// Get the Attribute of position from the shader program
	GLint positionBufferID = glGetAttribLocation(shaderProgramID, "positionBuffer");
	glEnableVertexAttribArray(positionBufferID);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
#pragma endregion

	// run the main loop
	bool running = true;
	while (running)
	{
		// handle events
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				// end the program
				running = false;
			}
			else if (event.type == sf::Event::Resized)
			{
				// adjust the viewport when the window is resized
				glViewport(0, 0, event.size.width, event.size.height);
			}
			else if (event.type == sf::Event::KeyPressed)
			{
				running = false;
			}
		}

		// clear the buffers
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		//Color and draw
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// end the current frame (internally swaps the front and back buffers)
		window.display();
	}

#pragma region Cleanup
	glDeleteProgram(shaderProgramID);
	glDeleteShader(fragmentShaderID);
	glDeleteShader(vertexShaderID);

	glDeleteBuffers(1, &vbo);
	glBindVertexArray(0); // Unbind VAO
	glDeleteVertexArrays(1, &vao);
#pragma endregion
	return 0;
}