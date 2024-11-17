#ifndef GEOMETRY_BUILDER_H
#define GEOMETRY_BUILDER_H
#pragma once
#include <GLCommon.h>
#include <lin_alg/lin_alg.h>
#include <simple_scene/simple_scene.h>
#include <vector>

struct RenderComponents
{
	GLuint VAO[1];
	GLuint VBO[3];
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

	ss::Mesh init_plane(GLfloat width, GLfloat depth, GLuint material_id);

// 	// ACTUALLY RESERVE 4 MATERIALS 0-3 FOR 0: FLOOR 1: WALL 2: CEIL 3:CANVAS BORDER 
// 	// TODO: INIT V-PLANE (FOR WALL)
// 	// TODO: INIT H-PLANE (FOR FLOOR AND CEIL)
// 	// TODO: INIT CANVAS (BORDER ONLY) (FOR PUTTING ON IMAGE)
// 	// TODO: INIT IMAGE (FOR PUTTING IT ON CANVAS)

	/**
	 * @brief Create box
	 *
	 * @param render_components RenderComponent struct to store VAO, VBOs, EBO and number of vertices and indices 
	 * @param center vec3, center of the box
	 * @param width width of the box
	 * @param height height of the box
	 * @param depth depth of the box
	 */
	void init_box(RenderComponents *, std::vector<GLfloat>, GLfloat, GLfloat, GLfloat);

// 	/**
// 	 * @brief Create square pyramid
// 	 *
// 	 * @param render_components RenderComponent struct to store VAO, VBOs, EBO and number of vertices and indices 
// 	 * @param center vec3, center of the base of the pyramid
// 	 * @param width width (depth, height) of the base of the pyramid
// 	 */
// 	void init_square_pyramid(RenderComponents *, std::vector<GLfloat>, GLfloat);

// 	/**
// 	 * @brief Create Sphere
// 	 * @note https://www.songho.ca/opengl/gl_sphere.html#sphere
// 	 * @param render_components RenderComponent struct to store VAO, VBOs, EBO and number of vertices and indices 
// 	 * @param radius radius of sphere
// 	 * @param sector_count longitude
// 	 * @param stack_count latitude
// 	 */
// 	void init_sphere(RenderComponents * , GLfloat, GLuint, GLuint);

private:
	/**
	 * @brief Initialize buffers using the given information and return it through ptr
	 *
	 * @param render_components RenderComponent struct to store VAO, VBOs, EBO and number of vertices and indices 
	 * @param vertices
	 * @param indices
	 * @param texture_coords
	 * @param texture_ids
	 */
	void init_buf(RenderComponents *, GLfloat *, GLuint *, GLfloat *, GLfloat *);

// 	/**
// 	 * @brief Generate indices for sphere
// 	 *
// 	 * @param stack_count
// 	 * @param sector_count
// 	 * @return vector of indices
// 	 */
// 	std::vector<GLuint> generate_sphere_indices(GLuint, GLuint);
};
#endif