#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <fstream>
#include <sstream>
#include <array>
#include "vendor/glm/source/glm.hpp"
#include "vendor/glm/source/gtc/matrix_transform.hpp"
#include "vendor/glm/source/gtc/type_ptr.hpp"
#include "ebo.h"
#include "vbo.h"
#include "vao.h"
#include "shaderprogram.h"
#include "camview.h"
#include "batch_renderer.h"
#include "ubo.h"
#include "fbo.h"
#include "assimp_utils.h"

#define SWIDTH 1000
#define SHEIGHT 700
#define SHWIDTH SWIDTH*5
#define SHHEIGHT SHEIGHT*5
#define SCREENRATIO SWIDTH/SHEIGHT

#define USE_GAMMA_CORRECTION
#ifdef USE_GAMMA_CORRECTION
#define ENABLE_GAMMA_CORRECTION glEnable(GL_FRAMEBUFFER_SRGB)
#define TEX_INTERNAL GL_SRGB
#define TEX_INTERNAL_ALPHA GL_SRGB_ALPHA
#else
#define ENABLE_GAMMA_CORRECTION
#define TEX_INTERNAL GL_RGB
#define TEX_INTERNAL_ALPHA GL_RGBA
#endif



camera_view view(glm::vec3(0, 0, 3));

void input(GLFWwindow* window,double deltaTime);

float vertices[] =
{
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,  0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,0.0f,  0.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,-1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,-1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,-1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,-1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -1.0f,  0.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,1.0f,  0.0f,  0.0f,


		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,0.0f,  1.0f,  0.0f
};
float rectvert[] =
{
		 1,  1, 0, 1.0f, 1.0f, 
		 1, -1, 0, 1.0f, 0.0f, 
		-1, -1, 0, 0.0f, 0.0f, 
		-1,  1, 0, 0.0f, 1.0f  
};

uint rectindices[] =
{
	0, 1, 3, 
	1, 2, 3 
};



double lastx = 0;
double lasty = 0;


GLFWwindow* window;

void glinit();


