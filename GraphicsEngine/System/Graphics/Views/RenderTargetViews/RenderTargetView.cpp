#include "RenderTargetView.h"
#include "../../Graphics.h"

RenderTargetView::RenderTargetView(Texture2D* textureResource)
{
	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc;

    rtvDesc.Format = *(textureResource->GetFormat());
 	rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
 	rtvDesc.Texture2D.MipSlice = 0;

    Graphics::GetInstance().GetDevice()->CreateRenderTargetView(textureResource->GetTexture(), &rtvDesc, &m_renderTargetView);
}

void RenderTargetView::Release()
{
	if (m_renderTargetView)
		m_renderTargetView->Release();
}