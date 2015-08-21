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
        Shader multi;

        Eigen::Vector4f default_color;
    public:
        MultiTexture(void)
        {
            default_color << 0.7, 0.7, 0.7, 1.0;
        }
        virtual ~MultiTexture(void){}

        virtual void initialize(void)
        {
            loadShader(multi, "multitextureshader");
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

            multiTex.getMesh()->setAttributeLocation(multi);
            glEnable(GL_DEPTH_TEST);

            multiTex.getMesh()->render();

            multi.unbind();
        }
    };
}

#endif // MULTITEXTURESHADER

