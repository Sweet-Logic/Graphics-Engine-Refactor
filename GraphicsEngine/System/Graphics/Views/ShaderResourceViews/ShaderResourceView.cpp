#include "ShaderResourceView.h"
#include "../../Graphics.h"
ShaderResourceView::ShaderResourceView(Texture2D* textureResource)
{
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;


    srvDesc.Format = *(textureResource->GetFormat());
 	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
 	srvDesc.Texture2D.MipLevels = 1;
    srvDesc.Texture2D.MostDetailedMip = 0;

    Graphics::GetInstance().GetDevice()->CreateShaderResourceView(textureResource->GetTexture(), &srvDesc, &m_resourceView);
}

void ShaderResourceView::Release()
{
    if(m_resourceView)
        m_resourceView->Release();
}