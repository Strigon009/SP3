#include "ExperienceBar.h"
#include "GL\glew.h"

#include <iostream>
using namespace std;

/**
 @brief Default Constructor
 */
CExperienceBar::CExperienceBar(void)
	:cPlayer3D(NULL)
	, fHeight(0.f)
	, fWidth(0.f)
	, expBar(false)
	, transform(glm::mat4(1.0f))
	, iExp(0)
	, iMaxExp(100)
	, iLevel(1)
{
}

/**
 @brief Destructor
 */
CExperienceBar::~CExperienceBar(void)
{
	// Delete the rendering objects in the graphics card
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	// We set this to NULL, since it was created elsewhere so we don't delete it here
	cShader = NULL;

	cPlayer3D = NULL;
}

/**
 @brief Initialise this class instance
 @return true is successfully initialised this class instance, else false
 */
bool CExperienceBar::Init(glm::vec3 pos, glm::vec4 color)
{
	// Check if the shader is ready
	if (!cShader)
	{
		cout << "CProgressBar::Init(): The shader is not available for this class instance." << endl;
		return false;
	}

	// Call the parent's Init()
	CEntity3D::Init();

	// Initialise the cPlayer3D
	cPlayer3D = CPlayer3D::GetInstance();

	// Set the type
	SetType(CEntity3D::TYPE::OTHERS);

	transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first

	fHeight = 0.0333f * 0.8;
	fWidth = 0.0333f * 6;
	vec3Position = pos;
	vec4Colour = color;
	vec3Scale.x = 0.f;

	// set up vertex data (and buffer(s)) and configure vertex attributes
	float vertices[] = {
		// positions		// texture coords
		-fWidth,  fHeight, 0.0f, vec4Colour.x, vec4Colour.y, vec4Colour.z,
		-fWidth, -fHeight, 0.0f, vec4Colour.x, vec4Colour.y, vec4Colour.z,
		 fWidth, -fHeight, 0.0f, vec4Colour.x, vec4Colour.y, vec4Colour.z,

		 fWidth, -fHeight, 0.0f, vec4Colour.x, vec4Colour.y, vec4Colour.z,
		 fWidth,  fHeight, 0.0f, vec4Colour.x, vec4Colour.y, vec4Colour.z,
		-fWidth,  fHeight, 0.0f, vec4Colour.x, vec4Colour.y, vec4Colour.z,
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// texture coord attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	return true;
}

/**
 @brief Set model
 @param model A glm::mat4 variable containing the model for this class instance
 */
void CExperienceBar::SetModel(glm::mat4 model)
{
	this->model = model;
}

/**
 @brief Set view
 @param view A glm::mat4 variable containing the model for this class instance
 */
void CExperienceBar::SetView(glm::mat4 view)
{
	this->view = glm::mat4(glm::mat3(view)); // remove translation from the view matrix
}

/**
 @brief Set projection
 @param projection A glm::mat4 variable containing the model for this class instance
 */
void CExperienceBar::SetProjection(glm::mat4 projection)
{
	this->projection = projection;
}

/**
 @brief PreRender Set up the OpenGL display environment before rendering
 */
void CExperienceBar::Update(const double dElapsedTime)
{
	vec3Scale.x = iExp / iMaxExp;

}

/**
 @brief PreRender Set up the OpenGL display environment before rendering
 */
void CExperienceBar::PreRender(void)
{
	// bind textures on corresponding texture units
	glActiveTexture(GL_TEXTURE0);

	// Activate blending mode
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

/**
 @brief Render Render this instance
 @param cShader A Shader* variable which contains the Shader to use in this class instance
 */
void CExperienceBar::Render(void)
{
	// If the shader is in this class, then do not render
	if (!cShader)
	{
		cout << "CProgressBar::Render(): The shader is not available for this class instance." << endl;
		return;
	}

	// Activate shader
	cShader->use();

	unsigned int transformLoc;
	// get matrix's uniform location and set matrix
	transformLoc = glGetUniformLocation(cShader->ID, "transform");
	// Reset the transform
	transform = glm::mat4(1.0f);
	// Translate to the position to render. Note that the centrepoint of the progressbar will be at this position
	// So we need to offset to the right by the vec3Scale.x * fWidth
	transform = glm::translate(transform, glm::vec3(vec3Position.x + vec3Scale.x * fWidth, vec3Position.y, vec3Position.z));
	// Scale the size of the progressbar by vec3Scale. 
	// Note that .y and .z should be 1.0f if you are not scaling them at all
	transform = glm::scale(transform, vec3Scale);

	// Update the shaders with the latest transform
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

	// Render the quad
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	// Reset to default
	glBindVertexArray(0);

	// get matrix's uniform location and set matrix
	transformLoc = glGetUniformLocation(cShader->ID, "transform");
	// Reset the transform
	transform = glm::mat4(1.0f);
	// Translate to the position to render. Note that the centrepoint of the progressbar will be at this position
	// So we need to offset to the right by the vec3Scale.x * fWidth
	transform = glm::translate(transform, glm::vec3(vec3Position.x + fWidth, vec3Position.y, vec3Position.z));

	// Update the shaders with the latest transform
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

	// Render the quad
	glBindVertexArray(VAO);
	glDrawArrays(GL_LINE_LOOP, 0, 6);

	// Reset to default
	glBindVertexArray(0);
}

/**
 @brief PostRender Set up the OpenGL display environment after rendering.
 */
void CExperienceBar::PostRender(void)
{
	// Disable blending
	glDisable(GL_BLEND);
}

float CExperienceBar::GetiExp()
{
	return iExp;
}

float CExperienceBar::GetiMaxExp()
{
	return iMaxExp;
}

void CExperienceBar::SetiExp(float iexp)
{
	iExp = iexp;
}

void CExperienceBar::SetiMaxExp(float imaxexp)
{
	iMaxExp = imaxexp;
}