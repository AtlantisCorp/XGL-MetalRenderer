//
//  XGLMTLRenderer.h
//  XGLMTLRenderer
//
//  Created by jacques tronconi on 14/07/2021.
//

#ifndef __XGL_MTLRENDERER_H__
#define __XGL_MTLRENDERER_H__

#include "OSXIncludes.h"

namespace XGL
{
    /**
     *  @brief Defines a IRenderer for Metal.
     *
     */
    class MTLRenderer : public IRenderer, public Class < MTLRenderer >
    {
        //! @brief The global MTLDevice.
        id mDevice;
        
        //! @brief The current MTLRenderCommandEncoder. Nil by default,
        //! any XGL::IRenderTarget can set the encoder through the function
        //! setRenderCommandEncoderUnsafe().
        id mCurrentEncoder;
        
    public:
        //! @brief Constructs a new instance.
        MTLRenderer();
        
        //! @brief Returns the renderer name.
        virtual const char* name() const;
        
        /// @brief Initializes the IRenderer. The options can vary between different
        /// renderers.
        virtual void initialize(const RendererInitArgs& options);
        
        //! @brief Returns true if the current encoder is not nil.
        virtual bool isRendering() const;
        
        //! @brief Returns the current MTLRenderCommandEncoder.
        id currentRenderCommandEncoder() const;
        
        //! @brief Sets the current MTLRenderCommandEncoder.
        void setCurrentRenderCommandEncoderUnsafe(id rhs);
        
        //! @brief Creates a new RenderCommandEncoder from an MTLRenderPassDescriptor.
        id createRenderCommandEncoder(id descriptor);
        
        //! @brief Creates a new ISurface from a IWindow.
        virtual PISurface createSurface(const PIWindow& window);
        
        //! @brief Creates a new ISurface and its IWindow.
        virtual std::shared_ptr < ISurface > createSurface(const WindowArgs& args) = 0;
        
        //! @brief Creates a new IBuffer.
        virtual std::shared_ptr < IBuffer > createBuffer(BufferRole role, size_t size, const void* data = NULL) = 0;
        
        //! @brief Creates a new IBuffer and sets the data to given vector.
        template < typename T > inline auto createBuffer(BufferRole role, const std::vector < T >& data) {
            return createBuffer(role, data.size() * sizeof(T), &data[0]);
        }
        
        //! @brief Creates a new IShader.
        virtual std::shared_ptr < IShader > createShader(ShaderType type, const std::string& filename, const std::string& entry = "main") = 0;
        
        //! @brief Returns the 'default' ShaderLibrary if existent, or nullptr.
        virtual std::shared_ptr < IShaderLibrary > defaultShaderLibrary() = 0;
        
        //! @brief Tries to load a ShaderLibrary from a file.
        virtual std::shared_ptr < IShaderLibrary > createShaderLibrary(const std::string& filename) = 0;
        
        //! @brief Creates a new 1D texture.
        virtual std::shared_ptr < ITexture > createTexture1d(PixelFormat::_ format, size_t width, PixelFormat::_ inFormat, const void* data) = 0;
        
        //! @brief Creates a new 2D texture.
        virtual std::shared_ptr < ITexture > createTexture2d(PixelFormat::_ format, size_t width, size_t height, PixelFormat::_ inFormat, const void* data) = 0;
        
        //! @brief Creates a new 3D texture.
        virtual std::shared_ptr < ITexture > createTexture3d(PixelFormat::_ format, size_t width, size_t height, size_t depth, PixelFormat::_ inFormat, const void* data) = 0;
        
        //! @brief Sets the viewport.
        virtual void setViewport(size_t x, size_t y, size_t width, size_t height) = 0;
        
        //! @brief Sets the current shader for a stage.
        virtual void setShader(ShaderType type, const std::shared_ptr < IShader >& shader) = 0;
        
        //! @brief Sets a value for the specified shader.
        virtual void setUniform(ShaderType type, const std::string& name, const std::any& value) = 0;
        
        //! @brief Sets a texture for the specified shader.
        virtual void setTexture(ShaderType type, const std::string& name, const std::shared_ptr < ITexture >& texture) = 0;
        
        //! @brief Binds a vertex buffer.
        virtual void bindVertexBuffer(const std::string& name, const std::shared_ptr < IBuffer >& buffer, Attrib::Type type, size_t stride) = 0;
        
        //! @brief Binds a Vertex and some VertexBuffers.
        virtual void bindVertexBuffers(const Vertex& vertex, const VertexBuffers& buffers) = 0;
        
        //! @brief Draws something from the bound vertex buffer.
        virtual void drawElements(DrawMode mode, size_t first, size_t count, size_t firstInstance = 0, size_t numInstance = 1) = 0;
        
        //! @brief Draws something from the bound vertex buffers and an index buffer.
        virtual void drawIndexedElements(const std::shared_ptr < IBuffer >& buffer, Elements::Type type, DrawMode mode, size_t first, size_t count, size_t firstInstance = 0, size_t numInstance = 1) = 0;
    };
    
    typedef std::shared_ptr < MTLRenderer > PMTLRenderer;
}

#endif /* __XGL_METALRENDERER_H__ */
