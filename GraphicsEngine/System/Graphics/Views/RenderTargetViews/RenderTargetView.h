#ifndef _RENDER_TARGET_VIEW_H_
#define _RENDER_TARGET_VIEW_H_

#include "../../../../Resource/Textures/Texture2D.h"

class RenderTargetView
{
	ID3D11RenderTargetView *m_renderTargetView;

    public:
    RenderTargetView(Texture2D*);
	RenderTargetView() = delete;
	void Release();
    ID3D11RenderTargetView* GetRenderTarget() {return m_renderTargetView;}
};

#endif //!_RENDER_TARGET_VIEW_H_