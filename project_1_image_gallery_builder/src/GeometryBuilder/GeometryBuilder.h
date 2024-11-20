#ifndef GEOMETRY_BUILDER_H
#define GEOMETRY_BUILDER_H
#pragma once
#include <GLCommon.h>
#include <lin_alg/lin_alg.h>
#include <simple_scene/simple_scene.h>
#include <vector>

struct RC
{
	GLuint VAO[1];
	GLuint VBO[4];
	GLuint EBO[1];
	GLuint n_vert;
	GLuint n_inds;
};

class GeometryBuilder
{
public:
	/**
	 * @brief Construct a new Geometry Builder object
	 *
	 */
	GeometryBuilder();
	~GeometryBuilder();

	ss::Mesh init_plane(GLfloat width, GLfloat depth, GLuint mat_id);
    ss::Mesh init_canvas_frame(GLfloat width, GLfloat depth, GLuint mat_id);
	ss::Mesh init_canvas_image(GLfloat width, GLfloat depth, GLuint mat_id);

	/**
	 * @brief Create box
	 *
	 * @param render_components RenderComponent struct to store VAO, VBOs, EBO and number of vertices and indices
	 * @param center vec3, center of the box
	 * @param width width of the box
	 * @param height height of the box
	 * @param depth depth of the box
	 */
	ss::Mesh init_box( GLfloat, GLfloat, GLfloat, GLfloat);

	ss::Mesh init_box_flipped(GLfloat width, GLfloat height, GLfloat depth, GLfloat mat_id);

	/**
	 * @brief Initialize buffers using the given information and return it through ptr
	 *
	 * @param render_components RenderComponent struct to store VAO, VBOs, EBO and number of vertices and indices
	 * @param vertices
	 * @param indices
	 * @param texture_coords
	 * @param texture_ids
	 */
	RC init_buf(lin_alg::vec3 *, lin_alg::vec3 *, lin_alg::ivec3 *, GLfloat *, GLfloat *);

private:

};
#endif