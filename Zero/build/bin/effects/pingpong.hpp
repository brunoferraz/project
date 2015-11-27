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

#ifndef __PINGPONG__
#define __PINGPONG__

#include <tucano.hpp>
#include <camera.hpp>

using namespace Tucano;

namespace Effects
{

/**
 * @brief Renders a mesh using a Phong shader.
 */
class PingPong : public Effect
{

private:

    /// Phong Shader
    Shader pprender;
    Shader pptf;

    VertexAttribute *write_va;
    VertexAttribute *read_va;

	/// Default color
	Eigen::Vector4f default_color;

public:

    /**
     * @brief Default constructor.
     */
    PingPong (void)
    {
		default_color << 0.7, 0.7, 0.7, 1.0;
        read_va = NULL;
        write_va = NULL;
    }

    /**
     * @brief Default destructor
     */
    virtual ~PingPong (void) {}

    /**
     * @brief Load and initialize shaders
     */
    virtual void initialize (void)
    {
        pptf.load("pptf", shaders_dir);
        const char* vars[] = {"nPos"};
        pptf.initializeTF(1, vars);
        shaders_list.push_back(&pptf);


        // searches in default shader directory (/shaders) for shader files phongShader.(vert,frag,geom,comp)
        loadShader(pprender, "pptfrender") ;
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
        //qDebug() << "UPDATING TF2";
        pptf.bind();
            //mesh.setAttributeLocation(tf);
            glEnable(GL_RASTERIZER_DISCARD);
                mesh.bindBuffers();
                    Tucano::Misc::errorCheckFunc(__FILE__, __LINE__);
                    //VertexAttribute* va = mesh.getAttribute("nPos");

                    write_va->disable();
                    //glDisableVertexAttribArray(mesh.getAttributeLocation("nPos"));

                    read_va->enable(pptf.getAttributeLocation("inPos"));
                    Tucano::Misc::errorCheckFunc(__FILE__, __LINE__);
                    glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, write_va->getBufferID());
                        glBeginTransformFeedback(GL_POINTS);
                            glEnable(GL_DEPTH_TEST);
                            mesh.renderPoints();
                        glEndTransformFeedback();
                    glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, 0);
                mesh.unbindBuffers();
            glDisable(GL_RASTERIZER_DISCARD);
        pptf.unbind();
    }
    void render (Tucano::Mesh& mesh, const Tucano::Camera& camera, const Tucano::Camera& lightTrackball)
    {
        if(read_va == NULL){
            read_va = mesh.getAttribute("positions1");
            write_va = mesh.getAttribute("positions2");
        }
        //updateTF(mesh, camera, lightTrackball);

        Eigen::Vector4f viewport = camera.getViewport();
        glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);


        pprender.bind();

        // sets all uniform variables for the phong shader
        pprender.setUniform("projectionMatrix", camera.getProjectionMatrix());
        pprender.setUniform("modelMatrix", mesh.getModelMatrix());
        pprender.setUniform("viewMatrix", camera.getViewMatrix());
        pprender.setUniform("lightViewMatrix", lightTrackball.getViewMatrix());
        pprender.setUniform("has_color", mesh.hasAttribute("in_Color"));
        pprender.setUniform("default_color", default_color);

        //BIND BUFFERS TO LOCATIONS

            read_va->enable(pprender.getAttributeLocation("in_Position"));
            mesh.getAttribute("inColor")->enable(pprender.getAttributeLocation("in_Color"));

        glEnable(GL_DEPTH_TEST);

        mesh.renderPoints();
        mesh.unbindBuffers();

        pprender.unbind();

//        VertexAttribute *tmp_va;
//        tmp_va = read_va;
//        read_va = write_va;
//        write_va = tmp_va;
    }
};

}


#endif
