#include "Application.h"
#include "System/Graphics/Graphics.h"
#include "System/Window/Window.h"

#include "SceneManagement/SceneManager.h"
#include "Resource/Managers/ResourceManager.h"

#include "File_IO/DirectoryService.h"

#define DBOUT( s )            \
{                             \
   std::wostringstream os_;    \
   os_ << s;                   \
   OutputDebugStringW( os_.str().c_str() );  \
}

//CameraObject* Application::_currentCamera = nullptr;



// void Application::BuildScene(std::string BuildFile)
// {
// 	XML::XMLReader doc = XML::XMLReader(BuildFile);

// 	std::vector<XML::Tag> objectsToLoad = doc.GetTags("Object"); 	1

// 	for (int i = 0; i < objectsToLoad.size(); i++)
// 	{
// 		std::string objectType = objectsToLoad.at(i).childTags.at(0).parameters.at(0).Value;
// 		if (objectType == "CarBaseObject")
// 		{
// 			_carReferance = new CarBaseObject("Car");

// 			XMFLOAT3 tempFloat = GetVectorFrom(objectsToLoad.at(i).GetChildTag("Position_3Float").Text);

// 			XMFLOAT4 temp4Float = XMFLOAT4(tempFloat.x, tempFloat.y, tempFloat.z, 1.0f);

// 			_carReferance->TranslateObject(XMLoadFloat4(&temp4Float));


// 			tempFloat = GetVectorFrom(objectsToLoad.at(i).GetChildTag("Rotation_3Float").Text);

// 			temp4Float = XMFLOAT4(tempFloat.x, tempFloat.y, tempFloat.z, 1.0f);

// 			_carReferance->RotateObject(XMLoadFloat4(&temp4Float));


// 			tempFloat = GetVectorFrom(objectsToLoad.at(i).GetChildTag("Scale_3Float").Text);

// 			temp4Float = XMFLOAT4(tempFloat.x, tempFloat.y, tempFloat.z, 1.0f);

// 			_carReferance->ScaleObject(XMLoadFloat4(&temp4Float));
// 		}
// 		else if (objectType == "BallObject")
// 		{
// 			BallObject* newObject = new BallObject();


// 			XMFLOAT3 tempFloat = GetVectorFrom(objectsToLoad.at(i).GetChildTag("Position_3Float").Text);

// 			XMFLOAT4 temp4Float = XMFLOAT4(tempFloat.x, tempFloat.y, tempFloat.z, 1.0f);

// 			newObject->TranslateObject(XMLoadFloat4(&temp4Float));


// 			tempFloat = GetVectorFrom(objectsToLoad.at(i).GetChildTag("Rotation_3Float").Text);

// 			temp4Float = XMFLOAT4(tempFloat.x, tempFloat.y, tempFloat.z, 1.0f);

// 			newObject->RotateObject(XMLoadFloat4(&temp4Float));


// 			tempFloat = GetVectorFrom(objectsToLoad.at(i).GetChildTag("Scale_3Float").Text);

// 			temp4Float = XMFLOAT4(tempFloat.x, tempFloat.y, tempFloat.z, 1.0f);

// 			newObject->ScaleObject(XMLoadFloat4(&temp4Float));
// 		}
// 		else if (objectType == "GoalObject")
// 		{
// 			GoalObject* newObject = new GoalObject();

// 			XMFLOAT3 tempFloat = GetVectorFrom(objectsToLoad.at(i).GetChildTag("Position_3Float").Text);

// 			XMFLOAT4 temp4Float = XMFLOAT4(tempFloat.x, tempFloat.y, tempFloat.z, 1.0f);

// 			newObject->TranslateObject(XMLoadFloat4(&temp4Float));

// 			newObject->Update(0.0f);
// 			tempFloat = GetVectorFrom(objectsToLoad.at(i).GetChildTag("Rotation_3Float").Text);

// 			temp4Float = XMFLOAT4(tempFloat.x, tempFloat.y, tempFloat.z, 1.0f);

// 			newObject->RotateObject(XMLoadFloat4(&temp4Float));
// 			newObject->Update(0.0f);


// 			tempFloat = GetVectorFrom(objectsToLoad.at(i).GetChildTag("Scale_3Float").Text);

// 			temp4Float = XMFLOAT4(tempFloat.x, tempFloat.y, tempFloat.z, 1.0f);

// 			newObject->ScaleObject(XMLoadFloat4(&temp4Float));
// 			newObject->Update(0.0f);


// 			newObject = nullptr;
// 		}
// 		else if (objectType == "WallObject")
// 		{
// 			WallObject* newObject = new WallObject();

// 			XMFLOAT3 tempFloat = GetVectorFrom(objectsToLoad.at(i).GetChildTag("Position_3Float").Text);

// 			XMFLOAT4 temp4Float = XMFLOAT4(tempFloat.x, tempFloat.y, tempFloat.z, 1.0f);

// 			newObject->TranslateObject(XMLoadFloat4(&temp4Float));


// 			tempFloat = GetVectorFrom(objectsToLoad.at(i).GetChildTag("Rotation_3Float").Text);

// 			temp4Float = XMFLOAT4(tempFloat.x, tempFloat.y, tempFloat.z, 1.0f);

// 			newObject->RotateObject(XMLoadFloat4(&temp4Float));


// 			tempFloat = GetVectorFrom(objectsToLoad.at(i).GetChildTag("Scale_3Float").Text);

// 			temp4Float = XMFLOAT4(tempFloat.x, tempFloat.y, tempFloat.z, 1.0f);

// 			newObject->ScaleObject(XMLoadFloat4(&temp4Float));
// 		}
// 		else if (objectType == "CurvedEdgeObject")
// 		{
// 			CurvedEdgeObject* newObject = new CurvedEdgeObject();

// 			XMFLOAT3 tempFloat = GetVectorFrom(objectsToLoad.at(i).GetChildTag("Position_3Float").Text);

// 			XMFLOAT4 temp4Float = XMFLOAT4(tempFloat.x, tempFloat.y, tempFloat.z, 1.0f);

// 			newObject->TranslateObject(XMLoadFloat4(&temp4Float));


// 			tempFloat = GetVectorFrom(objectsToLoad.at(i).GetChildTag("Rotation_3Float").Text);

// 			temp4Float = XMFLOAT4(tempFloat.x, tempFloat.y, tempFloat.z, 1.0f);

// 			newObject->RotateObject(XMLoadFloat4(&temp4Float));


// 			tempFloat = GetVectorFrom(objectsToLoad.at(i).GetChildTag("Scale_3Float").Text);

// 			temp4Float = XMFLOAT4(tempFloat.x, tempFloat.y, tempFloat.z, 1.0f);

// 			newObject->ScaleObject(XMLoadFloat4(&temp4Float));
// 		}
// 		else if (objectType == "PlaneObject")
// 		{
// 			PlaneObject* newObject = new PlaneObject();

// 			XMFLOAT3 tempFloat = GetVectorFrom(objectsToLoad.at(i).GetChildTag("Position_3Float").Text);

// 			XMFLOAT4 temp4Float = XMFLOAT4(tempFloat.x, tempFloat.y, tempFloat.z, 1.0f);

// 			newObject->TranslateObject(XMLoadFloat4(&temp4Float));


// 			tempFloat = GetVectorFrom(objectsToLoad.at(i).GetChildTag("Rotation_3Float").Text);

// 			temp4Float = XMFLOAT4(tempFloat.x, tempFloat.y, tempFloat.z, 1.0f);

// 			newObject->RotateObject(XMLoadFloat4(&temp4Float));


// 			tempFloat = GetVectorFrom(objectsToLoad.at(i).GetChildTag("Scale_3Float").Text);

// 			temp4Float = XMFLOAT4(tempFloat.x, tempFloat.y, tempFloat.z, 1.0f);

// 			newObject->ScaleObject(XMLoadFloat4(&temp4Float));
// 		}
// 		else if (objectType == "CrateObject")
// 		{
// 			CrateObject* newObject = new CrateObject("Crate");

// 			XMFLOAT3 tempFloat = GetVectorFrom(objectsToLoad.at(i).GetChildTag("Position_3Float").Text);

// 			XMFLOAT4 temp4Float = XMFLOAT4(tempFloat.x, tempFloat.y, tempFloat.z, 1.0f);

// 			newObject->TranslateObject(XMLoadFloat4(&temp4Float));


// 			tempFloat = GetVectorFrom(objectsToLoad.at(i).GetChildTag("Rotation_3Float").Text);

// 			temp4Float = XMFLOAT4(tempFloat.x, tempFloat.y, tempFloat.z, 1.0f);

// 			newObject->RotateObject(XMLoadFloat4(&temp4Float));


// 			tempFloat = GetVectorFrom(objectsToLoad.at(i).GetChildTag("Scale_3Float").Text);

