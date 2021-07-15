//
//  XGLMTKViewDelegate.h
//  XGLMetalRenderer
//
//  Created by jacques tronconi on 15/07/2021.
//

#ifndef __XGL_MTKVIEWDELEGATE_H__
#define __XGL_MTKVIEWDELEGATE_H__

#include "OSXIncludes.h"
#include "XGLMTLSurface.h"

@interface XGLMTKViewDelegate : NSObject < MTKViewDelegate >

@property (assign) XGL::MTLSurface* surface;

- (id) init;

@end

#endif /* __XGL_MTKVIEWDELEGATE_H__ */
