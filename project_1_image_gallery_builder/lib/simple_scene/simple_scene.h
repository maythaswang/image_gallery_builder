#ifndef SIMPLE_SCENE_H
#define SIMPLE_SCENE_H
#pragma once
#include "./SS_GLCommon.h"
#include "./Texture/Texture.h"
#include "./TextureManager/TextureManager.h"
#include "./Shader/Shader.h"
#include "./Camera/Camera.h"
#include "./SceneComponents/Mesh.h"
#include "./SceneComponents/Material.h"
#include "./SceneComponents/Light.h"

#include "./MaterialManager/MaterialManager.h"
#include "./LightManager/LightManager.h"

/**
 * QOL LIBRARY FOR SETTING UP BASIC SCENES
 * Use ss namespace to access types and functions provided
 * Despite the name, this library does not provide any Scene Management system.
 * Only required components for flexibility
 *
 * The components provided are
 * - Camera
 * - LightManager
 * - MaterialManager
 * - SceneComponents
 *      - Light
 *      - Mesh
 *      - Material
 * - Texture
 * - TextureManager
 * - Shader
 */
namespace ss
{

}

#endif