// 			temp4Float = XMFLOAT4(tempFloat.x, tempFloat.y, tempFloat.z, 1.0f);

// 			newObject->ScaleObject(XMLoadFloat4(&temp4Float));
// 		}
// 		else if (objectType == "Billboard")
// 		{
// 			XMFLOAT3 tempFloat = GetVectorFrom(objectsToLoad.at(i).GetChildTag("Position_3Float").Text);

// 			XMFLOAT4 temp4Float = XMFLOAT4(tempFloat.x, tempFloat.y, tempFloat.z, 1.0f);

// 			std::string filePath = objectsToLoad.at(i).GetChildTag("Texture2D").Text;
// 			BillboardObject::GetInstance()->Initialize(_pd3dDevice);
// 			BillboardObject::GetInstance()->AddBillboard(tempFloat, new Texture2D(filePath));
			
// 		}
// 		else if (objectType == "GrassObject")
// 		{
// 			GrassObject* newObject = new GrassObject();

// 			XMFLOAT3 tempFloat = GetVectorFrom(objectsToLoad.at(i).GetChildTag("Position_3Float").Text);

// 			XMFLOAT4 temp4Float = XMFLOAT4(tempFloat.x, tempFloat.y, tempFloat.z, 1.0f);

// 			newObject->TranslateObject(XMLoadFloat4(&temp4Float));
// 			tempFloat = GetVectorFrom(objectsToLoad.at(i).GetChildTag("BoundsSize").Text);

// 			XMFLOAT3 bounds = tempFloat;

// 			newObject->SetBounds(XMFLOAT3(-(bounds.x/2), -(1 -bounds.y), -(bounds.z / 2)), XMFLOAT3((bounds.x / 2), bounds.y, (bounds.z / 2)));
// 			newObject->SetDensity(std::stof(objectsToLoad.at(i).GetChildTag("Density").Text));

// 		}
// 	}


// 	objectsToLoad = doc.GetTags("Light");

// 	for (int i = 0; i < objectsToLoad.size(); i++)
// 	{
// 		XML::Tag light = objectsToLoad.at(i).GetChildTag("DirectionalLight");

// 		if (light.tagIdentifier != "EMPTY")
// 		{

// 			if (DLight.size() < 8)
// 			{
// 				DirectionalLight newLight = DirectionalLight();
// 				XMFLOAT3 tempFloat = GetVectorFrom(objectsToLoad.at(i).GetChildTag("Ambient").Text);

// 				XMFLOAT4 temp4Float = XMFLOAT4(tempFloat.x, tempFloat.y, tempFloat.z, 1.0f);

// 				newLight.Ambient = temp4Float;

// 				tempFloat = GetVectorFrom(objectsToLoad.at(i).GetChildTag("Diffuse").Text);

// 				temp4Float = XMFLOAT4(tempFloat.x, tempFloat.y, tempFloat.z, 1.0f);

// 				newLight.Diffuse = temp4Float;
			
// 				tempFloat = GetVectorFrom(objectsToLoad.at(i).GetChildTag("Specular").Text);

// 				temp4Float = XMFLOAT4(tempFloat.x, tempFloat.y, tempFloat.z, 0.5f);

// 				newLight.Specular = temp4Float;
			
// 				tempFloat = GetVectorFrom(objectsToLoad.at(i).GetChildTag("Direction").Text);

// 				newLight.Direction = tempFloat;

// 				newLight.Intensity = std::stof(objectsToLoad.at(i).GetChildTag("Intensity").Text);

// 				DLight.push_back(newLight);
// 			}
// 		}

// 		light = objectsToLoad.at(i).GetChildTag("PointLight");

// 		if (light.tagIdentifier != "EMPTY")
// 		{
// 			if (PLight.size() < 8)
// 			{
// 				PointLight newLight = PointLight();

// 				XMFLOAT3 tempFloat = GetVectorFrom(objectsToLoad.at(i).GetChildTag("Ambient").Text);

// 				XMFLOAT4 temp4Float = XMFLOAT4(tempFloat.x, tempFloat.y, tempFloat.z, 1.0f);

// 				newLight.Ambient = temp4Float;

// 				tempFloat = GetVectorFrom(objectsToLoad.at(i).GetChildTag("Diffuse").Text);

// 				temp4Float = XMFLOAT4(tempFloat.x, tempFloat.y, tempFloat.z, 1.0f);

// 				newLight.Diffuse = temp4Float;

// 				tempFloat = GetVectorFrom(objectsToLoad.at(i).GetChildTag("Specular").Text);

// 				temp4Float = XMFLOAT4(tempFloat.x, tempFloat.y, tempFloat.z, 1.0f);

// 				newLight.Specular = temp4Float;

// 				tempFloat = GetVectorFrom(objectsToLoad.at(i).GetChildTag("Position").Text);

// 				newLight.Position = tempFloat;

// 				tempFloat = GetVectorFrom(objectsToLoad.at(i).GetChildTag("Attenuation").Text);

// 				newLight.Attenuation = tempFloat;

// 				newLight.Range = std::stof(objectsToLoad.at(i).GetChildTag("Range").Text);

// 				newLight.Intensity = std::stof(objectsToLoad.at(i).GetChildTag("Intensity").Text);


// 				PLight.push_back(newLight);
// 			}
// 		}
		
// 		light = objectsToLoad.at(i).GetChildTag("SpotLight");

// 		if (light.tagIdentifier != "EMPTY")
// 		{
// 			if (SLight.size() < 8)
// 			{
// 				SpotLight newLight = SpotLight();

// 				XMFLOAT3 tempFloat = GetVectorFrom(objectsToLoad.at(i).GetChildTag("Ambient").Text);

// 				XMFLOAT4 temp4Float = XMFLOAT4(tempFloat.x, tempFloat.y, tempFloat.z, 1.0f);

// 				newLight.Ambient = temp4Float;

// 				tempFloat = GetVectorFrom(objectsToLoad.at(i).GetChildTag("Diffuse").Text);

// 				temp4Float = XMFLOAT4(tempFloat.x, tempFloat.y, tempFloat.z, 1.0f);

// 				newLight.Diffuse = temp4Float;

// 				tempFloat = GetVectorFrom(objectsToLoad.at(i).GetChildTag("Specular").Text);

// 				temp4Float = XMFLOAT4(tempFloat.x, tempFloat.y, tempFloat.z, 1.0f);

// 				newLight.Specular = temp4Float;

// 				tempFloat = GetVectorFrom(objectsToLoad.at(i).GetChildTag("Position").Text);

// 				newLight.Position = tempFloat;

// 				tempFloat = GetVectorFrom(objectsToLoad.at(i).GetChildTag("Attenuation").Text);

// 				newLight.Attenuation = tempFloat;

// 				newLight.Range = std::stof(objectsToLoad.at(i).GetChildTag("Range").Text);

// 				tempFloat = GetVectorFrom(objectsToLoad.at(i).GetChildTag("Direction").Text);

// 				newLight.Direction = tempFloat;

// 				newLight.Spot = std::stof(objectsToLoad.at(i).GetChildTag("Spot").Text);

// 				newLight.Intensity = std::stof(objectsToLoad.at(i).GetChildTag("Intensity").Text);



// 				SLight.push_back(newLight);
// 			}

// 		}
// 	}

// 	mSceneBoundingSphere.Center = XMFLOAT3(0.0f, 0.0f, 0.0f);
// 	mSceneBoundingSphere.Radius = 2800.0f;
// }

void Application::Release()
{
	Cleanup();
}

HRESULT Application::Initialise(HINSTANCE hInstance, int nCmdShow)
{
	//Load system preferances
	if (
		FAILED(Window::GetInstance().Initialise()) ||
		FAILED(Graphics::GetInstance().Initialise()))
	{
		Cleanup();

		return E_FAIL;
	}
	DirectoryService::GetInstance().Initialise();
	SceneManager::GetInstance().Initialise();
	ResourceManager::GetInstance().Initialise();
	return S_OK;
}

// HRESULT Application::InitShadersAndInputLayout()
// {
// 	HRESULT hr;

// 	ID3DInclude* IncludeHandle;


// 	// Compile the vertex shader
// 	ID3DBlob* pVSBlob = nullptr;
// 	ID3DBlob* pPSBlob = nullptr;

// 	_baseShader = new Shader(L"DX11 Framework.fx", "VS", "PS", "vs_4_0", "ps_4_0", _pd3dDevice, &pVSBlob, &pPSBlob);

