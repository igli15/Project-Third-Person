#ifndef COLORMATERIAL_HPP
#define COLORMATERIAL_HPP

#include "GL/glew.h"
#include "mge/materials/AbstractMaterial.hpp"

class ShaderProgram;

/**
 * This is about the simplest material we can come up with, it demonstrates how to
 * render a single color material without caching, passing in all the matrices we require separately.
 */
class ColorMaterial : public AbstractMaterial
{
    public:
        ColorMaterial();
        virtual ~ColorMaterial();

		virtual void render(World* pWorld, MeshRenderer* meshRenderer, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) override;

        //in rgb values
        void SetDiffuseColor (glm::vec3 pDiffuseColor);

		void SetShineness(float shineValue);

    private:
        //all the static properties are shared between instances of ColorMaterial
        //note that they are all PRIVATE, we do not expose this static info to the outside world
        static ShaderProgram* m_shaderProgram;
        static void InitializeShader();

        //this one is unique per instance of color material
        glm::vec3 m_diffuseColor = glm::vec3(1,1,1);
		float m_shineness = 8;
};

#endif // COLORMATERIAL_HPP
