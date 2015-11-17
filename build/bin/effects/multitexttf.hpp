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
#include <photo/multiTextureManagerObj.h>

using namespace Tucano;

namespace Effects
{

/**
 * @brief Renders a mesh using a Phong shader.
 */
class MultiTextTF : public Effect
{

private:
    Framebuffer *fbo;

    /// Phong Shader
    Shader multiTextRender;
    Shader multiTF;
    Shader depthMap;

    Shader showFBO;

	/// Default color
	Eigen::Vector4f default_color;

    int depthTextureID;

    Mesh quad;

    bool firstFlag;
public:

    /**
     * @brief Default constructor.
     */
    MultiTextTF (void)
    {
		default_color << 0.7, 0.7, 0.7, 1.0;
        fbo             = 0;
        depthTextureID  = 0;
        firstFlag       = true;
    }

    /**
     * @brief Default destructor
     */
    virtual ~MultiTextTF (void) {
        delete fbo;
    }

    /**
     * @brief Load and initialize shaders
     */
    virtual void initialize (void)
    {
        loadShader(depthMap, "depthmap");
        loadShader(showFBO, "showFbo");


        multiTF.load("multitf", shaders_dir);
        const char* vars[] = {"nColor"};
        multiTF.initializeTF(1, vars);
        shaders_list.push_back(&multiTF);

        // searches in default shader directory (/shaders) for shader files phongShader.(vert,frag,geom,comp)
        loadShader(multiTextRender, "mtextrender") ;

        fbo = new Framebuffer();
        quad.createQuad();
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
    void depthMapRender (Tucano::Mesh& mesh, const Tucano::Camera& camera, const Tucano::Camera& lightTrackball)
    {
        Eigen::Vector4f viewPort = camera.getViewport();
        Eigen::Vector2i viewport_size = camera.getViewportSize();
        int size = 1;
        viewPort << 0, 0, viewport_size[0] * size, viewport_size[1] * size;
        glViewport(viewPort[0], viewPort[1], viewPort[2], viewPort[3]);

        if(fbo->getWidth() != viewport_size[0] || fbo->getHeight() != viewport_size[1])
        {
            fbo->create(viewport_size[0], viewport_size[1], 1);
        }

        fbo->clearAttachments();
        fbo->bindRenderBuffer(depthTextureID);

            depthMap.bind();

            depthMap.setUniform("projectionMatrix", camera.getProjectionMatrix());
            depthMap.setUniform("modelMatrix", mesh.getModelMatrix());
            depthMap.setUniform("viewMatrix", camera.getViewMatrix());

            mesh.setAttributeLocation(depthMap);

            glEnable(GL_DEPTH_TEST);
            mesh.render();
//            mesh.bindBuffers();
//            mesh.renderPoints();
//            mesh.unbindBuffers();

            depthMap.unbind();

        fbo->unbind();
        fbo->clearDepth();
    }

    void updateTF (Tucano::Mesh& mesh, const Tucano::Camera& camera, const Tucano::Camera& lightTrackball)
    {
        qDebug() << "updateTF 0";

        Eigen::Vector2f viewport = Eigen::Vector2f(camera.getViewport()[2], camera.getViewport()[3]);

        multiTF.bind();
            glEnable(GL_RASTERIZER_DISCARD);

                multiTF.setUniform("in_Viewport", viewport);
                multiTF.setUniform("projectionMatrix", camera.getProjectionMatrix());
                multiTF.setUniform("modelMatrix", mesh.getModelMatrix());
                multiTF.setUniform("viewMatrix", camera.getViewMatrix());
                multiTF.setUniform("imageTexture", fbo->bindAttachment(depthTextureID));
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
        fbo->unbindAttachments();
    }

    void updateTF (MultiTextureManagerObj& multiTex, const Tucano::Camera& camera, const Tucano::Camera& lightTrackball)
    {
        qDebug() << "updateTF 0";
        Mesh &mesh = *multiTex.getMesh();
        Eigen::Vector2f viewport = Eigen::Vector2f(camera.getViewport()[2], camera.getViewport()[3]);

        multiTF.bind();
            glEnable(GL_RASTERIZER_DISCARD);

                multiTF.setUniform("in_Viewport", viewport);
                multiTF.setUniform("projectionMatrix", camera.getProjectionMatrix());
                multiTF.setUniform("modelMatrix", mesh.getModelMatrix());
                multiTF.setUniform("viewMatrix", camera.getViewMatrix());
                multiTF.setUniform("depthMapTexture", fbo->bindAttachment(depthTextureID));
                multiTF.setUniform("imageTexture", multiTex.getBaseTexture()->bind());
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
        fbo->unbindAttachments();
    }

    void render (Tucano::Mesh& mesh, const Tucano::Camera& camera, const Tucano::Camera& lightTrackball)
    {
        if(firstFlag){
            depthMapRender(mesh, camera, lightTrackball);
            //renderFbo(mesh, camera, lightTrackball);
            updateTF(mesh, camera, lightTrackball);
            firstFlag = false;
        }
        renderSimple(mesh, camera, lightTrackball);
    }
    void render (MultiTextureManagerObj& multiTex, const Tucano::Camera& camera, const Tucano::Camera& lightTrackball)
    {
        if(firstFlag){
            depthMapRender(*multiTex.getMesh(), camera, lightTrackball);
            updateTF(multiTex, camera, lightTrackball);
            firstFlag = false;
        }
        renderSimple(*multiTex.getMesh(), camera, lightTrackball);
    }

    void renderFbo(Tucano::Mesh& mesh, const Tucano::Camera& camera, const Tucano::Camera& lightTrackball)
    {
        showFBO.bind();
        showFBO.setUniform("imageTexture", fbo->bindAttachment(depthTextureID));

        quad.render();

        showFBO.unbind();
        fbo->unbindAttachments();
    }

    void renderSimple(Tucano::Mesh& mesh, const Tucano::Camera& camera, const Tucano::Camera& lightTrackball)
    {
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
