//
//  XGLMTKViewDelegate.m
//  XGLMetalRenderer
//
//  Created by jacques tronconi on 15/07/2021.
//

#include "XGLMTKViewDelegate.h"

@implementation XGLMTKViewDelegate
@synthesize surface;

- (id) init
{
    self = [super init];
    
    if (self)
    {
        self.surface = nil;
    }
    
    return self;
}

- (void)mtkView:(MTKView *)view drawableSizeWillChange:(CGSize)size
{
    XGLThrowIf(!surface, std::runtime_error("XGLMTKViewDelegate:mtkView:drawableSizeWillChange: Null surface."));
    
    _surface->Resized.call(*_surface,
                           static_cast < size_t >(size.width),
                           static_cast < size_t >(size.height));
}

- (void)drawInMTKView:(MTKView *)view
{
    XGLThrowIf(!surface, std::runtime_error("XGLMTKViewDelegate:drawInMTKView: Null surface."));
    _surface->Render.call(*_surface);
}

@end
