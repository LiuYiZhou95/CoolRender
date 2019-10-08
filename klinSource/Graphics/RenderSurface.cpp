////
//// Created by liuyizhou on 2019/9/24.
////
//
//#include "RenderSurface.h"
//
//
//#include "Camera.h"
//#include "Graphics.h"
//#include "GraphicsImpl.h"
//#include "Renderer.h"
//#include "RenderSurface.h"
//#include "Texture.h"
//
//
//
//RenderSurface::~RenderSurface() {
//    Release();
//}
//
//void RenderSurface::SetNumViewports(unsigned num) {
//    viewports_.reserve(num);
//}
//
//void RenderSurface::SetViewport(unsigned index, Viewport *viewport) {
////    if (index >= viewports_.size())
////        viewports_.reserve(index + 1);
////
////    viewports_[index] = viewport;
//}
//
//void RenderSurface::SetUpdateMode(RenderSurfaceUpdateMode mode) {
//    updateMode_ = mode;
//}
//
//void RenderSurface::SetLinkedRenderTarget(RenderSurface *renderTarget) {
////    if (renderTarget != this)
////        //是否过期
////        if (linkedRenderTarget_.expired())
////            linkedRenderTarget_.lock()= renderTarget;
//}
//
//void RenderSurface::SetLinkedDepthStencil(RenderSurface *depthStencil) {
////    if (depthStencil != this)
////        //是否过期
////        if (linkedDepthStencil_.expired())
////            linkedDepthStencil_.lock() = depthStencil;
//}
//
//void RenderSurface::QueueUpdate() {
//    updateQueued_ = true;
//}
//
//void RenderSurface::ResetUpdateQueued() {
//    updateQueued_ = false;
//}
//
//int RenderSurface::GetWidth() const {
//    return parentTexture_->getWidth();
//}
//
//int RenderSurface::GetHeight() const {
//    return parentTexture_->getHeight();
//}
//
//TextureUsage RenderSurface::GetUsage() const {
//    return parentTexture_->getUsage();
//}
//
//int RenderSurface::GetMultiSample() const {
//    return parentTexture_->getMultiSample();
//}
//
//bool RenderSurface::GetAutoResolve() const {
//    return parentTexture_->getAutoResolve();
//}
//
//Viewport *RenderSurface::GetViewport(unsigned index) const {
//    return index < viewports_.size() ? viewports_[index].get() : nullptr;
//}
//
//
