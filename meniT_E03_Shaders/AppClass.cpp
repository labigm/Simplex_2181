#include "AppClass.h"
//Application Class
AppClass::AppClass(std::string a_windowName) : m_sWindowName(a_windowName) {}
AppClass::AppClass(AppClass const& input) {}
AppClass& AppClass::operator=(AppClass const& input) { return *this; }
AppClass::~AppClass(void){ Release(); }
bool useCompl = false;
void AppClass::Run(void)
{
	//Initialize the system with the fields recollected by the constructor
	Init();
	
	//Set the background color
	glClearColor(0.392f, 0.584f, 0.929f, 1.0f);

	// run the main loop
	while (m_bRunning)
	{
		// handle events
		sf::Event event;
		while (m_pWindow->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				// end the program
				m_bRunning = false;
			}
			else if (event.type == sf::Event::Resized)
			{
				// adjust the viewport when the window is resized
				glViewport(0, 0, event.size.width, event.size.height);
			}
			else if (event.type == sf::Event::KeyPressed)
			{
				ProcessKeyboard(event);
			}
		}

		Display();
	}
}
void AppClass::Init(void)
{
	InitWindow();	//Create Window
	InitOpenGL();	//Initialize Rendering Context
	InitShaders();	//Compile Shaders
	InitVariables();//Init shape
}
void AppClass::InitWindow()
{
	// create the window
	m_pWindow = new sf::Window(sf::VideoMode(800, 600), m_sWindowName, sf::Style::Default, sf::ContextSettings(32));
	m_pWindow->setVerticalSyncEnabled(true);
}
void AppClass::InitOpenGL(void)
{
	// Initialize GLEW
	glewExperimental = GL_TRUE;
	glewInit(); //run glew setup

	glEnable(GL_BLEND);	//Enable pixel blend
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //type of the blend function

	glEnable(GL_DEPTH_TEST);// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);	// The Type Of Depth Testing To Do

	glEnable(GL_CULL_FACE);	//Don't show faces from behind
}
void AppClass::InitShaders(void)
{
	m_uShaderProgramID = LoadShaders("Shaders//BasicColor.vs", "Shaders//BasicColor.fs");
	glUseProgram(m_uShaderProgramID);
}
void AppClass::InitVariables(void)
{
	std::vector<glm::vec3> lVertex;
	//vertex 1
	lVertex.push_back(glm::vec3(-1.0f, -1.0f, 0.0f)); //position
	lVertex.push_back(glm::vec3(1.0f, 0.0f, 0.0f)); //color
	//vertex 2
	lVertex.push_back(glm::vec3(1.0f, -1.0f, 0.0f)); //position
	lVertex.push_back(glm::vec3(0.0f, 1.0f, 0.0f)); //color
	//vertex 3
	lVertex.push_back(glm::vec3(0.0f, 1.0f, 0.0f)); //position
	lVertex.push_back(glm::vec3(0.0f, 0.0f, 1.0f)); //color
	
	glGenVertexArrays(1, &m_uVAO);//Generate vertex array object
	glGenBuffers(1, &m_uVBO);//Generate Vertex Buffered Object

	glBindVertexArray(m_uVAO);//Bind the VAO
	glBindBuffer(GL_ARRAY_BUFFER, m_uVBO);//Bind the VBO

	//Generate space for the VBO (vertex count times size of vec3)
	glBufferData(GL_ARRAY_BUFFER, lVertex.size() * sizeof(glm::vec3), &lVertex[0], GL_STATIC_DRAW);

	//count the attributes
	int attributeCount = 2;
	
	// Position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, attributeCount * sizeof(glm::vec3), (GLvoid*)0);

	// Color attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, attributeCount * sizeof(glm::vec3), (GLvoid*)(1 * sizeof(glm::vec3)));
}
void AppClass::ProcessKeyboard(sf::Event a_event)
{
	if (a_event.key.code == sf::Keyboard::Key::Escape)//Event says I pressed the Escape key
		m_bRunning = false;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) //I am currently pressing the Num1 (not the same as above)
		m_v3Color = glm::vec3(1.0f, 0.0f, 0.0f);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
		m_v3Color = glm::vec3(0.0f, 1.0f, 0.0f);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
		m_v3Color = glm::vec3(0.0f, 0.0f, 1.0f);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num9))
	{
		std::cout << "HELLO" << std::endl;
		useCompl = !useCompl;
		//m_v3Color = glm::vec3(-1.0f, -1.0f, -1.0f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0)) {
	//	useCompl = !useCompl;
		m_v3Color = glm::vec3(-1.0f, -1.0f, -1.0f);
	}
}
void AppClass::Display(void)
{
	// clear the buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//read uniforms and send values
	GLuint SolidColor = glGetUniformLocation(m_uShaderProgramID, "SolidColor");
	GLuint isComp = glGetUniformLocation(m_uShaderProgramID, "isComp");


	glUniform3f(SolidColor, m_v3Color.r, m_v3Color.g, m_v3Color.b);
	glUniform1i(isComp, useCompl);


	//draw content
	glDrawArrays(GL_TRIANGLES, 0, 3);

	// end the current frame (internally swaps the front and back buffers)
	m_pWindow->display();
}
void AppClass::Release()
{
	glDeleteShader(m_uShaderProgramID);
	glDeleteBuffers(1, &m_uVBO);
	glBindVertexArray(0); // Unbind VAO
	glDeleteVertexArrays(1, &m_uVAO);

	if (m_pWindow)
	{
		delete m_pWindow;
		m_pWindow = nullptr;
	}
}