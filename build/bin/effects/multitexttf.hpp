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

#ifndef __MULTITEXTTF__
#define __MULTITEXTTF__

#include <tucano.hpp>
#include <camera.hpp>
#include <QDebug>

using namespace Tucano;

namespace Effects
{

/**
 * @brief Renders a mesh using a Phong shader.
 */
class MultiTextTF : public Effect
{

private:

    /// Phong Shader
    Shader multiTextRender;
    Shader multiTF;

	/// Default color
	Eigen::Vector4f default_color;

public:

    /**
     * @brief Default constructor.
     */
    MultiTextTF (void)
    {
		default_color << 0.7, 0.7, 0.7, 1.0;
    }

    /**
     * @brief Default destructor
     */
    virtual ~MultiTextTF (void) {}

    /**
     * @brief Load and initialize shaders
     */
    virtual void initialize (void)
    {
        multiTF.load("multitf", shaders_dir);
        const char* vars[] = {"nColor"};
        multiTF.initializeTF(1, vars);
        shaders_list.push_back(&multiTF);

        // searches in default shader directory (/shaders) for shader files phongShader.(vert,frag,geom,comp)
        loadShader(multiTextRender, "mtextrender") ;
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
    void updateTF (Tucano::Mesh& mesh, const Tucano::Camera& camera, const Tucano::Camera& lightTrackball)
    {
        qDebug() << "updateTF 0";
        multiTF.bind();
            glEnable(GL_RASTERIZER_DISCARD);

                multiTF.setUniform("adjustment", 1 -mesh.getScale());
                mesh.bindBuffers();

                mesh.getAttribute("nColor")->disable();
                mesh.getAttribute("in_Position")->enable();
                mesh.getAttribute("in_Position")->enable(multiTF.getAttributeLocation("in_Position"));
                    glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, mesh.getAttribute("nColor")->getBufferID());
                        glBeginTransformFeedback(GL_POINTS);
                            glEnable(GL_DEPTH_TEST);
                            mesh.renderPoints();
                        glEndTransformFeedback();
                    glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, 0);
                mesh.unbindBuffers();
            glDisable(GL_RASTERIZER_DISCARD);
        multiTF.unbind();
    }

    void render (Tucano::Mesh& mesh, const Tucano::Camera& camera, const Tucano::Camera& lightTrackball)
    {
        updateTF(mesh, camera, lightTrackball);

        Eigen::Vector4f viewport = camera.getViewport();
        glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);

        multiTextRender.bind();

        // sets all uniform variables for the phong shader
        multiTextRender.setUniform("projectionMatrix", camera.getProjectionMatrix());
        multiTextRender.setUniform("modelMatrix", mesh.getModelMatrix());
        multiTextRender.setUniform("viewMatrix", camera.getViewMatrix());
        multiTextRender.setUniform("lightViewMatrix", lightTrackball.getViewMatrix());
        multiTextRender.setUniform("has_color", mesh.hasAttribute("in_Color"));
        multiTextRender.setUniform("default_color", default_color);

//      mesh.setAttributeLocation(multiTextRender);

        mesh.getAttribute("in_Position")->enable(multiTextRender.getAttributeLocation("in_Position"));
        mesh.getAttribute("in_Normal")->enable(multiTextRender.getAttributeLocation("in_Normal"));
        mesh.getAttribute("nColor")->enable(multiTextRender.getAttributeLocation("in_Color"));

//      qDebug() << mesh.hasAttribute("in_Position");
        glEnable(GL_DEPTH_TEST);

        //why need to bind to renderelements? whitout bind online renderPoints works
        mesh.bindBuffers();
        mesh.renderElements();
        mesh.unbindBuffers();

        multiTextRender.unbind();

    }
};

}


#endif