// 	// Define the input layout
// 	D3D11_INPUT_ELEMENT_DESC layout[] =
// 	{
// 		{ "POSITION",	0,	DXGI_FORMAT_R32G32B32_FLOAT,	0,	0,	D3D11_INPUT_PER_VERTEX_DATA,	0 },
// 		{ "TEXCOORD",	0,	DXGI_FORMAT_R32G32_FLOAT,		0,	12,	D3D11_INPUT_PER_VERTEX_DATA,	0 },
// 		{ "NORMAL",		0,	DXGI_FORMAT_R32G32B32A32_FLOAT,	0,	20,	D3D11_INPUT_PER_VERTEX_DATA,	0 },
// 		{ "TANGENT",	0,	DXGI_FORMAT_R32G32B32_FLOAT,	0,	36,	D3D11_INPUT_PER_VERTEX_DATA,	0 },
// 	};

// 	UINT numElements = ARRAYSIZE(layout);

// 	// Create the input layout
// 	hr = _pd3dDevice->CreateInputLayout(layout, numElements, pVSBlob->GetBufferPointer(),
// 		pVSBlob->GetBufferSize(), &_pVertexLayout);

// 	pVSBlob->Release();

// 	if (FAILED(hr))
// 		return hr;

// 	// Set the input layout
// 	_pImmediateContext->IASetInputLayout(_pVertexLayout);

// 	//Special Effects
// 	_blurShader = new Shader(L"Blur.fx", "VS", "PS", "vs_4_0", "ps_4_0", _pd3dDevice, &pVSBlob, &pPSBlob);

// 	// Define the input layout
// 	D3D11_INPUT_ELEMENT_DESC SpFxlayout[] =
// 	{
// 		{ "POSITION",	0,	DXGI_FORMAT_R32G32_FLOAT,	0,	0,	D3D11_INPUT_PER_VERTEX_DATA,	0 },
// 		{ "TEXCOORD",	0,	DXGI_FORMAT_R32G32_FLOAT,		0,	8,	D3D11_INPUT_PER_VERTEX_DATA,	0 },
// 	};

// 	numElements = ARRAYSIZE(SpFxlayout);

// 	// Create the input layout
// 	hr = _pd3dDevice->CreateInputLayout(SpFxlayout, numElements, pVSBlob->GetBufferPointer(),
// 		pVSBlob->GetBufferSize(), &_pScreenVertexLayout);
// 	pVSBlob->Release();

// 	if (FAILED(hr))
// 		return hr;


// 	//Brightness Map Shader
// 	_brightnessMapShader = new Shader(L"BrightnessMapping.fx", "VS", "PS", "vs_4_0", "ps_4_0", _pd3dDevice, &pVSBlob, &pPSBlob);

// 	//Bloom Shader
// 	_bloomShader = new Shader(L"Bloom.fx", "VS", "PS", "vs_4_0", "ps_4_0", _pd3dDevice, &pVSBlob, &pPSBlob);

// 	_renderScene = new Shader(L"RenderToScene.fx", "VS", "PS", "vs_4_0", "ps_4_0", _pd3dDevice, &pVSBlob, &pPSBlob);

// 	//SKYMAP = new Shader(L"skyMap.fx", "VS", "PS", "vs_4_0", "ps_4_0", _pd3dDevice, &SKYMAP_VS_Buffer, &SKYMAP_PS_Buffer);



// 	return hr;
// }

// HRESULT Application::InitVertexBuffer()
// {
// 	HRESULT hr;

// 	D3D11_BUFFER_DESC bd;


// 	D3D11_SUBRESOURCE_DATA InitData;


// 	ScreenVertex sfxPlaneVerts[] =
// 	{	//Pos								//Tex				
// 		{ XMFLOAT2(-1.0f, 1.0f),		XMFLOAT2(0.0f,0.0f)},
// 		{ XMFLOAT2(1.0f, 1.0f ),	XMFLOAT2(1.0f,0.0f)},
// 		{ XMFLOAT2(-1.0f,-1.0f),		XMFLOAT2(0.0f,1.0f)},
// 		{ XMFLOAT2(1.0f,-1.0f ),	XMFLOAT2(1.0f,1.0f)},
// 	};

// 	D3D11_BUFFER_DESC sfxbd;
// 	ZeroMemory(&sfxbd, sizeof(sfxbd));
// 	sfxbd.Usage = D3D11_USAGE_DEFAULT;
// 	sfxbd.ByteWidth = sizeof(ScreenVertex) * 4;
// 	sfxbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
// 	sfxbd.CPUAccessFlags = 0;

// 	D3D11_SUBRESOURCE_DATA sfxInitData;
// 	ZeroMemory(&sfxInitData, sizeof(sfxInitData));
// 	sfxInitData.pSysMem = sfxPlaneVerts;

// 	hr = _pd3dDevice->CreateBuffer(&sfxbd, &sfxInitData, &_pScreenVertexBuffer);

// 	if (FAILED(hr))
// 		return hr;

// 	return S_OK;
// }

// HRESULT Application::InitIndexBuffer()
// {
// 	HRESULT hr;

// 	D3D11_BUFFER_DESC bd;


// 	D3D11_SUBRESOURCE_DATA InitData;

// 	WORD sfxPlane[] =
// 	{
// 		0,1,2,
// 		2,1,3,
// 	};

// 	ZeroMemory(&bd, sizeof(bd));

// 	bd.Usage = D3D11_USAGE_DEFAULT;
// 	bd.ByteWidth = sizeof(int) * 6;
// 	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;

// 	ZeroMemory(&InitData, sizeof(InitData));
// 	InitData.pSysMem = sfxPlane;
// 	hr = _pd3dDevice->CreateBuffer(&bd, &InitData, &_pScreenIndexBuffer);

// 	if (FAILED(hr))
// 		return hr;

// 	return S_OK;
// }

// void Application::BuildShadowTransform()
// {
// 	XMVECTOR lightDirection = XMLoadFloat3(&DLight[0].Direction);
// 	XMVECTOR lightPosition = -2.0f*mSceneBoundingSphere.Radius*lightDirection;
// 	XMVECTOR targetPos = XMLoadFloat3(&mSceneBoundingSphere.Center);
// 	XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

// 	XMMATRIX V = XMMatrixLookAtLH(lightPosition, targetPos, up);

// 	//Transform bounding sphere to light space
// 	XMFLOAT3 sphereCenterLS;
// 	XMStoreFloat3(&sphereCenterLS, XMVector3TransformCoord(targetPos, V));

// 	//Ortho frustum in light space encloses scene

// 	float l = sphereCenterLS.x - mSceneBoundingSphere.Radius;
// 	float b = sphereCenterLS.y - mSceneBoundingSphere.Radius;
// 	float n = sphereCenterLS.z - mSceneBoundingSphere.Radius;

// 	float r = sphereCenterLS.x + mSceneBoundingSphere.Radius;
// 	float t = sphereCenterLS.y + mSceneBoundingSphere.Radius;
// 	float f = sphereCenterLS.z + mSceneBoundingSphere.Radius;

// 	XMMATRIX P = XMMatrixOrthographicOffCenterLH(l, r, b, t, n, f);

// 	//Transform NDC space [-1,+1]^2 to texture space [0,1]^2
// 	XMMATRIX T(
// 		0.5f, 0.0f, 0.0f, 0.0f,
// 		0.0f, -0.5f, 0.0f, 0.0f,
// 		0.0f, 0.0f, 1.0f, 0.0f,
// 		0.5f, 0.5f, 0.0f, 1.0f);

// 	XMMATRIX S = V * P *T;

// 	XMStoreFloat4x4(&mLightView, V);
// 	XMStoreFloat4x4(&mLightProj, P);
// 	XMStoreFloat4x4(&mShadowMapTransform, S);


// }


// HRESULT Application::CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
// {
// 	HRESULT hr = S_OK;

// 	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
// #if defined(DEBUG) || defined(_DEBUG)
// 	// Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
// 	// Setting this flag improves the shader debugging experience, but still allows 
// 	// the shaders to be optimized and to run exactly the way they will run in 
// 	// the release configuration of this program.
// 	dwShaderFlags |= D3DCOMPILE_DEBUG;
// #endif

// 	ID3DBlob* pErrorBlob;
// 	hr = D3DCompileFromFile(szFileName, nullptr, nullptr, szEntryPoint, szShaderModel,
// 		dwShaderFlags, 0, ppBlobOut, &pErrorBlob);

// 	if (FAILED(hr))
// 	{
// 		if (pErrorBlob != nullptr)
// 			OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());

// 		if (pErrorBlob) pErrorBlob->Release();

// 		return hr;
// 	}

// 	if (pErrorBlob) pErrorBlob->Release();

