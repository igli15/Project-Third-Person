#ifndef TEXTUREMATERIAL_HPP
#define TEXTUREMATERIAL_HPP

#include "mge/materials/AbstractMaterial.hpp"
#include "GL/glew.h"

class ShaderProgram;
class Texture;

/**
 * This material is already a little bit more complicated, instead of a color we can pass in a texture,
 * all attributes and uniforms are cached and we precompute the MVP matrix passing it in as one entity.
 */
class TextureMaterial : public AbstractMaterial
{
    public:
        TextureMaterial (Texture* pDiffuseTexture,Texture* specularTexture,Texture* emissionTexture,Texture* normalMap = nullptr);
        virtual ~TextureMaterial ();

        virtual void render(World* pWorld, MeshRenderer* meshRenderer, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) override;

        void setDiffuseTexture (Texture* pDiffuseTexture);
		void SetSpecularTexture(Texture* specularTexture);
		void SetEmissionTexture(Texture* emissionTexture);
		void SetDiffuseColor(glm::vec3 color);
		void SetShininess(float shininess);

    protected:
    private:
        static ShaderProgram* m_shaderProgram;
        static void _lazyInitializeShader();

        //in this example we cache all identifiers for uniforms & attributes
        static GLint _uMVPMatrix;
        static GLint _uDiffuseTexture;

        static GLint _aVertex ;
        static GLint _aNormal;
        static GLint _aUV ;

        Texture* _diffuseTexture = nullptr;
		Texture* m_spcecularTexture = nullptr;
		Texture* m_emissionTexture = nullptr;
		Texture* m_normalMap = nullptr;

		float m_shineness = 8;

		glm::vec3 m_diffuseColor = glm::vec3(1, 1, 1);

        TextureMaterial(const TextureMaterial&);
        TextureMaterial& operator=(const TextureMaterial&);

		Texture* m_whiteTex;
		Texture* m_blackTex;
		Texture* m_normalFlatTex;

};

#endif // TEXTUREMATERIAL_HPP
