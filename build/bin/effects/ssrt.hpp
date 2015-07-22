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

#ifndef __SSRT__
#define __SSRT__

#include "tucano.hpp"
#include "utils/trackball.hpp"
#include <math.h>
using namespace Tucano;

namespace Effects
{

/**
 * @brief Renders a mesh using a Phong shader.
 */
class SSRT : public Effect
{


private:

    /// DEPTH MAP
    Shader depthMap;

    /// SCREN SPACE RAYTRACE
    Shader ssrt_shader;

    Shader final;

    ///Frame buffer object
    Framebuffer* fbo;

    Mesh quad;

	/// Default color
    Eigen::Vector4f in_Position;
    Eigen::Vector3f in_Normal;
    Eigen::Vector4f in_Color;
    Eigen::Vector2f in_TexCoords;
    Eigen::Vector4f default_color;

    int depthTextureID;
    int normalTextureID;
    int colorTextureID;

public:

    /**
     * @brief Default constructor.
     */
    SSRT (void)
    {
		default_color << 0.7, 0.7, 0.7, 1.0;

        depthTextureID  = 0;
        normalTextureID = 1;
        colorTextureID  = 2;

        fbo = 0;
    }

    /**
     * @brief Default destructor
     */
    virtual ~SSRT (void)
    {
        delete fbo;
    }

    /**
     * @brief Load and initialize shaders
     */
    virtual void initialize (void)
    {
        // searches in default shader directory (/shaders) for shader files phongShader.(vert,frag,geom,comp)
        fbo = new Framebuffer();
        loadShader(ssrt_shader, "ssrt") ;
        loadShader(depthMap, "depthMap");
        loadShader(final, "showFbo");
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
    virtual void render(Mesh& mesh, const Trackball& camera_trackball, const Trackball& light_trackball)
    {
        Eigen::Vector4f viewport = camera_trackball.getViewport();
        Eigen::Vector2i viewport_size = camera_trackball.getViewportSize();

        glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);

        // check if viewport was modified, if so, regenerate fbo
        if (fbo->getWidth() != viewport_size[0] || fbo->getHeight() != viewport_size[1])
        {
            fbo->create(viewport_size[0], viewport_size[1], 5);
        }

        glEnable(GL_DEPTH_TEST);
        glClearColor(1.0, 1.0, 1.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //createViewSpaceBuffer(mesh,camera_trackball , light_trackball);
        renderScreen(mesh,camera_trackball , light_trackball);

    }
    void renderScreen (Mesh& mesh, const Trackball& camera_trackball, const Trackball& light_trackball)
    {
        final.bind();
        final.setUniform("projectionMatrix", camera_trackball.getProjectionMatrix());
        final.setUniform("modelMatrix", mesh.getModelMatrix());
        final.setUniform("viewMatrix", camera_trackball.getViewMatrix());
        final.setUniform("lightViewMatrix", light_trackball.getViewMatrix());
        final.setUniform("has_color", mesh.hasAttribute("in_Color"));

        mesh.setAttributeLocation(final);
        mesh.render();

        final.unbind();
    }

    void createViewSpaceBuffer (Mesh& mesh, const Trackball& camera_trackball, const Trackball& light_trackball)
    {
        // Bind buffer to store coord, normal and color information
        fbo->clearAttachments();
        fbo->bindRenderBuffers(depthTextureID, normalTextureID, colorTextureID);

        depthMap.bind();
        depthMap.setUniform("projectionMatrix", camera_trackball.getProjectionMatrix());
        depthMap.setUniform("modelMatrix",mesh.getModelMatrix());
        depthMap.setUniform("viewMatrix", camera_trackball.getViewMatrix());
        depthMap.setUniform("lightViewMatrix", light_trackball.getViewMatrix());
//        depthMap.setUniform("has_color", mesh.hasAttribute("in_Color"));

        mesh.setAttributeLocation(depthMap);
        mesh.render();

        depthMap.unbind();
        fbo->unbind();
        fbo->clearDepth();
    }
};

}


#endif