// 	return S_OK;
// }

 //HRESULT Application::InitDevice()
 //{
 //	HRESULT hr = S_OK;

 //	UINT createDeviceFlags = 0;

 //#ifdef _DEBUG
 //	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
 //#endif

 //	D3D_DRIVER_TYPE driverTypes[] =
 //	{
 //		D3D_DRIVER_TYPE_HARDWARE,
 //		D3D_DRIVER_TYPE_WARP,
 //		D3D_DRIVER_TYPE_REFERENCE,
 //	};

 //	UINT numDriverTypes = ARRAYSIZE(driverTypes);

 //	D3D_FEATURE_LEVEL featureLevels[] =
 //	{
 //		D3D_FEATURE_LEVEL_11_0,
 //		D3D_FEATURE_LEVEL_10_1,
 //		D3D_FEATURE_LEVEL_10_0,
 //	};

 //	UINT numFeatureLevels = ARRAYSIZE(featureLevels);

 //	DXGI_SWAP_CHAIN_DESC sd;
 //	ZeroMemory(&sd, sizeof(sd));
 //	sd.BufferCount = 1;
 //	sd.BufferDesc.Width = _WindowWidth;
 //	sd.BufferDesc.Height = _WindowHeight;
 //	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
 //	sd.BufferDesc.RefreshRate.Numerator = 60;
 //	sd.BufferDesc.RefreshRate.Denominator = 1;
 //	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
 //	sd.OutputWindow = _hWnd;
 //	sd.SampleDesc.Count = 1;
 //	sd.SampleDesc.Quality = 0;
 //	sd.Windowed = TRUE;

 //	for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
 //	{
 //		_driverType = driverTypes[driverTypeIndex];
 //		hr = D3D11CreateDeviceAndSwapChain(nullptr, _driverType, nullptr, createDeviceFlags, featureLevels, numFeatureLevels,
 //			D3D11_SDK_VERSION, &sd, &_pSwapChain, &_pd3dDevice, &_featureLevel, &_pImmediateContext);
 //		if (SUCCEEDED(hr))
 //			break;
 //	}

 //	if (FAILED(hr))
 //		return hr;

 //	ID3D11Texture2D* pBackBuffer = nullptr;

 //	// Create a render target view
 //	hr = _pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

 //	if (FAILED(hr))
 //		return hr;


 //	hr = _pd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &_pRenderTargetView);

 //	pBackBuffer->Release();

 //	if (FAILED(hr))
 //		return hr;

 //	D3D11_TEXTURE2D_DESC depthStencilDesc;

 //	depthStencilDesc.Width = _WindowWidth;
 //	depthStencilDesc.Height = _WindowHeight;
 //	depthStencilDesc.MipLevels = 1;
 //	depthStencilDesc.ArraySize = 1;
 //	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
 //	depthStencilDesc.SampleDesc.Count = 1;
 //	depthStencilDesc.SampleDesc.Quality = 0;
 //	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
 //	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
 //	depthStencilDesc.CPUAccessFlags = 0;
 //	depthStencilDesc.MiscFlags = 0;

 //	_pd3dDevice->CreateTexture2D(&depthStencilDesc, nullptr, &_depthStencilBuffer);
 //	_pd3dDevice->CreateDepthStencilView(_depthStencilBuffer, nullptr, &_depthStencilView);

 //	_pImmediateContext->OMSetRenderTargets(1, &_pRenderTargetView, _depthStencilView);

 //	// Setup the viewport
 //	vp.Width = (FLOAT)_WindowWidth;
 //	vp.Height = (FLOAT)_WindowHeight;
 //	vp.MinDepth = 0.0f;
 //	vp.MaxDepth = 1.0f;
 //	vp.TopLeftX = 0;
 //	vp.TopLeftY = 0;
 //	_pImmediateContext->RSSetViewports(1, &vp);

 //	InitShadersAndInputLayout();

 //	InitVertexBuffer();
 //	InitIndexBuffer();


 //	// Create the constant buffer
 //	D3D11_BUFFER_DESC bd;
 //	ZeroMemory(&bd, sizeof(bd));
 //	bd.Usage = D3D11_USAGE_DEFAULT;
 //	bd.ByteWidth = sizeof(CBFrame);
 //	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
 //	bd.CPUAccessFlags = 0;
 //	hr = _pd3dDevice->CreateBuffer(&bd, nullptr, &_pCBFrame);

 //	if (FAILED(hr))
 //		return hr;

 //	// Create the Special Effect constant buffer
 //	ZeroMemory(&bd, sizeof(bd));
 //	bd.Usage = D3D11_USAGE_DEFAULT;
 //	bd.ByteWidth = sizeof(ConstantBufferSFX);
 //	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
 //	bd.CPUAccessFlags = 0;
 //	hr = _pd3dDevice->CreateBuffer(&bd, nullptr, &_pConstantBufferSFX);

 //	if (FAILED(hr))
 //		return hr;

 //	// Create the constant buffer per frame
 //	D3D11_BUFFER_DESC bd1;
 //	ZeroMemory(&bd1, sizeof(bd1));
 //	bd1.Usage = D3D11_USAGE_DEFAULT;
 //	bd1.ByteWidth = sizeof(CBObject);
 //	bd1.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
 //	bd1.CPUAccessFlags = 0;
 //	bd1.MiscFlags = 0;
 //	hr = _pd3dDevice->CreateBuffer(&bd1, nullptr, &_pCBObject);

 //	if (FAILED(hr))
 //		return hr;

 //	// Create the constant buffer per frame
 //	D3D11_BUFFER_DESC bd2;
 //	ZeroMemory(&bd2, sizeof(bd2));
 //	bd2.Usage = D3D11_USAGE_DEFAULT;
 //	bd2.ByteWidth = sizeof(ConstantBufferBrightnessMapping);
 //	bd2.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
 //	bd2.CPUAccessFlags = 0;
 //	bd2.MiscFlags = 0;
 //	hr = _pd3dDevice->CreateBuffer(&bd2, nullptr, &_pConstantBufferBrightnessMap);
 //	if (FAILED(hr))
 //		return hr;

 //	D3D11_RASTERIZER_DESC wfdesc;
 //	ZeroMemory(&wfdesc, sizeof(D3D11_RASTERIZER_DESC));
 //	wfdesc.FillMode = D3D11_FILL_WIREFRAME;
 //	wfdesc.CullMode = D3D11_CULL_NONE;
 //	hr = _pd3dDevice->CreateRasterizerState(&wfdesc, &_wireFrame);




 //	if (FAILED(hr))
 //		return hr;

 //	//Special Effect Initalizeation
 //	D3D11_TEXTURE2D_DESC texDesc;
 //	D3D11_RENDER_TARGET_VIEW_DESC RenTargetDesc;
 //	D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceDesc;

 //	//Creating Texture for special effects
	//
 //	texDesc.Width = _WindowWidth;
 //	texDesc.Height = _WindowHeight;
 //	texDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
 //	texDesc.MipLevels = 0;
 //	texDesc.SampleDesc.Count = 1;
 //	texDesc.SampleDesc.Quality = 0;
 //	texDesc.ArraySize = 1;
 //	texDesc.CPUAccessFlags = 0;
 //	texDesc.MiscFlags = 0;
 //	texDesc.Usage = D3D11_USAGE_DEFAULT;
 //	texDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;

 // 	hr = _pd3dDevice->CreateTexture2D(&texDesc, nullptr, &_blurTexture);

 //	if (FAILED(hr))
 //	{
 //		return hr;
 //	}
 //	//Creating RenderTarget
 //	RenTargetDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
 //	RenTargetDesc.Format = texDesc.Format;
 //	RenTargetDesc.Texture2D.MipSlice = 0;

 //	_pd3dDevice->CreateRenderTargetView(_blurTexture, &RenTargetDesc, &_pBlurTargetView);

 //	//Creating Shader Resource View
 //	shaderResourceDesc.Format = texDesc.Format;
 //	shaderResourceDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
 //	shaderResourceDesc.Texture2D.MipLevels = 1;
 //	shaderResourceDesc.Texture2D.MostDetailedMip = 0;

 //	_pd3dDevice->CreateShaderResourceView(_blurTexture, &shaderResourceDesc, &_pBlurResourceView);

 //	//BrightnessMap Initalizeation


 //	//Creating Texture for BrightnessMap

 //	texDesc.Width = _WindowWidth;
 //	texDesc.Height = _WindowHeight;
 //	texDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
 //	texDesc.MipLevels = 0;
 //	texDesc.SampleDesc.Count = 1;
 //	texDesc.SampleDesc.Quality = 0;
 //	texDesc.ArraySize = 1;
 //	texDesc.CPUAccessFlags = 0;
 //	texDesc.MiscFlags = 0;
 //	texDesc.Usage = D3D11_USAGE_DEFAULT;
 //	texDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;

 //	hr = _pd3dDevice->CreateTexture2D(&texDesc, nullptr, &_brightnessMapTexture);

 //	if (FAILED(hr))
 //	{
 //		return hr;
 //	}
 //	//Creating RenderTarget
 //	RenTargetDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
 //	RenTargetDesc.Format = texDesc.Format;
 //	RenTargetDesc.Texture2D.MipSlice = 0;

 //	_pd3dDevice->CreateRenderTargetView(_brightnessMapTexture, &RenTargetDesc, &_pBrightnessMapTargetView);

 //	//Creating Shader Resource View
 //	shaderResourceDesc.Format = texDesc.Format;
 //	shaderResourceDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
 //	shaderResourceDesc.Texture2D.MipLevels = 1;
 //	shaderResourceDesc.Texture2D.MostDetailedMip = 0;

 //	_pd3dDevice->CreateShaderResourceView(_brightnessMapTexture, &shaderResourceDesc, &_pBrightnessMapResourceView);

 //	//Creating Texture for FinalRender

 //	texDesc.Width = _WindowWidth;
 //	texDesc.Height = _WindowHeight;
 //	texDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
 //	texDesc.MipLevels = 0;
 //	texDesc.SampleDesc.Count = 1;
 //	texDesc.SampleDesc.Quality = 0;
 //	texDesc.ArraySize = 1;
 //	texDesc.CPUAccessFlags = 0;
 //	texDesc.MiscFlags = 0;
 //	texDesc.Usage = D3D11_USAGE_DEFAULT;
 //	texDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;

 //	hr = _pd3dDevice->CreateTexture2D(&texDesc, nullptr, &_finalRenderTexture);

 //	if (FAILED(hr))
 //	{
 //		return hr;
 //	}
 //	//Creating RenderTarget
 //	RenTargetDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
 //	RenTargetDesc.Format = texDesc.Format;
 //	RenTargetDesc.Texture2D.MipSlice = 0;

 //	_pd3dDevice->CreateRenderTargetView(_finalRenderTexture, &RenTargetDesc, &_pFinalRenderTargetView);

 //	//Creating Shader Resource View
 //	shaderResourceDesc.Format = texDesc.Format;
 //	shaderResourceDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
 //	shaderResourceDesc.Texture2D.MipLevels = 1;
 //	shaderResourceDesc.Texture2D.MostDetailedMip = 0;

 //	_pd3dDevice->CreateShaderResourceView(_finalRenderTexture, &shaderResourceDesc, &_pFinalRenderResourceView);

 //	//Creating Texture for SceneRender

 //	texDesc.Width = _WindowWidth;
 //	texDesc.Height = _WindowHeight;
 //	texDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
 //	texDesc.MipLevels = 0;
 //	texDesc.SampleDesc.Count = 1;
 //	texDesc.SampleDesc.Quality = 0;
 //	texDesc.ArraySize = 1;
 //	texDesc.CPUAccessFlags = 0;
 //	texDesc.MiscFlags = 0;
 //	texDesc.Usage = D3D11_USAGE_DEFAULT;
 //	texDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;

 //	hr = _pd3dDevice->CreateTexture2D(&texDesc, nullptr, &_sceneRender);

 //	if (FAILED(hr))
 //	{
 //		return hr;
 //	}
 //	//Creating RenderTarget
 //	RenTargetDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
 //	RenTargetDesc.Format = texDesc.Format;
 //	RenTargetDesc.Texture2D.MipSlice = 0;

 //	_pd3dDevice->CreateRenderTargetView(_sceneRender, &RenTargetDesc, &_pSceneTargetView);

 //	//Creating Shader Resource View
 //	shaderResourceDesc.Format = texDesc.Format;
 //	shaderResourceDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
 //	shaderResourceDesc.Texture2D.MipLevels = 1;
 //	shaderResourceDesc.Texture2D.MostDetailedMip = 0;

 //	_pd3dDevice->CreateShaderResourceView(_sceneRender, &shaderResourceDesc, &_pSceneResourceView);

 //	//Creating Texture for Bloom

 //	texDesc.Width = _WindowWidth;
 //	texDesc.Height = _WindowHeight;
 //	texDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
 //	texDesc.MipLevels = 0;
 //	texDesc.SampleDesc.Count = 1;
 //	texDesc.SampleDesc.Quality = 0;
 //	texDesc.ArraySize = 1;
 //	texDesc.CPUAccessFlags = 0;
 //	texDesc.MiscFlags = 0;
 //	texDesc.Usage = D3D11_USAGE_DEFAULT;
 //	texDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;

 //	hr = _pd3dDevice->CreateTexture2D(&texDesc, nullptr, &_bloomTexture);

 //	if (FAILED(hr))
 //	{
 //		return hr;
 //	}
 //	//Creating RenderTarget
 //	RenTargetDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
 //	RenTargetDesc.Format = texDesc.Format;
 //	RenTargetDesc.Texture2D.MipSlice = 0;

 //	_pd3dDevice->CreateRenderTargetView(_bloomTexture, &RenTargetDesc, &_pBloomTargetView);

 //	//Creating Shader Resource View
 //	shaderResourceDesc.Format = texDesc.Format;
 //	shaderResourceDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
 //	shaderResourceDesc.Texture2D.MipLevels = 1;
 //	shaderResourceDesc.Texture2D.MostDetailedMip = 0;

 //	_pd3dDevice->CreateShaderResourceView(_bloomTexture, &shaderResourceDesc, &_pBloomResourceView);

 //	//Creating Texture for shaderoutput

 //	texDesc.Width = _WindowWidth;
 //	texDesc.Height = _WindowHeight;
 //	texDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
 //	texDesc.MipLevels = 0;
 //	texDesc.SampleDesc.Count = 1;
 //	texDesc.SampleDesc.Quality = 0;
 //	texDesc.ArraySize = 1;
 //	texDesc.CPUAccessFlags = 0;
 //	texDesc.MiscFlags = 0;
 //	texDesc.Usage = D3D11_USAGE_DEFAULT;
 //	texDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;

 //	hr = _pd3dDevice->CreateTexture2D(&texDesc, nullptr, &_shaderOutput);

 //	if (FAILED(hr))
 //	{
 //		return hr;
 //	}

 //	//Creating Shader Resource View
 //	shaderResourceDesc.Format = texDesc.Format;
 //	shaderResourceDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
 //	shaderResourceDesc.Texture2D.MipLevels = 1;
 //	shaderResourceDesc.Texture2D.MostDetailedMip = 0;

 //	_pd3dDevice->CreateShaderResourceView(_shaderOutput, &shaderResourceDesc, &_pShaderOutputResourceView);


 //	Texture2D::SetReferances(_pd3dDevice, _pImmediateContext);
 //	MaterialLibaryLoader::GetInstance(_pd3dDevice, _pImmediateContext);
 //	ObjLoader::GetInstance(_pd3dDevice);

 //	D3D11_SAMPLER_DESC sdesc;
 //	sdesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
 //	sdesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
 //	sdesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
 //	sdesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
 //	sdesc.MipLODBias = 0;
 //	sdesc.MaxAnisotropy = 1;
 //	sdesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
 //	sdesc.BorderColor[4] = { 0.0f };
 //	sdesc.MinLOD = 0;
 //	sdesc.MaxLOD = 0;

 //	hr = _pd3dDevice->CreateSamplerState(&sdesc, &Sampler);
 //	if (FAILED(hr))
 //		return hr;

	//
 //	_pImmediateContext->PSSetSamplers(0, 1, &Sampler);
	//
	//

 //	sdesc;
 //	sdesc.Filter = D3D11_FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT;
 //	sdesc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
 //	sdesc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
 //	sdesc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
 //	sdesc.MipLODBias = 0;
 //	sdesc.MaxAnisotropy = 1;
 //	sdesc.ComparisonFunc = D3D11_COMPARISON_LESS_EQUAL;
 //	sdesc.BorderColor[4] = { 0.0f };
 //	sdesc.MinLOD = 0;
 //	sdesc.MaxLOD = 0;

 //	hr = _pd3dDevice->CreateSamplerState(&sdesc, &shadow);
 //	if (FAILED(hr))
 //		return hr;


 //	_pImmediateContext->PSSetSamplers(1, 1, &shadow);


 //	sfxcb.ScreenSize = XMFLOAT2((float)_WindowWidth, (float)_WindowHeight);



 //	D3D11_BLEND_DESC blendDesc;
 //	ZeroMemory(&blendDesc, sizeof(blendDesc));

 //	D3D11_RENDER_TARGET_BLEND_DESC rtbd;
 //	ZeroMemory(&rtbd, sizeof(rtbd));

 //	rtbd.BlendEnable = true;
 //	rtbd.SrcBlend = D3D11_BLEND_SRC_COLOR;
 //	rtbd.DestBlend = D3D11_BLEND_BLEND_FACTOR;
 //	rtbd.BlendOp = D3D11_BLEND_OP_ADD;
 //	rtbd.SrcBlendAlpha = D3D11_BLEND_ONE;
 //	rtbd.DestBlendAlpha = D3D11_BLEND_ZERO;
 //	rtbd.BlendOpAlpha = D3D11_BLEND_OP_ADD;
 //	rtbd.RenderTargetWriteMask = D3D10_COLOR_WRITE_ENABLE_ALL;

 //	blendDesc.AlphaToCoverageEnable = false;
 //	blendDesc.RenderTarget[0] = rtbd;

 //	_pd3dDevice->CreateBlendState(&blendDesc, &Transparency);

 //	BuildScene("Build.xml");

 //	SkyMapObject* skymap = new SkyMapObject("SkyMap");

 //	BillboardObject::GetInstance();
 //	List<SceneObject>* temp;
 //	temp = SceneObject::ObjectList;

 //	mSmap = new ShadowMap(_pd3dDevice, SMapSize, SMapSize);

 //	for (int i = 0; i < SceneObject::ObjectCount; i++)
 //	{
 //		temp->val->Initialize(_pd3dDevice);
 //		temp = temp->next;
 //	}




 //	return S_OK;
 //}

