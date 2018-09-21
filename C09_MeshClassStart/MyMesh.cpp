#include "MyMesh.h"
MyMesh::MyMesh(float size)
{
	glGenVertexArrays(1, &m_uVAO);//Generate vertex array object
	glGenBuffers(1, &m_uVBO);//Generate Vertex Buffered Object

	glBindVertexArray(m_uVAO);//Bind the VAO
	glBindBuffer(GL_ARRAY_BUFFER, m_uVBO);//Bind the VBO
	InitShader();
	InitTriangle(size);
}
void MyMesh::InitShader(void)
{
	m_uShaderProgramID = LoadShaders("Shaders//BasicColor.vs", "Shaders//BasicColor.fs");
	glUseProgram(m_uShaderProgramID);
}
void MyMesh::InitTriangle(float size)
{
	
	//vertex 1
	m_lVertex.push_back(glm::vec3(-size, -size, 0.0f)); //position
	m_lVertex.push_back(glm::vec3(1.0f, 0.0f, 0.0f)); //color

	 //vertex 2
	m_lVertex.push_back(glm::vec3(size, -size, 0.0f)); //position
	m_lVertex.push_back(glm::vec3(0.0f, 1.0f, 0.0f)); //color

	 //vertex 3
	m_lVertex.push_back(glm::vec3(-size, size, 0.0f)); //position
	m_lVertex.push_back(glm::vec3(0.0f, 0.0f, 1.0f)); //color

													//vertex 4
	m_lVertex.push_back(glm::vec3(-size, size, 0.0f)); //position
	m_lVertex.push_back(glm::vec3(1.0f, 0.0f, 0.0f)); //color

													//vertex 5
	m_lVertex.push_back(glm::vec3(-size, -size, 0.0f)); //position
	m_lVertex.push_back(glm::vec3(0.0f, 1.0f, 0.0f)); //color

													//vertex 6
	m_lVertex.push_back(glm::vec3(size, size, 0.0f)); //position
	m_lVertex.push_back(glm::vec3(0.0f, 0.0f, 1.0f)); //color
	
													 //Generate space for the VBO (vertex count times size of vec3)
	glBufferData(GL_ARRAY_BUFFER, m_lVertex.size() * sizeof(glm::vec3), &m_lVertex[0], GL_STATIC_DRAW);

	//count the attributes
	int attributeCount = 2;

	// Position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, attributeCount * sizeof(glm::vec3), (GLvoid*)0);

	// Color attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, attributeCount * sizeof(glm::vec3), (GLvoid*)(1 * sizeof(glm::vec3)));
}
void MyMesh::Draw(void)
{
	//draw content
	glDrawArrays(GL_TRIANGLES, 0, m_lVertex.size());
}
MyMesh::~MyMesh(void)
{
	glDeleteShader(m_uShaderProgramID);
	glDeleteBuffers(1, &m_uVBO);
	glBindVertexArray(0); // Unbind VAO
	glDeleteVertexArrays(1, &m_uVAO);
}
