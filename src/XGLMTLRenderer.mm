//
//  XGLMTLRenderer.mm
//  XGLMTLRenderer
//
//  Created by jacques tronconi on 14/07/2021.
//

#include "XGLMTLRenderer.h"
#include "XGLMTLSurface.h"
#include "XGLMTKViewDelegate.h"

namespace XGL
{
    MTLRenderer::MTLRenderer():
    mDevice(nil),
    mCurrentEncoder(nil)
    {
        
    }
    
    const char* MTLRenderer::name() const
    {
        return "XGLMTLRenderer";
    }
    
    void MTLRenderer::initialize(const RendererInitArgs& args)
    {
        XGLThrowIf(mDevice, std::runtime_error("XGL:MTLRenderer:initialize(): MTLDevice already "
                                               "initialized."));
        
        mDevice = MTLCreateSystemDefaultDevice();
        XGLThrowIf(!mDevice, std::runtime_error("XGL:MTLRenderer:initialize(): Cannot find "
                                                "any suitable MTLDevice."));
    }
    
    bool MTLRenderer::isRendering() const
    {
        return mCurrentEncoder != nil;
    }
    
    id MTLRenderer::currentRenderCommandEncoder() const
    {
        return mCurrentEncoder;
    }
    
    void MTLRenderer::setCurrentRenderCommandEncoder(id rhs)
    {
        mCurrentEncoder = rhs;
    }
    
    PISurface MTLRenderer::createSurface(const PIWindow& window)
    {
        XGLThrowIf(!window, std::runtime_error("XGL:MTLRenderer:createSurface(): Null window."));
        XGLThrowIf(!mDevice, std::runtime_error("XGL:MTLRenderer:createSurface(): Null MTLDevice. "
                                                "Please call initialize() before doing anyhting with "
                                                "the XGL IRenderer."));
        Frame lframe = window->frame();
        MTKView* lview = [[MTKView alloc] initWithFrame:NSMakeRect(lframe.x, lframe.y, lframe.width, lframe.height)
                                                 device:mDevice];
        XGLThrowIf(!lview, std::runtime_error("XGL:MTLRenderer:createSurface(): Cannot create MTKView "
                                              "instance."));
        
        XGLMTKViewDelegate* ldelegate = [[XGLMTKViewDelegate alloc] init];
        
        PMTLSurface lsurface = MTLSurface::New(*this, lview, ldelegate, window);
        ldelegate.surface = lsurface.get();
        
        NSWindow* lwin = window->handle();
        [lwin setContentView:lview];
        
        return lsurface;
    }
}