void Application::Cleanup()
{
// 	// Clear Contex
// 	if (_pImmediateContext) _pImmediateContext->ClearState();

// 	//Constant Buffers
// 	if (_pCBFrame) _pCBFrame->Release();
// 	if (_pConstantBufferSFX) _pConstantBufferSFX->Release();
// 	if (_pCBObject) _pCBObject->Release();
// 	if (_pConstantBufferBrightnessMap) _pConstantBufferBrightnessMap->Release();

// 	// VertexBuffers
// 	if (_pScreenVertexBuffer)				_pScreenVertexBuffer->Release();


// 	// Index Buffers
// 	if (_pScreenIndexBuffer)				_pScreenIndexBuffer->Release();

// 	// Layouts
// 	if (_pVertexLayout)						_pVertexLayout->Release();
// 	if (_pScreenVertexLayout)				_pScreenVertexLayout->Release();

// 	// Shaders
// 	if (_baseShader)						_baseShader->Release();
// 	if (_blurShader)						_blurShader->Release();
// 	if (_bloomShader)						_bloomShader->Release();
// 	if (_brightnessMapShader)				_brightnessMapShader->Release();

// 	// Stencils
// 	if (_depthStencilView)					_depthStencilView->Release();
// 	if (_depthStencilBuffer)				_depthStencilBuffer->Release();

// 	// RTV
// 	if (_pRenderTargetView)					_pRenderTargetView->Release();
// 	if (_pBlurTargetView)					_pBlurTargetView->Release();
// 	if (_pBrightnessMapTargetView)			_pBrightnessMapTargetView->Release();
// 	if (_pSceneTargetView)					_pSceneTargetView->Release();

// 	// Rastarizer State
// 	if (_wireFrame) _wireFrame->Release();
	
// 	// SRV
// 	if (_pBlurResourceView) _pBlurResourceView->Release();
// 	if (_pBrightnessMapResourceView) _pBrightnessMapResourceView->Release();
// 	if (_pSceneResourceView) _pSceneResourceView->Release();

// 	// Samplers
// 	if (Sampler) Sampler->Release();

// 	// Textures
// 	if (_blurTexture) _blurTexture->Release();
// 	if (_brightnessMapTexture) _brightnessMapTexture->Release();
// 	if (_sceneRender) _sceneRender->Release();

// 	//Misc
// 	if (_pSwapChain) _pSwapChain->Release();

// 	if (_pImmediateContext) _pImmediateContext->Release();

// 	if (_pd3dDevice) _pd3dDevice->Release();

	Graphics::GetInstance().Release();
	Window::GetInstance().Release();

	SceneManager::GetInstance().Release();
	ResourceManager::GetInstance().Release();
}

