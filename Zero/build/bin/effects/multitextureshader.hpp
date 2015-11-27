#ifndef __MULTITEXTURESHADER__
#define __MULTITEXTURESHADER__

#include <tucano.hpp>
#include <camera.hpp>
#include <photo/multiTextureManagerObj.h>
#include <framebuffer.hpp>
using namespace Tucano;

namespace Effects {
    class MultiTexture: public Effect
    {
    private:
        Framebuffer *fbo;

        Shader multi;
        Shader showFbo;

        Eigen::Vector4f default_color;
        int coordTextureID;

        Mesh quad;
    public:
        MultiTexture(void)
        {
            default_color << 0.7, 0.7, 0.7, 1.0;
            coordTextureID = 0;
            fbo = 0;
        }
        virtual ~MultiTexture(void){}

        virtual void initialize(void)
        {
            loadShader(multi, "multitextureshader");
            loadShader(showFbo, "showFbo");

            fbo = new Framebuffer();
            quad.createQuad();
        }
        void render (Tucano::Mesh& mesh, const Tucano::Camera& camera, const Tucano::Camera& lightTrackball)
        {

            Eigen::Vector4f viewport = camera.getViewport();
            glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);

            multi.bind();

            // sets all uniform variables for the phong shader
            multi.setUniform("projectionMatrix",    camera.getProjectionMatrix());
            multi.setUniform("modelMatrix",         mesh.getModelMatrix());
            multi.setUniform("viewMatrix",          camera.getViewMatrix());
            multi.setUniform("lightViewMatrix",     lightTrackball.getViewMatrix());
            multi.setUniform("has_color",           mesh.hasAttribute("in_Color"));
            multi.setUniform("default_color",       default_color);
            multi.setUniform("in_viewPort",         viewport);

            mesh.setAttributeLocation(multi);

            glEnable(GL_DEPTH_TEST);
            mesh.render();

            multi.unbind();
        }
        void render (MultiTextureManagerObj& multiTex, const Tucano::Camera& camera, const Tucano::Camera& lightTrackball)
        {
            //this version use multiTextureObj
//          renderSimple(multiTex, camera, lightTrackball);
            renderToFBO(multiTex, camera, lightTrackball);
            renderFromFbo(multiTex);
        }
        void renderToFBO (MultiTextureManagerObj& multiTex, const Tucano::Camera& camera, const Tucano::Camera& lightTrackball)
        {
            Eigen::Vector4f viewport = camera.getViewport();
            Eigen::Vector2i viewport_size = camera.getViewportSize();

            glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);
            if(fbo->getWidth() != viewport_size[0], fbo->getHeight() != viewport_size[1])
            {
                fbo->create(viewport_size[0], viewport_size[1], 1);
            }
            fbo->clearAttachments();
            fbo->bindRenderBuffer(coordTextureID);

            renderSimple(multiTex, camera, lightTrackball);

            fbo->unbind();
            fbo->clearDepth();
        }
        void renderFromFbo(MultiTextureManagerObj& multiTex)
        {
            showFbo.bind();
            showFbo.setUniform("imageTexture", fbo->bindAttachment(coordTextureID));

            quad.render();

            showFbo.unbind();
            fbo->unbindAttachments();
        }
        void renderSimple (MultiTextureManagerObj& multiTex, const Tucano::Camera& camera, const Tucano::Camera& lightTrackball)
        {
            Eigen::Vector4f viewport = camera.getViewport();
            glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);

            multi.bind();

            // sets all uniform variables for the phong shader
            multi.setUniform("projectionMatrix", camera.getProjectionMatrix());
            multi.setUniform("modelMatrix", (*multiTex.getMesh()).getModelMatrix());
            multi.setUniform("viewMatrix", camera.getViewMatrix());
            multi.setUniform("lightViewMatrix", lightTrackball.getViewMatrix());
            multi.setUniform("has_color", (*multiTex.getMesh()).hasAttribute("in_Color"));
            multi.setUniform("default_color", default_color);
            multi.setUniform("in_viewPort", Eigen::Vector2f(viewport(2),viewport(3)));

            multiTex.getMesh()->setAttributeLocation(multi);
            glEnable(GL_DEPTH_TEST);

            multiTex.getMesh()->render();

            multi.unbind();
        }
    };
}

#endif // MULTITEXTURESHADER

