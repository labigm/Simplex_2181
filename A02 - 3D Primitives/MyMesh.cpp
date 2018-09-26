#include "MyMesh.h"
void MyMesh::Init(void)
{
	m_bBinded = false;
	m_uVertexCount = 0;

	m_VAO = 0;
	m_VBO = 0;

	m_pShaderMngr = ShaderManager::GetInstance();
}
void MyMesh::Release(void)
{
	m_pShaderMngr = nullptr;

	if (m_VBO > 0)
		glDeleteBuffers(1, &m_VBO);

	if (m_VAO > 0)
		glDeleteVertexArrays(1, &m_VAO);

	m_lVertex.clear();
	m_lVertexPos.clear();
	m_lVertexCol.clear();
}
MyMesh::MyMesh()
{
	Init();
}
MyMesh::~MyMesh() { Release(); }
MyMesh::MyMesh(MyMesh& other)
{
	m_bBinded = other.m_bBinded;

	m_pShaderMngr = other.m_pShaderMngr;

	m_uVertexCount = other.m_uVertexCount;

	m_VAO = other.m_VAO;
	m_VBO = other.m_VBO;
}
MyMesh& MyMesh::operator=(MyMesh& other)
{
	if (this != &other)
	{
		Release();
		Init();
		MyMesh temp(other);
		Swap(temp);
	}
	return *this;
}
void MyMesh::Swap(MyMesh& other)
{
	std::swap(m_bBinded, other.m_bBinded);
	std::swap(m_uVertexCount, other.m_uVertexCount);

	std::swap(m_VAO, other.m_VAO);
	std::swap(m_VBO, other.m_VBO);

	std::swap(m_lVertex, other.m_lVertex);
	std::swap(m_lVertexPos, other.m_lVertexPos);
	std::swap(m_lVertexCol, other.m_lVertexCol);

	std::swap(m_pShaderMngr, other.m_pShaderMngr);
}
void MyMesh::CompleteMesh(vector3 a_v3Color)
{
	uint uColorCount = m_lVertexCol.size();
	for (uint i = uColorCount; i < m_uVertexCount; ++i)
	{
		m_lVertexCol.push_back(a_v3Color);
	}
}
void MyMesh::AddVertexPosition(vector3 a_v3Input)
{
	m_lVertexPos.push_back(a_v3Input);
	m_uVertexCount = m_lVertexPos.size();
}
void MyMesh::AddVertexColor(vector3 a_v3Input)
{
	m_lVertexCol.push_back(a_v3Input);
}
void MyMesh::CompileOpenGL3X(void)
{
	if (m_bBinded)
		return;

	if (m_uVertexCount == 0)
		return;

	CompleteMesh();

	for (uint i = 0; i < m_uVertexCount; i++)
	{
		//Position
		m_lVertex.push_back(m_lVertexPos[i]);
		//Color
		m_lVertex.push_back(m_lVertexCol[i]);
	}
	glGenVertexArrays(1, &m_VAO);//Generate vertex array object
	glGenBuffers(1, &m_VBO);//Generate Vertex Buffered Object

	glBindVertexArray(m_VAO);//Bind the VAO
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);//Bind the VBO
	glBufferData(GL_ARRAY_BUFFER, m_uVertexCount * 2 * sizeof(vector3), &m_lVertex[0], GL_STATIC_DRAW);//Generate space for the VBO

	// Position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(vector3), (GLvoid*)0);

	// Color attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(vector3), (GLvoid*)(1 * sizeof(vector3)));

	m_bBinded = true;

	glBindVertexArray(0); // Unbind VAO
}
void MyMesh::Render(matrix4 a_mProjection, matrix4 a_mView, matrix4 a_mModel)
{
	// Use the buffer and shader
	GLuint nShader = m_pShaderMngr->GetShaderID("Basic");
	glUseProgram(nShader); 

	//Bind the VAO of this object
	glBindVertexArray(m_VAO);

	// Get the GPU variables by their name and hook them to CPU variables
	GLuint MVP = glGetUniformLocation(nShader, "MVP");
	GLuint wire = glGetUniformLocation(nShader, "wire");

	//Final Projection of the Camera
	matrix4 m4MVP = a_mProjection * a_mView * a_mModel;
	glUniformMatrix4fv(MVP, 1, GL_FALSE, glm::value_ptr(m4MVP));
	
	//Solid
	glUniform3f(wire, -1.0f, -1.0f, -1.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArrays(GL_TRIANGLES, 0, m_uVertexCount);  

	//Wire
	glUniform3f(wire, 1.0f, 0.0f, 1.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_POLYGON_OFFSET_LINE);
	glPolygonOffset(-1.f, -1.f);
	glDrawArrays(GL_TRIANGLES, 0, m_uVertexCount);
	glDisable(GL_POLYGON_OFFSET_LINE);

	glBindVertexArray(0);// Unbind VAO so it does not get in the way of other objects
}
void MyMesh::AddTri(vector3 a_vBottomLeft, vector3 a_vBottomRight, vector3 a_vTopLeft)
{
	//C
	//| \
	//A--B
	//This will make the triangle A->B->C 
	AddVertexPosition(a_vBottomLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopLeft);
}
void MyMesh::AddQuad(vector3 a_vBottomLeft, vector3 a_vBottomRight, vector3 a_vTopLeft, vector3 a_vTopRight)
{
	//C--D
	//|  |
	//A--B
	//This will make the triangle A->B->C and then the triangle C->B->D
	AddVertexPosition(a_vBottomLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopLeft);

	AddVertexPosition(a_vTopLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopRight);
}

void MyMesh::GenerateCube(float a_fSize, vector3 a_v3Color)
{
	if (a_fSize < 0.01f)
		a_fSize = 0.01f;

	Release();
	Init();

	float fValue = a_fSize * 0.5f;
	//3--2
	//|  |
	//0--1

	vector3 point0(-fValue,-fValue, fValue); //0
	vector3 point1( fValue,-fValue, fValue); //1
	vector3 point2( fValue, fValue, fValue); //2
	vector3 point3(-fValue, fValue, fValue); //3

	vector3 point4(-fValue,-fValue,-fValue); //4
	vector3 point5( fValue,-fValue,-fValue); //5
	vector3 point6( fValue, fValue,-fValue); //6
	vector3 point7(-fValue, fValue,-fValue); //7

	//F
	AddQuad(point0, point1, point3, point2);

	//B
	AddQuad(point5, point4, point6, point7);

	//L
	AddQuad(point4, point0, point7, point3);

	//R
	AddQuad(point1, point5, point2, point6);

	//U
	AddQuad(point3, point2, point7, point6);

	//D
	AddQuad(point4, point5, point0, point1);

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::GenerateCuboid(vector3 a_v3Dimensions, vector3 a_v3Color)
{
	Release();
	Init();

	vector3 v3Value = a_v3Dimensions * 0.5f;
	//3--2
	//|  |
	//0--1
	vector3 point0(-v3Value.x, -v3Value.y, v3Value.z); //0
	vector3 point1(v3Value.x, -v3Value.y, v3Value.z); //1
	vector3 point2(v3Value.x, v3Value.y, v3Value.z); //2
	vector3 point3(-v3Value.x, v3Value.y, v3Value.z); //3

	vector3 point4(-v3Value.x, -v3Value.y, -v3Value.z); //4
	vector3 point5(v3Value.x, -v3Value.y, -v3Value.z); //5
	vector3 point6(v3Value.x, v3Value.y, -v3Value.z); //6
	vector3 point7(-v3Value.x, v3Value.y, -v3Value.z); //7

	//F
	AddQuad(point0, point1, point3, point2);

	//B
	AddQuad(point5, point4, point6, point7);

	//L
	AddQuad(point4, point0, point7, point3);

	//R
	AddQuad(point1, point5, point2, point6);

	//U
	AddQuad(point3, point2, point7, point6);

	//D
	AddQuad(point4, point5, point0, point1);

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}

void MyMesh::GenerateCone(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_fRadius < 0.01f)
		a_fRadius = 0.01f;

	if (a_fHeight < 0.01f)
		a_fHeight = 0.01f;

	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();


	vector3* vertexPos = new vector3[a_nSubdivisions + 2]; // Create an array of v3s to hold our positions.
	// Draw the circle which makes the base of the cone.

	vertexPos[0] = vector3(0.0f, 0.0f, -a_fHeight / 2.0f); // Create the origin.

	float theta = 0; // The angle which we use to calculate positions of points, in radians.
					 // Calculate positions of all other points.
	for (int i = 0; i < a_nSubdivisions; i++) {
		vertexPos[i + 1] = vector3(a_fRadius * cos(theta), a_fRadius * sin(theta), -a_fHeight / 2.0f);
		theta += (2 * PI / a_nSubdivisions);
	}
	// Add the only other point, which represents the tip of the cone.
	
	vertexPos[a_nSubdivisions + 1] = vector3(0.0f, 0.0f, a_fHeight / 2.0f);
	
	// Now, draw all triangles via AddTri to generate the circle first, then the cone.
	int j = 2; // Make this 2, since i starts at 1, and we may guarantee that the first triangle is 0->2->1 (where the numbers are the indices of vertexPos)
	// I changed the drawing order from E04 because the circle must be shown from the other side this time.
	for (int i = 1; i <= a_nSubdivisions; i++) {
		if (i > a_nSubdivisions) {
			i = 0;
		}
		if (j > a_nSubdivisions) {
			j = 0;
		}
		AddTri(vertexPos[0], vertexPos[j], vertexPos[i]); // Always draw starting from origin.
		j++;
	}
	
	AddTri(vertexPos[0], vertexPos[1], vertexPos[a_nSubdivisions]); // Draw in the final triangle, completing the shape.
	// Draw all triangles from the outside of the circle to the tip of the cone.
	j = 2;
	for (int i = 1; i <= a_nSubdivisions; i++) {
		if (j > a_nSubdivisions) {
			j = 1;
		}
		AddTri(vertexPos[i], vertexPos[j], vertexPos[a_nSubdivisions + 1]);
		j++;
	}
	
	delete[] vertexPos;
	vertexPos = nullptr;
	

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::GenerateCylinder(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_fRadius < 0.01f)
		a_fRadius = 0.01f;

	if (a_fHeight < 0.01f)
		a_fHeight = 0.01f;

	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	vector3* vertexPos = new vector3[(a_nSubdivisions * 2) + 1]; // Create an array of v3s to hold our positions.
	// Draw the first circle facing "down" (CW) with a z-component of zero.
	// Draw the second circle facing "up" (CCW) with a z-component of the height.
	vertexPos[0] = vector3(0, 0, -a_fHeight / 2.0f); // Create the origin of the first circle.
	vertexPos[a_nSubdivisions + 1] = vector3(0, 0, a_fHeight / 2.0f); // Create the origin of the second circle.
	float theta = 0; // The angle which we use to calculate positions of points, in radians.
	 // Calculate positions of the circle points.
	for (int i = 0; i < a_nSubdivisions; i++) {
		vertexPos[i + 1] = vector3(a_fRadius * cos(theta), a_fRadius * sin(theta), -a_fHeight / 2.0f);
		vertexPos[a_nSubdivisions + (i + 2)] = vector3(a_fRadius * cos(theta), a_fRadius * sin(theta), a_fHeight / 2.0f);
		theta += (2 * PI / a_nSubdivisions);
	}
	
	// Add triangles to complete the first, bottom circle. We will draw it clockwise to face out from the cylinder.
	int i = 1; 
	int j = a_nSubdivisions;
	for (int x = 0; x < a_nSubdivisions; x++) {
		if (i <= 0) {
			i = a_nSubdivisions;
		}
		AddTri(vertexPos[0], vertexPos[i], vertexPos[j]);
		i--;
		j--;
	}

	// Add triangles to complete the second, top circle. We will draw it counter-clockwise to face out from the cylinder.
	i = a_nSubdivisions + 2;
	j = a_nSubdivisions + 3;
	for (int x = 0; x < a_nSubdivisions; x++) {
		if (j > ((a_nSubdivisions * 2) + 1)) {
			j = a_nSubdivisions + 2;
		}
		AddTri(vertexPos[a_nSubdivisions + 1], vertexPos[i], vertexPos[j]);
		i++;
		j++;
	}

	// Connect the two circles with quads, completing the cylinder.
	i = 1;
	j = 2;
	int k = a_nSubdivisions + 2;
	int m = a_nSubdivisions + 3;
	for (int x = 0; x < a_nSubdivisions; x++) {
		if (i > a_nSubdivisions) {
			i = 1;
		}
		if (j > a_nSubdivisions) {
			j = 1;
		}
		if (k > (a_nSubdivisions * 2) + 1) {
			k = a_nSubdivisions + 2;
		}
		if (m > (a_nSubdivisions * 2) + 1) {
			m = a_nSubdivisions + 2;
		}
		AddQuad(vertexPos[i], vertexPos[j], vertexPos[k], vertexPos[m]);
		i++;
		j++;
		k++;
		m++;
	}

	delete[] vertexPos;
	vertexPos = nullptr;

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::GenerateTube(float a_fOuterRadius, float a_fInnerRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_fOuterRadius < 0.01f)
		a_fOuterRadius = 0.01f;

	if (a_fInnerRadius < 0.005f)
		a_fInnerRadius = 0.005f;

	if (a_fInnerRadius > a_fOuterRadius)
		std::swap(a_fInnerRadius, a_fOuterRadius);

	if (a_fHeight < 0.01f)
		a_fHeight = 0.01f;

	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();
	
	vector3* vertexPos = new vector3[(a_nSubdivisions * 4) + 1]; // Create an array of v3s to hold our positions.
	// We're going to first make two "flat donuts" as two faces of the tube.
	float theta = 0; // The angle which we use to calculate positions of points, in radians.
	// Calculate positions of the points.
	int n = 0; // Used for indexing purposes.
	for (int i = 0; i < a_nSubdivisions; i++) {
		vertexPos[n] = vector3(a_fOuterRadius * cos(theta), a_fOuterRadius * sin(theta), -a_fHeight / 2.0f); // First, calculate the outer point.
		vertexPos[n + 1] = vector3(a_fInnerRadius * cos(theta), a_fInnerRadius * sin(theta), -a_fHeight / 2.0f);
		vertexPos[(a_nSubdivisions * 2) + n] = vector3(a_fInnerRadius * cos(theta), a_fInnerRadius * sin(theta), a_fHeight / 2.0f); // Inner point of the top shape.
		vertexPos[(a_nSubdivisions * 2) + n + 1] = vector3(a_fOuterRadius * cos(theta), a_fOuterRadius * sin(theta), a_fHeight / 2.0f);
		theta += (2 * PI / a_nSubdivisions);
		n += 2;
	}
	
	// Draw the quads to make up the "flat donuts" of the tube. 
	// First, draw the shape with a z-component of zero. We'll draw this facing outwards by going clockwise.
	int i = 0;
	int j = 2;
	for (int x = 0; x < a_nSubdivisions; x++) {
		if (i >= a_nSubdivisions * 2) {
			i = 0;
		}
		if (j >= a_nSubdivisions * 2) {
			j = 0;
		}
		AddQuad(vertexPos[i], vertexPos[i + 1], vertexPos[j], vertexPos[j + 1]);
		i += 2;
		j += 2;
	}

	// Then, draw the one with a nonzero z-component. We'll need to tweak the vertex drawing order in order to draw them counter-clockwise.
	i = a_nSubdivisions * 2;
	j = (a_nSubdivisions * 2) + 2;
	for (int x = 0; x < a_nSubdivisions; x++) {
		if (i >= a_nSubdivisions * 4) {
			i = (a_nSubdivisions * 2);
		}
		if (j >= a_nSubdivisions * 4) {
			j = (a_nSubdivisions * 2);
		}
		AddQuad(vertexPos[i], vertexPos[i + 1], vertexPos[j], vertexPos[j + 1]);
		i += 2;
		j += 2;
	}
	
	// Fill in the quads to make up the inner and outer lengths of the tube using the existing coordinates.
	// First, the outer length.
	
	i = 0;
	j = 2;
	int k = (a_nSubdivisions * 2) + 1;
	int m = (a_nSubdivisions * 2) + 3;
	for (int x = 0; x < a_nSubdivisions; x++) {
		if (i >= a_nSubdivisions * 2) {
			i = 0;
		}
		if (j >= a_nSubdivisions * 2) {
			j = 0;
		}
		if (k >= a_nSubdivisions * 4) {
			k = (a_nSubdivisions * 2) + 1;
		}
		if (m >= a_nSubdivisions * 4) {
			m = (a_nSubdivisions * 2) + 1;
		}
		AddQuad(vertexPos[i], vertexPos[j], vertexPos[k], vertexPos[m]);
		i += 2;
		j += 2;
		k += 2;
		m += 2;
	}
	// Then, the inner length.
	i = 3;
	j = 1;
	k = (a_nSubdivisions * 2) + 2;
	m = (a_nSubdivisions * 2);
	for (int x = 0; x < a_nSubdivisions; x++) {
		if (i >= a_nSubdivisions * 2) {
			i = 1;
		}
		if (j >= a_nSubdivisions * 2) {
			j = 1;
		}
		if (k >= a_nSubdivisions * 4) {
			k = a_nSubdivisions * 2;
		}
		if (m >= a_nSubdivisions * 4) {
			m = a_nSubdivisions * 2;
		}
		AddQuad(vertexPos[i], vertexPos[j], vertexPos[k], vertexPos[m]);
		i += 2;
		j += 2;
		k += 2;
		m += 2;
	}
	
	delete[] vertexPos;
	vertexPos = nullptr;
	
	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::GenerateTorus(float a_fOuterRadius, float a_fInnerRadius, int a_nSubdivisionsA, int a_nSubdivisionsB, vector3 a_v3Color)
{
	if (a_fOuterRadius < 0.01f)
		a_fOuterRadius = 0.01f;

	if (a_fInnerRadius < 0.005f)
		a_fInnerRadius = 0.005f;

	if (a_fInnerRadius > a_fOuterRadius)
		std::swap(a_fInnerRadius, a_fOuterRadius);

	if (a_nSubdivisionsA < 3)
		a_nSubdivisionsA = 3;
	if (a_nSubdivisionsA > 360)
		a_nSubdivisionsA = 360;

	if (a_nSubdivisionsB < 3)
		a_nSubdivisionsB = 3;
	if (a_nSubdivisionsB > 360)
		a_nSubdivisionsB = 360;

	Release();
	Init();

	GenerateCube(a_fInnerRadius * 2.0f, a_v3Color);
	// -------------------------------

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::GenerateSphere(float a_fRadius, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_fRadius < 0.01f)
		a_fRadius = 0.01f;

	//Sets minimum and maximum of subdivisions
	if (a_nSubdivisions < 1)
	{
		GenerateCube(a_fRadius * 2.0f, a_v3Color);
		return;
	}
	if (a_nSubdivisions > 6)
		a_nSubdivisions = 6;

	Release();
	Init();

	vector3* vertexPos = new vector3[(a_nSubdivisions * ((2 * a_nSubdivisions) - 1)) + 2]; // Create an array of v3s to hold our positions.
	vertexPos[0] = vector3(0, 0, -a_fRadius); // Define a point at the "bottom"
	float tempRad = (a_fRadius / a_nSubdivisions); // Define a temporary radius to use as we draw the concentric circles.
	int n = 1; // Keep the index in vertexPos.

	// Draws up to the middle-most ring of circles, inclusive.
	for (int i = 1; i <= a_nSubdivisions; i++) {
		float theta = 0; // The angle which we use to calculate positions of points, in radians.
		// Calculate positions of each circle's points.
		for (int j = 0; j < a_nSubdivisions; j++) {
			vertexPos[n] = vector3(tempRad * cos(theta), tempRad * sin(theta), (-a_fRadius + tempRad));
			n++;
			theta += (2 * PI / a_nSubdivisions);
		}
		tempRad += (a_fRadius / a_nSubdivisions);
	}

	
	// Draws the ring of circles after the middle-most one.
	for (int i = 1; i < a_nSubdivisions; i++) {
		float theta = 0; // The angle which we use to calculate positions of points, in radians.
		// Calculate positions of each circle's points.
		tempRad -= ((a_fRadius) / a_nSubdivisions);
		for (int j = 0; j < a_nSubdivisions; j++) {
			vertexPos[n] = vector3(tempRad * cos(theta), tempRad * sin(theta), (a_fRadius - tempRad));
			n++;
			theta += (2 * PI / a_nSubdivisions);
		}
	}
	// Add the final point, which is the "top" vertex of the sphere.
	vertexPos[n] = vector3(0, 0, a_fRadius);
	
	// Connect all of these points via quads.
	// Draw triangles to connect the bottommost circle to the bottommost point.
	int i = 2;
	int j = 1;
	for (int n = 0; n < a_nSubdivisions; n++) {
		if (i > a_nSubdivisions) {
			i = 1;
		}
		if (j > a_nSubdivisions) {
			j = 1;
		}
		AddTri(vertexPos[0], vertexPos[i], vertexPos[j]);
		i++;
		j++;
	}

	int k = 0;
	int m = 0;
	// Draw quads to connect points on the circles to each other.
	for (int p = 0; p < (a_nSubdivisions * 2) - 2; p++) {
		i = 1 + (p * a_nSubdivisions);
		j = 2 + (p * a_nSubdivisions);
		k = 1 + ((p + 1) * a_nSubdivisions);
		m = 2 + ((p + 1) * a_nSubdivisions);
		for (int n = 0; n < a_nSubdivisions; n++) {
			if (i > 1 + (a_nSubdivisions * (p + 1))) {
				i = 1 + (p * a_nSubdivisions);
			}
			if (j > 1 + (a_nSubdivisions * (p + 1))) {
				j = 2 + (p * a_nSubdivisions);
			}
			if (k > 1 + (a_nSubdivisions * (2 + p))) {
				k = 1 + ((p + 1) * a_nSubdivisions);
			}
			if (m > 1 + (a_nSubdivisions * (2 + p))) {
				m = 2 + ((p + 1) * a_nSubdivisions);
			}
			AddQuad(vertexPos[i], vertexPos[j], vertexPos[k], vertexPos[m]);
			i++;
			j++;
			k++;
			m++;
		}
	}
	// Finally, close up the shape with the point at the "top". Use triangles for this.
	int lastIndex = (a_nSubdivisions * ((2 * a_nSubdivisions) - 1)) + 1; // The last index of the vertexPos array.
	int a = lastIndex - a_nSubdivisions;
	int b = (lastIndex - a_nSubdivisions) + 1;
	for (int q = 0; q < a_nSubdivisions; q++) {
		if (a >= lastIndex) {
			a = lastIndex - a_nSubdivisions;
		}
		if (b >= lastIndex) {
			b = lastIndex - a_nSubdivisions;
		}
		AddTri(vertexPos[lastIndex], vertexPos[a], vertexPos[b]);
		a++;
		b++;
	}

	delete[] vertexPos;
	vertexPos = nullptr;
	// -------------------------------

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}