void Application::Update()
{
	

	// // Initialize the projection matrix
	// //XMStoreFloat4x4(&_projection, XMMatrixPerspectiveFovLH(XM_PIDIV2, _WindowWidth / (FLOAT)_WindowHeight, 0.01f, 100.0f));

	// RECT rc;
	// GetClientRect(_hWnd, &rc);
	// _WindowWidth = rc.right - rc.left;
	// _WindowHeight = rc.bottom - rc.top;

	// D3D11_TEXTURE2D_DESC texDesc;
	// D3D11_RENDER_TARGET_VIEW_DESC RenTargetDesc;
	// D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceDesc;
	// _shaderOutput->Release();
	// _pBloomResourceView->Release();
	// _pBloomTargetView->Release();

	// texDesc.Width = _WindowWidth;
	// texDesc.Height = _WindowHeight;
	// texDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	// texDesc.MipLevels = 0;
	// texDesc.SampleDesc.Count = 1;
	// texDesc.SampleDesc.Quality = 0;
	// texDesc.ArraySize = 1;
	// texDesc.CPUAccessFlags = 0;
	// texDesc.MiscFlags = 0;
	// texDesc.Usage = D3D11_USAGE_DEFAULT;
	// texDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;

	// //Creating RenderTarget
	// RenTargetDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	// RenTargetDesc.Format = texDesc.Format;
	// RenTargetDesc.Texture2D.MipSlice = 0;

	// _pd3dDevice->CreateRenderTargetView(_bloomTexture, &RenTargetDesc, &_pBloomTargetView);

	// //Creating Shader Resource View
	// shaderResourceDesc.Format = texDesc.Format;
	// shaderResourceDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	// shaderResourceDesc.Texture2D.MipLevels = 1;
	// shaderResourceDesc.Texture2D.MostDetailedMip = 0;

	// _pd3dDevice->CreateShaderResourceView(_bloomTexture, &shaderResourceDesc, &_pBloomResourceView);

	// //Creating Texture for shaderoutput

	// texDesc.Width = _WindowWidth;
	// texDesc.Height = _WindowHeight;
	// texDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	// texDesc.MipLevels = 0;
	// texDesc.SampleDesc.Count = 1;
	// texDesc.SampleDesc.Quality = 0;
	// texDesc.ArraySize = 1;
	// texDesc.CPUAccessFlags = 0;
	// texDesc.MiscFlags = 0;
	// texDesc.Usage = D3D11_USAGE_DEFAULT;
	// texDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;

	// _pd3dDevice->CreateTexture2D(&texDesc, nullptr, &_shaderOutput);

	// XMStoreFloat4x4(&_projection, XMMatrixPerspectiveFovLH(XM_PIDIV2, _WindowWidth / (FLOAT)_WindowHeight, 0.01f, 10000.0f));

	// // Update our time
	// static double t = 0.0f;



	// if (_driverType == D3D_DRIVER_TYPE_REFERENCE)
	// {
	// 	t += (float)XM_PI * 0.0125f;
	// }
	// else
	// {
	// 	static DWORD dwTimeStart = 0;
	// 	DWORD dwTimeCur = GetTickCount();

	// 	if (dwTimeStart == 0)
	// 		dwTimeStart = dwTimeCur;

	// 	t = (dwTimeCur - dwTimeStart) / 1000.0f;
	// }
	// if (lastTime != currentTime)
	// {
	// 	lastTime = currentTime;
	// }
	// currentTime = t;

	// double DeltaTime = currentTime - lastTime;

	// //DBOUT("The value of x is " << DeltaTime << '\n');

	// time -= DeltaTime;
	// if (time <= 0.0f)
	// {
	// 	time = 1.0f;
	// 	DBOUT("Second" << '\n');

	// }


	// Frame_ConstantBuffer.gTime = (float)t;
	// sfxcb.gTime = (float)DeltaTime;

	// if (GetAsyncKeyState(VK_UP))
	// {

	// 		//cubeRot += (XM_PI / 2);
	// 		//RenderInWireframe = !RenderInWireframe;
	// 	RenderInWireframe = true;
		
	// }
	// if (GetAsyncKeyState(VK_DOWN))
	// {

	// 		//cubeRot += (XM_PI / 2);
	// 		//RenderInWireframe = !RenderInWireframe;
	// 	RenderInWireframe = false;
		
	// }

	// if (GetAsyncKeyState(VK_RIGHT) && !pressed)
	// {
		
	// 	blurLoopAmount++;
	// 	pressed = true;

	// }
	// else if (GetAsyncKeyState(VK_LEFT) && !pressed)
	// {
	// 	pressed = true;

	// 	if (blurLoopAmount > 1)
	// 	{
	// 		blurLoopAmount--;
	// 	}
	// }
	// else if (!GetAsyncKeyState(VK_RIGHT) &&!GetAsyncKeyState(VK_LEFT) && pressed)
	// {
	// 	pressed = false;

	// }

	// if (BlurOn)
	// {
	// 	DBOUT(std::to_wstring(blurLoopAmount) << std::endl;);
	// }

	// if(!GetAsyncKeyState('3'))
	// {
	// 	_currentCamera = _carReferance->FollowCamera;
	// }


	// if (GetAsyncKeyState('4'))
	// {
	// 	_currentCamera = _carReferance->FrontCamera;
	// }

	// if (GetAsyncKeyState('V'))
	// {

	// 	if (blurLoopAmount > 0)
	// 	{
	// 		blurLoopAmount--;
	// 	}
	// }

	// if (GetAsyncKeyState('1'))
	// {

	// 	_currentCamera = LookDown;
	// }
	// if (GetAsyncKeyState('2'))
	// {

	// 	_currentCamera = LookAtPitch;

	// }



	// if (GetAsyncKeyState('B'))
	// {
	// 	if (blurLoopAmount < 3)
	// 	{
	// 		blurLoopAmount++;
	// 	}
	// }

	// if (GetAsyncKeyState('U'))
	// {
	// 	BlurOn = true;
	// }
	// if (GetAsyncKeyState('I'))
	// {
	// 	BloomOn = true;
	// }
	// if (GetAsyncKeyState('J'))
	// {
	// 	BlurOn = false;
	// }
	// if (GetAsyncKeyState('K'))
	// {
	// 	BloomOn = false;
	// }

	





	// //Set sphereWorld's world space using the transformations

	// List<SceneObject>* temp;
	// temp = SceneObject::ObjectList;




	// for (int i = 0; i < SceneObject::ObjectCount - 1; i++)
	// {
	// 	temp->val->Update((float)DeltaTime);
	// 	temp = temp->next;
	// }
	// XMFLOAT3 camera3Float;
	// XMStoreFloat3(&camera3Float, _currentCamera->GetWorldPosition());

	// XMFLOAT4 camera4Float;
	// XMStoreFloat4(&camera4Float, _currentCamera->GetWorldPosition());
	// BillboardObject::GetInstance()->UpdateCameraPosition(XMFLOAT4(camera4Float));

	// //Frame Constant Buffer
	// for (int i = 0; i < DLight.size(); i++)
	// {
	// 	Frame_ConstantBuffer.gDirLight[i] = DLight.at(i);
	// }	
	
	// for (int i = 0; i < PLight.size(); i++)
	// {
	// 	Frame_ConstantBuffer.gPointLight[i] = PLight.at(i);
	// }

	// for (int i = 0; i < SLight.size(); i++)
	// {
	// 	Frame_ConstantBuffer.gSpotLight[i] = SLight.at(i);
	// }
	// Frame_ConstantBuffer.PointLightCount = (float)PLight.size();
	// Frame_ConstantBuffer.DirLightCount = (float)DLight.size();
	// Frame_ConstantBuffer.SpotLightCount = (float)SLight.size();

	// Frame_ConstantBuffer.View = _currentCamera->GetTransposedViewMatrix();
	// XMStoreFloat4(&(Frame_ConstantBuffer.EyePosW), _currentCamera->GetWorldPosition());
	// Frame_ConstantBuffer.Projection = XMMatrixTranspose(XMLoadFloat4x4(&_projection));


	// BuildShadowTransform();

	SceneManager::GetInstance().Update();
	Graphics::GetInstance().Update();

	SceneManager::GetInstance().Update();
	ResourceManager::GetInstance().Update();
}

