/**
 * Tucano - A library for rapid prototying with Modern OpenGL and GLSL
 * Copyright (C) 2014
 * LCG - Laboratório de Computação Gráfica (Computer Graphics Lab) - COPPE
 * UFRJ - Federal University of Rio de Janeiro
 *
 * This file is part of Tucano Library.
 *
 * Tucano Library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Tucano Library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Tucano Library.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __DEPTH_MAP__
#define __DEPTH_MAP__

#include <tucano.hpp>
#include <camera.hpp>

using namespace Tucano;

namespace Effects
{

/**
 * @brief Renders a mesh using a Phong shader.
 */
class DepthMap : public Effect
{

private:

    /// Phong Shader
    Shader depthMap_shader;

	/// Default color
	Eigen::Vector4f default_color;

public:
    /**
     * @brief Default constructor.
     */
    DepthMap (void)
    {
		default_color << 0.7, 0.7, 0.7, 1.0;
    }

    /**
     * @brief Default destructor
     */
    virtual ~DepthMap (void) {}

    /**
     * @brief Load and initialize shaders
     */
    virtual void initialize (void)
    {
        // searches in default shader directory (/shaders) for shader files phongShader.(vert,frag,geom,comp)
        loadShader(depthMap_shader, "depthMap") ;
    }

	/**
	* @brief Sets the default color, usually used for meshes without color attribute
	*/
	void setDefaultColor ( Eigen::Vector4f& color )
	{
		default_color = color;
	}

    /** * @brief Render the mesh given a camera and light, using a Phong shader 
     * @param mesh Given mesh
     * @param camera Given camera 
     * @param lightTrackball Given light camera 
     */

    void render (Tucano::Mesh& mesh, const Tucano::Camera& camera, const Tucano::Camera& lightTrackball)
    {

        Eigen::Vector4f viewport = camera.getViewport();
        glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);

        depthMap_shader.bind();

        // sets all uniform variables for the phong shader
        depthMap_shader.setUniform("projectionMatrix", camera.getProjectionMatrix());
        depthMap_shader.setUniform("modelMatrix", mesh.getModelMatrix());
        depthMap_shader.setUniform("viewMatrix", camera.getViewMatrix());
        depthMap_shader.setUniform("lightViewMatrix", lightTrackball.getViewMatrix());
        depthMap_shader.setUniform("has_color", mesh.hasAttribute("in_Color"));
        depthMap_shader.setUniform("default_color", default_color);

        mesh.setAttributeLocation(depthMap_shader);

        glEnable(GL_DEPTH_TEST);
        mesh.render();

        depthMap_shader.unbind();
    }
};
}


#endif
