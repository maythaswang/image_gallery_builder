#ifndef GEOMETRY_BUILDER_H
#define GEOMETRY_BUILDER_H
#pragma once
#include <GLCommon.h>
#include <lin_alg/lin_alg.h>
#include <simple_scene/simple_scene.h>
#include <vector>

/**
 * @brief Class for building meshes
 * 
 */
class GeometryBuilder
{
public:
	/**
	 * @brief Construct a new Geometry Builder object
	 *
	 */
	GeometryBuilder();
	~GeometryBuilder();

	/**
	 * @brief Create plane
	 *
	 * @param width width of the plane
	 * @param depth depth of the plane
	 * @param material_id material id
	 *
	 * @return plane mesh
	 */
	ss::Mesh init_plane(GLfloat width, GLfloat depth, GLuint mat_id);

	/**
	 * @brief Create canvas frame
	 *
	 * @param width width of the frame
	 * @param depth depth of the frame
	 * @param material_id material id
	 * @return canvas frame mesh
	 */
	ss::Mesh init_canvas_frame(GLfloat width, GLfloat depth, GLuint mat_id);

	/**
	 * @brief Create box
	 *
	 * @param width width of the box
	 * @param height height of the box
	 * @param depth depth of the box
	 * @param mat_id material id
	 *
	 * @return plane mesh
	 */
	ss::Mesh init_box(GLfloat width, GLfloat height, GLfloat depth, GLfloat mat_id);

	/**
	 * @brief Create box with flipped normals
	 *
	 * @param width width of the box
	 * @param height height of the box
	 * @param depth depth of the box
	 * @param mat_id material id
	 *
	 * @return plane mesh
	 */
	ss::Mesh init_box_flipped(GLfloat width, GLfloat height, GLfloat depth, GLfloat mat_id);

private:
};
#endif