// void Application::Draw()
// {
// 	//
// 	// Clear the back buffer
// 	//
// 	float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; // red,green,blue,alpha

// 	float ClearColorb[4] = { 0.0f, 0.0f, 0.0f, 1.0f };

// 	ID3D11ShaderResourceView *const pSRV[1] = { NULL };

// 	ID3D11RenderTargetView* pRTV[8] = { nullptr,nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, };


// 	//Clear all RTVs
// 	_pImmediateContext->ClearRenderTargetView(_pRenderTargetView, ClearColorb);
// 	_pImmediateContext->ClearRenderTargetView(_pBlurTargetView, ClearColor);
// 	_pImmediateContext->ClearRenderTargetView(_pBrightnessMapTargetView, ClearColorb);
// 	_pImmediateContext->ClearRenderTargetView(_pSceneTargetView, ClearColorb);

// 	_pImmediateContext->ClearDepthStencilView(_depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
// 	_pImmediateContext->IASetInputLayout(_pVertexLayout);



// 	//Render Scene To Shadow Map

// 	mSmap->BindDsvAndSetNullRenderTarget(_pImmediateContext);

// 	DrawSceneToShadowMap();

// 	_pImmediateContext->RSSetState(0);

// 	//Render the Scene to a Texture

// 	_pImmediateContext->RSSetViewports(1, &vp);
// 	ID3D11RenderTargetView* input[2] = { _pSceneTargetView, _pBrightnessMapTargetView};

// 	_pImmediateContext->OMSetRenderTargets(2, *&input, _depthStencilView);

// 	Frame_ConstantBuffer.View = _currentCamera->GetTransposedViewMatrix();
// 	//XMStoreFloat4(&(Frame_ConstantBuffer.EyePosW), _currentCamera->GetWorldPosition());
// 	Frame_ConstantBuffer.Projection = XMMatrixTranspose(XMLoadFloat4x4(&_projection));

// 	_pImmediateContext->UpdateSubresource(_pCBFrame, 0, nullptr, &Frame_ConstantBuffer, 0, 0);
// 	_pImmediateContext->VSSetConstantBuffers(0, 1, &_pCBFrame);
// 	_pImmediateContext->PSSetConstantBuffers(0, 1, &_pCBFrame);




// 	// Render opaque objects //

// 	// Set the blend state for transparent objects






// 	// Set vertex buffer
// 	UINT stride = sizeof(Vertex);
// 	UINT offset = 0;

// 	// Set primitive topology
// 	_pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


// 	if (RenderInWireframe)
// 		_pImmediateContext->RSSetState(_wireFrame);
// 	else
// 		_pImmediateContext->RSSetState(nullptr);

// 	//ConstantBuffer cb;
// 	_pImmediateContext->PSSetShaderResources(0, 1,  pSRV);
// 	_pImmediateContext->PSSetShaderResources(1, 1,  pSRV);
// 	_pImmediateContext->PSSetShaderResources(2, 1,  pSRV);
// 	_pImmediateContext->PSSetShaderResources(3, 1,  pSRV);
// 	_pImmediateContext->PSSetShaderResources(4, 1,  pSRV);
// 	_pImmediateContext->PSSetShaderResources(5, 1,  pSRV);
// 	_pImmediateContext->PSSetShaderResources(6, 1, mSmap->DepthMapSRV());

// 	List<SceneObject>* temp;
// 	temp = SceneObject::ObjectList;
// 	std::vector<SceneObject*> transparantObjects;
// 	_pImmediateContext->PSSetSamplers(1, 1, &shadow);

// 	for (int i = 0; i < SceneObject::ObjectCount - 1; i++)
// 	{
// 		//SetShader
// 		_pImmediateContext->VSSetShader(_baseShader->GetVS(), nullptr, 0);
// 		_pImmediateContext->VSSetConstantBuffers(0, 1, &_pCBFrame);
// 		_pImmediateContext->VSSetConstantBuffers(1, 1, &_pCBObject);


// 		_pImmediateContext->PSSetShader(_baseShader->GetPS(), nullptr, 0);
// 		_pImmediateContext->PSSetConstantBuffers(0, 1, &_pCBFrame);
// 		_pImmediateContext->PSSetConstantBuffers(1, 1, &_pCBObject);
// 		IDrawable* toDraw = dynamic_cast<IDrawable*>(temp->val);
// 		if (toDraw != nullptr)
// 		{



// 			if (!toDraw->GetHasTransparancy())
// 			{
// 				_pImmediateContext->UpdateSubresource(_pCBObject, 0, nullptr, &temp->val->GetObjectCB(), 0, 0);

// 				toDraw->Draw(_pImmediateContext, &stride, &offset, _pCBObject);
// 			}
// 			else
// 			{
// 				transparantObjects.push_back(temp->val);
// 			}

// 		}
// 		temp = temp->next;
// 		_pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

// 		if (RenderInWireframe)
// 			_pImmediateContext->RSSetState(_wireFrame);
// 		else
// 			_pImmediateContext->RSSetState(nullptr);
// 	}

// 	//SetShader
// 	_pImmediateContext->VSSetShader(_baseShader->GetVS(), nullptr, 0);
// 	_pImmediateContext->VSSetConstantBuffers(0, 1, &_pCBFrame);
// 	_pImmediateContext->VSSetConstantBuffers(1, 1, &_pCBObject);


