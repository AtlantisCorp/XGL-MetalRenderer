//
//  XGLMetalSurface.h
//  XGLMetalRenderer
//
//  Created by jacques tronconi on 14/07/2021.
//

#ifndef __XGL_MTLSURFACE_H__
#define __XGL_MTLSURFACE_H__

#include "OSXIncludes.h"

namespace XGL
{
    /**
     *  @brief Defines an XGL::ISurface for MTL renderer.
     *
     */
    class MTLSurface : public ISurface, public Class < MTLSurface >
    {
        //! @brief The MTKView.
        id mView;
        
        //! @brief The associated IWindow.
        PIWindow mWindow;
        
        //! @brief The current MTLRenderCommandEncoder.
        id mEncoder;
        
        //! @brief The XGLMTKViewDelegate.
        id mDelegate;
        
    public:
        
        //! @brief Constructs a new instance.
        MTLSurface(IRenderer& renderer, id mView, id delegate, const PIWindow& window);
        
        //! @brief Returns the MTKView.
        id view() const;
        
        //! @brief Returns the surface frame.
        virtual Frame frame() const;
        
        //! @brief Returns the associated IWindow.
        virtual PIWindow window() const;
        
        //! @brief Returns true if this surface owns the IWindow.
        virtual bool ownsWindow() const;
    
        //! @brief Creates a new RenderCommandEncoder for the given
        //! RenderPass.
        virtual void begin(const RenderPass& rhs);
        
        //! @brief Ends the current RenderCommandEncoder.
        virtual void end();
        
        //! @brief Returns a RenderPass suitable to render to this surface.
        virtual RenderPass createRenderPass();
    };
    
    std::shared_ptr < MTLSurface > PMTLSurface;
}

#endif /* __XGL_MTLSURFACE_H__ */