int main()
{

	glinit();
	vao m_vao(vertices,sizeof(vertices),8*sizeof(float),  std::array<data,3>{data{ GL_FLOAT,3 }, data{ GL_FLOAT,2 }, data{ GL_FLOAT,3 }}._Elems,3);
	vao rect_vao(rectvert, sizeof(rectvert),rectindices,sizeof(rectindices),5 * sizeof(float), std::array<data, 2>{data{ GL_FLOAT,3 }, data{ GL_FLOAT,2 }}._Elems,2);
	program_t program = program_from_file("vertex.glsl","fragment.glsl");
	program_t rectprog = program_from_file("rectvert.glsl","rectfrag.glsl");
	program_t simpleprog = program_from_file("simplev.glsl","simplef.glsl");
	program_t skybox_prog = program_from_file("skybox.glsl", "skyboxfrag.glsl");
	program_t outline_prog = program_from_file("outlinevert.glsl","outlinefrag.glsl");
	program_t model_prog = program_from_file("model_vert.glsl","model_frag.glsl");
	uint texture = load_texture("tex.png");

	//view and projection matrices
	ubo m_ubo(0,sizeof(glm::mat4));

	const char* tex_faces[] = {"right.jpg","left.jpg","top.jpg","bottom.jpg","front.jpg","back.jpg"};
	uint cubemap = load_cubemap(tex_faces);

	const  glm::vec3 lightpos(0, 0.5, 1);

	const glm::mat4 light_proj_mat = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 7.5f);
	const glm::mat4 light_view_mat = glm::lookAt(lightpos,glm::vec3(0,0,0),glm::vec3(0,1,0));
	const glm::mat4 light_space_mat = light_proj_mat * light_view_mat;

	//Assimp mesh loading
	scene gun_model = load_scene("BANH VONG MIN.obj");

	fbo m_fbo;
	uint rbo = m_fbo.renderbuffer_attachment(GL_DEPTH_STENCIL_ATTACHMENT,GL_DEPTH24_STENCIL8,SWIDTH,SHEIGHT);
	uint fbtex = m_fbo.texture_attachment(GL_COLOR_ATTACHMENT0, GL_UNSIGNED_BYTE,GL_RGBA,SWIDTH,SHEIGHT);
	fbo light_fbo;
	uint depth_map = light_fbo.texture_attachment(GL_DEPTH_ATTACHMENT,GL_FLOAT,GL_DEPTH_COMPONENT, SHWIDTH, SHHEIGHT);
	float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	program.bind();
	glm::mat4 models[2];

	models[0] = glm::translate(glm::mat4(1),glm::vec3(0,0,0));
	models[1] = glm::translate(glm::mat4(1), glm::vec3(0, 0, -1.5));

	constexpr double scale = 1.04;
	glm::mat4 outline_models[2];
	outline_models[0] = glm::scale(models[0],glm::vec3(scale));
	outline_models[1] = glm::scale(models[1], glm::vec3(scale));

	glm::mat4 projection = glm::perspective(glm::radians(50.0f),(float)SCREENRATIO,0.1f,600.0f);
	program.set_uniform_int(program.get_uniform_location("image"),0);
	auto model_loc = program.get_uniform_location("models");
	auto lpos_loc = program.get_uniform_location("lightpos");

	//last frame - used to calculate delta time
	double last_frame = 0;

	glfwPollEvents();
	glfwGetCursorPos(window,&lastx,&lasty);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D,depth_map);
	glActiveTexture(GL_TEXTURE0);

	glEnable(GL_DEPTH_TEST);
	glUniformMatrix4fv(model_loc,2,false,(float*)models);
	program.set_uniform_vec3(lpos_loc, lightpos);
	program.set_uniform_mat4(program.get_uniform_location("light_space_matrix"),light_space_mat);
	program.set_uniform_int(program.get_uniform_location("shadowMap"), 1);

	simpleprog.bind();
	auto model_loc2 = simpleprog.get_uniform_location("models");
	glUniformMatrix4fv(model_loc2, 2, false, (float*)models);
	simpleprog.set_uniform_mat4(simpleprog.get_uniform_location("lspace_mat"),light_space_mat);

	rectprog.bind();
	rectprog.set_uniform_int(rectprog.get_uniform_location("screenimage"), 0);


	skybox_prog.bind();
	skybox_prog.set_uniform_mat4(skybox_prog.get_uniform_location("model"), glm::scale(glm::mat4(1),glm::vec3(0.01f)));
	auto skyb_proj_loc = skybox_prog.get_uniform_location("proj");
	auto skyb_view_loc = skybox_prog.get_uniform_location("view");
	skybox_prog.set_uniform_int(skybox_prog.get_uniform_location("skybox"),0);

	outline_prog.bind();
	glUniformMatrix4fv(outline_prog.get_uniform_location("models"), 2, false, (float*)outline_models);
	model_prog.bind();
	model_prog.set_uniform_mat4(model_prog.get_uniform_location("model"), glm::scale(glm::mat4(1), glm::vec3(1.0f)));
	model_prog.set_uniform_int(model_prog.get_uniform_location("tex"), 0);

	while (!glfwWindowShouldClose(window))
	{

		double deltaTime = glfwGetTime()-last_frame;
		last_frame = glfwGetTime();
		input(window,deltaTime);


		//drawing to light map


		light_fbo.bind();
		m_vao.bind();
		simpleprog.bind();

		glEnable(GL_DEPTH_TEST);
		glViewport(0,0,SHWIDTH, SHHEIGHT);

		auto view_m = view.get_view_mat();

		glClear(GL_DEPTH_BUFFER_BIT);
		const auto vpmat = projection * view_m;
		m_ubo.data(0, sizeof(glm::mat4), &vpmat);
		view.update();
		glDrawArraysInstanced(GL_TRIANGLES,0,12*8,2);

		//drawing to fbo
		glUniformMatrix4fv(model_loc, 2, false, (float*)models);
		glViewport(0, 0, SWIDTH, SHEIGHT);
		m_fbo.bind();
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		glStencilMask(0x00);
		model_prog.bind();
		gun_model.draw_scene();
		m_vao.bind();
		program.bind();
		glEnable(GL_STENCIL_TEST);
		glStencilFunc(GL_ALWAYS, 1, 0xFF);
		glStencilMask(0xFF);
		glBindTexture(GL_TEXTURE_2D, texture);
		glDrawArraysInstanced(GL_TRIANGLES, 0,12*8, 2);


		//drawing the outline

		/*glDepthFunc(GL_ALWAYS);
		glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
		glStencilMask(0x00);
		outline_prog.bind();
		glDrawArraysInstanced(GL_TRIANGLES, 0, 12 * 8, 2);*/
		//glStencilFunc(GL_ALWAYS, 1, 0xFF);
		glDepthFunc(GL_LEQUAL);
		glStencilMask(0x00);

		//drawing the skybox
		skybox_prog.bind();
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap);
		skybox_prog.set_uniform_mat4(skyb_proj_loc, projection);
		skybox_prog.set_uniform_mat4(skyb_view_loc, glm::mat4(glm::mat3(view_m)));
		glDrawArrays(GL_TRIANGLES, 0, 9 * 12);
		glDepthFunc(GL_LESS);

		glStencilMask(0xFF);
		
		//drawing from fbo, to screen
		m_fbo.unbind();
		glDisable(GL_STENCIL_TEST);
		glDisable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT);
		glBindTexture(GL_TEXTURE_2D, fbtex);
		rectprog.bind();
		rect_vao.bind();
		glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
		

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();
}


void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void glinit()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	window = glfwCreateWindow(SWIDTH, SHEIGHT, "FPS Test", nullptr, nullptr);
	glfwSetCursorPosCallback(window,mouse_callback);
	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	gladLoadGL();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
	glStencilOp(GL_KEEP,GL_KEEP,GL_REPLACE);
	ENABLE_GAMMA_CORRECTION;
}

#define W GLFW_KEY_W
#define S GLFW_KEY_S
#define A GLFW_KEY_A
#define D GLFW_KEY_D
#define KEYPRESSED(X) glfwGetKey(window,X) == GLFW_PRESS

void input(GLFWwindow* window,double deltaTime)
{
	if (KEYPRESSED(GLFW_KEY_0))
		glfwSetWindowShouldClose(window,true);
	if (KEYPRESSED(W))
		view.keyboard_handling(0,deltaTime);
	if(KEYPRESSED(S))
		view.keyboard_handling(1, deltaTime);
	if (KEYPRESSED(A))
		view.keyboard_handling(2, deltaTime);
	if (KEYPRESSED(D))
		view.keyboard_handling(3, deltaTime);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	float xoffset = xpos - lastx;
	float yoffset = lasty - ypos;
	view.mouse_handling(xoffset,yoffset);
	lastx = xpos;
	lasty = ypos;
}