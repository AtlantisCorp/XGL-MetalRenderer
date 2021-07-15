//
//  XGLMTLSurface.m
//  XGLMetalRenderer
//
//  Created by jacques tronconi on 14/07/2021.
//

#include "XGLMTLSurface.h"
#include "XGLMetalRenderer.h"

namespace XGL
{
    MTLSurface::MTLSurface(IRenderer& renderer, id view, id delegate, const PIWindow& window):
    ISurface(renderer),
    mView(view),
    mWindow(window),
    mDelegate(delegate)
    {
        XGLThrowIf(!view, std::runtime_error("XGL:MTLSurface(): Null view."));
        XGLThrowIf(!window, std::runtime_error("XGL:MTLSurface(): Null window."));
    }
    
    id MTLSurface::view() const
    {
        return mView;
    }
    
    Frame MTLSurface::frame() const
    {
        XGLThrowIf(!mView, std::runtime_error("XGL:MTLSurface:frame(): No MTKView."));
        NSRect rect = [(MTKView*)mView frame];
        return Frame {
            .x = static_cast < size_t >(rect.origin.x),
            .y = static_cast < size_t >(rect.origin.y),
            .width = static_cast < size_t >(rect.size.width),
            .height = static_cast < size_t >(rect.size.height)
        };
    }
    
    PIWindow MTLSurface::window() const
    {
        return std::atomic_load(&mWindow);
    }
    
    bool MTLSurface::ownsWindow() const
    {
        return false;
    }
    
    void MTLSurface::begin(const RenderPass& rhs)
    {
        MTLRenderPassDescriptor* ldescriptor = MakeMTLRenderPassDescriptor(rhs);
        XGLThrowIf(!ldescriptor, std::runtime_error("XGL:MTLSurface:begin(): Cannot create an "
                                                    "MTLRenderPassDescriptor  instance."));
        
        MTLRenderer& lrend = dynamic_cast < MTLRenderer& >(renderer());
        id < MTLRenderCommandEncoder > lencoder = lrend.createRenderCommandEncoder(ldescriptor);
        XGLThrowIf(!lencoder, std::runtime_error("XGL:MTLSurface:begin(): Cannot create "
                                                 "MTLRenderCommandEncoder."));
        
        lrend.setCurrentRenderCommandEncoderUnsafe(lencoder);
    }
    
    void MTLSurface::end()
    {
        MTLRenderer& lrend = dynamic_cast < MTLRenderer& >(renderer());
        id < MTLRenderCommandEncoder > lenc = lrend.currentRenderCommandEncoder();
        
        if (lenc)
        {
            [lenc endEncoding];
            lrend.setCurrentRenderCommandEncoderUnsafe(nil);
        }
    }
    
    RenderPass MTLSurface::createRenderPass()
    {
        MTLRenderPassDescriptor* ldesc = [(MTKView*)mView currentRenderPassDescriptor];
        XGLThrowIf(!ldesc, std::runtime_error("XGL:MTLSurface:createRenderPass(): Cannot get current "
                                              "render pass descriptor."));
        return MakeRenderPass(ldesc);
    }
}