// 	_pImmediateContext->PSSetShader(_baseShader->GetPS(), nullptr, 0);
// 	_pImmediateContext->PSSetConstantBuffers(0, 1, &_pCBFrame);
// 	_pImmediateContext->PSSetConstantBuffers(1, 1, &_pCBObject);
// 	//SetShader
// 	float blendFactor[] = { 0.2f, 0.2f, 0.2f, 1.0f };
// 	_pImmediateContext->OMSetBlendState(Transparency, blendFactor, 0xffffffff);

// 	for (int i = 0; i < transparantObjects.size(); i++)
// 	{
// 		IDrawable* toDraw = dynamic_cast<IDrawable*>(transparantObjects.at(i));
// 		_pImmediateContext->UpdateSubresource(_pCBObject, 0, nullptr, &transparantObjects.at(i)->GetObjectCB(), 0, 0);

// 		toDraw->Draw(_pImmediateContext, &stride, &offset, _pCBObject);
// 	}

// 	_pImmediateContext->OMSetBlendState(0, 0, 0xffffffff);

// 	_pImmediateContext->PSSetShaderResources(0, 1, pSRV);
// 	_pImmediateContext->PSSetShaderResources(1, 1, pSRV);
// 	_pImmediateContext->PSSetShaderResources(2, 1, pSRV);
// 	_pImmediateContext->PSSetShaderResources(3, 1, pSRV);
// 	_pImmediateContext->PSSetShaderResources(4, 1, pSRV);
// 	_pImmediateContext->PSSetShaderResources(5, 1, pSRV);
// 	_pImmediateContext->PSSetShaderResources(6, 1, pSRV);



// 	_pImmediateContext->OMSetRenderTargets(8, *&pRTV, NULL);

// 	//// End of Scene Render--------------------------------



// 	//Start of PostProssessing

// 	_pImmediateContext->RSSetState(nullptr);
// 	_pImmediateContext->PSSetShaderResources(0, 1, pSRV);
	
// 	_pImmediateContext->IASetInputLayout(_pScreenVertexLayout);
	
// 	_pImmediateContext->VSSetConstantBuffers(0, 1, &_pConstantBufferSFX);
// 	_pImmediateContext->PSSetConstantBuffers(0, 1, &_pConstantBufferSFX);

// 	stride = sizeof(ScreenVertex);
// 	//Set vertex buffer

// 	_pImmediateContext->IASetVertexBuffers(0, 1, &_pScreenVertexBuffer, &stride, &offset);

// 	//Set index buffer
// 	_pImmediateContext->IASetIndexBuffer(_pScreenIndexBuffer, DXGI_FORMAT_R16_UINT, 0);

// 	//Set primitive topology
// 	_pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
// 	_pImmediateContext->UpdateSubresource(_pConstantBufferSFX, 0, nullptr, &sfxcb, 0, 0);

// 	if (BloomOn)
// 	{
// 		_pImmediateContext->OMSetRenderTargets(1, &_pBlurTargetView, NULL);


// 		_pImmediateContext->VSSetShader(_blurShader->GetVS(), nullptr, 0);

// 		_pImmediateContext->PSSetShader(_blurShader->GetPS(), nullptr, 0);



// 		for (int i = 0; i < 9; i++)
// 		{
// 			_pImmediateContext->PSSetShaderResources(0, 1, &_pBrightnessMapResourceView);

// 			_pImmediateContext->DrawIndexed(6, 0, 0);


// 			_pImmediateContext->CopyResource(_brightnessMapTexture, _blurTexture);

// 			_pImmediateContext->PSSetShaderResources(0, 1, pSRV);


// 		}

// 		_pImmediateContext->OMSetRenderTargets(1, &_pBloomTargetView, NULL);

// 		_pImmediateContext->VSSetShader(_bloomShader->GetVS(), nullptr, 0);

// 		_pImmediateContext->PSSetShader(_bloomShader->GetPS(), nullptr, 0);

// 		_pImmediateContext->PSSetShaderResources(0, 1, &_pBrightnessMapResourceView);
// 		_pImmediateContext->PSSetShaderResources(1, 1, &_pSceneResourceView);


// 		_pImmediateContext->DrawIndexed(6, 0, 0);

// 		_pImmediateContext->PSSetShaderResources(0, 1, pSRV);
// 		_pImmediateContext->PSSetShaderResources(1, 1, pSRV);


// 		_pImmediateContext->CopyResource(_sceneRender, _bloomTexture);
// 	}

// 	// Blur Scene
// 	if (BlurOn)
// 	{

// 		_pImmediateContext->OMSetRenderTargets(1, &_pBlurTargetView, NULL);


// 		_pImmediateContext->VSSetShader(_blurShader->GetVS(), nullptr, 0);

// 		_pImmediateContext->PSSetShader(_blurShader->GetPS(), nullptr, 0);





// 		for (int i = 0; i < blurLoopAmount; i++)
// 		{

// 			_pImmediateContext->PSSetShaderResources(0, 1, &_pSceneResourceView);

// 			_pImmediateContext->DrawIndexed(6, 0, 0);

// 			_pImmediateContext->PSSetShaderResources(0, 1, pSRV);

// 			_pImmediateContext->CopyResource(_sceneRender, _blurTexture);
// 		}

// 	}
// 	_pImmediateContext->PSSetShaderResources(0, 1, pSRV);


	
// 	// Final Render
// 	_pImmediateContext->OMSetRenderTargets(1, &_pRenderTargetView, _depthStencilView);

// 	_pImmediateContext->VSSetShader(_renderScene->GetVS(), nullptr, 0);
// 	_pImmediateContext->PSSetShader(_renderScene->GetPS(), nullptr, 0);

// 	//_pImmediateContext->OMSetBlendState(nullptr, nullptr, 0xffffffff);

// 	// Set vertex buffer

// 	if (GetAsyncKeyState('P'))
// 	{
// 		_pImmediateContext->PSSetShaderResources(0, 1, mSmap->DepthMapSRV());
// 	}
// 	else 
// 	{
// 		_pImmediateContext->PSSetShaderResources(0, 1, &_pSceneResourceView);
// 	}
// 	_pImmediateContext->DrawIndexed(6, 0, 0);
// 	_pImmediateContext->PSSetShaderResources(0, 1, pSRV);

// 	_pSwapChain->Present(0, 0);
// }

// void Application::Resize()
// {
// 	int i = 0; 
	
// 	i++;


// }

// void Application::DrawSceneToShadowMap()
// {
// 	List<SceneObject>* temp;
// 	temp = SceneObject::ObjectList;
// 	std::vector<SceneObject*> transparantObjects;

// 	XMMATRIX LightProj = XMLoadFloat4x4(&mLightProj);
// 	XMMATRIX LightView = XMLoadFloat4x4(&mLightView);				
// 	//
// 	Frame_ConstantBuffer.View = XMMatrixTranspose(LightView);
// 	Frame_ConstantBuffer.Projection = XMMatrixTranspose(LightProj);
// 	Frame_ConstantBuffer.gCameraView = XMMatrixTranspose(LightView);
// 	Frame_ConstantBuffer.gCameraProj = XMMatrixTranspose(LightProj);

// 	_pImmediateContext->UpdateSubresource(_pCBFrame, 0, nullptr, &Frame_ConstantBuffer, 0, 0);
// 	_pImmediateContext->VSSetConstantBuffers(0, 1, &_pCBFrame);
// 	_pImmediateContext->PSSetConstantBuffers(0, 1, &_pCBFrame);

// 	UINT stride = sizeof(Vertex);
// 	UINT offset = 0;
// 	_pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

// 	for (int i = 0; i < SceneObject::ObjectCount - 1; i++)
// 	{

// 		IDrawable* toDraw = dynamic_cast<IDrawable*>(temp->val);
// 		SkyMapObject* test = dynamic_cast<SkyMapObject*>(temp->val);
// 		if (test == nullptr)
// 		{
// 			//BillboardObject* biltest = dynamic_cast<BillboardObject*>(temp->val);
// 			//if(biltest == nullptr)
// 			//{
// 				/*WallObject* wallTest = dynamic_cast<WallObject*>(temp->val);
// 				if (wallTest == nullptr)
// 				{*/
// 					if (toDraw != nullptr)
// 					{

// 						//SetShader
// 						_pImmediateContext->VSSetConstantBuffers(0, 1, &_pCBFrame);
// 						_pImmediateContext->VSSetConstantBuffers(1, 1, &_pCBObject);

// 						_pImmediateContext->PSSetConstantBuffers(0, 1, &_pCBFrame);
// 						_pImmediateContext->PSSetConstantBuffers(1, 1, &_pCBObject);
						
// 						toDraw->Draw(_pImmediateContext, &stride, &offset, _pCBObject);

// 					}
// 				//}
// 			//}
// 		}
// 		temp = temp->next;
// 		_pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
// 	}


// }