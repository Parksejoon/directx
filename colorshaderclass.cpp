//
// FileName : colorshaderclass.cpp
//
#include "colorshaderclass.h"


//
// CLASS FUNCTION
//
ColorShaderClass::ColorShaderClass()
{
	m_vertexShader = 0;
	m_pixelShader = 0;
	m_layout = 0;
	m_matrixBuffer = 0;
}

ColorShaderClass::ColorShaderClass(const ColorShaderClass& other)
{
}

ColorShaderClass::~ColorShaderClass()
{
}

bool ColorShaderClass::Initialize(ID3D11Device* device, HWND hwnd)
{
	bool result;


	// ���� ���̴��� �ȼ� ���̴��� �ʱ�ȭ�մϴ�.
	result = InitializeShader(device, hwnd, L"../Studying_DX/color.vs", L"../Studying_DX/color.ps");
	if (!result)
	{
		return false;
	}

	return true;
}

void ColorShaderClass::Shutdown()
{
	// ���� ���̴��� �ȼ� ���̴� �� �׿� ���õ� �͵��� ��ȯ�մϴ�.
	ShutdownShader();

	return;
}

bool ColorShaderClass::Render(ID3D11DeviceContext* deviceContext, int indexCount,
	XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix)
{
	bool result;


	// �������� ����� ���̴��� ���ڸ� �Է��մϴ�.
	result = SetShaderParameters(deviceContext, worldMatrix, viewMatrix, projectionMatrix);
	if (!result)
	{
		return false;
	}

	// ���̴��� �̿��Ͽ� �غ�� ���۸� �׸��ϴ�.
	RenderShader(deviceContext, indexCount);

	return true;
}

bool ColorShaderClass::InitializeShader(ID3D11Device* device, HWND hwnd, WCHAR* vsFilename, WCHAR* psFilename)
{
	HRESULT result;
	ID3D10Blob* errorMessage;
	ID3D10Blob* vertexShaderBuffer;
	ID3D10Blob* pixelShaderBuffer;
	D3D11_INPUT_ELEMENT_DESC plygonLayout[2];
	unsigned int numElements;
	D3D11_BUFFER_DESC matrixBufferDesc;


	// �� �Լ����� ����ϴ� �����͵��� NULL�� �ʱ�ȭ�մϴ�.
	errorMessage = NULL;
	vertexShaderBuffer = NULL;
	pixelShaderBuffer = NULL;

	// ���� ���̴��� �������մϴ�.
	result = D3DCompileFromFile(vsFilename, NULL, NULL, "ColorVertexShader", "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0,
		&vertexShaderBuffer, &errorMessage);
	if (FAILED(result))
	{
		// ���̴��� �����Ͽ� �����ϸ� ���� �޼����� ����մϴ�.
		if (errorMessage)
		{
			OutputShaderErrorMessage(errorMessage, hwnd, vsFilename);
		}
		// ���� �޼����� ���ٸ� ���̴� ������ ã�� ���Ѱ��Դϴ�.
		else
		{
			MessageBox(hwnd, vsFilename, L"Missing Shader File", MB_OK);
		}

		return false;
	}

	// �ȼ� ���̴��� �������մϴ�.
	result = D3DCompileFromFile(psFilename, NULL, NULL, "ColorPixelShader", "ps_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0,
		&pixelShaderBuffer, &errorMessage);
	if (FAILED(result))
	{
		// ���̴� �����Ͽ� �����ϸ� ���� �޼����� ����մϴ�.
		if (errorMessage)
		{
			OutputShaderErrorMessage(errorMessage, hwnd, psFilename);
		}
		// ���� �޼����� ���ٸ� ���̴� ������ ã�� ���Ѱ��Դϴ�.
		else
		{
			MessageBox(hwnd, psFilename, L"Missing Shader File", MB_OK);
		}

		return false;
	}

	// ���۷κ��� ���� ���̴��� �����մϴ�.
	result = device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), NULL, &m_vertexShader);
	if (FAILED(result))
	{
		return false;
	}

	// ���۷κ��� �ȼ� ���̴��� �����մϴ�.
	result = device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), NULL, &m_pixelShader);
	if (FAILED(result))
	{
		return false;
	}

	// ���� �Է� ���̾ƿ� description�� �ۼ��մϴ�.
	// �� ������ ModelClass�� ���̴��� �ִ� VertexType�� ��ġ�ؾ� �մϴ�.
	plygonLayout[0].SemanticName = "POSITION";
	plygonLayout[0].SemanticIndex = 0;
	plygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	plygonLayout[0].InputSlot = 0;
	plygonLayout[0].AlignedByteOffset = 0;
	plygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	plygonLayout[0].InstanceDataStepRate = 0;

	plygonLayout[1].SemanticName = "COLOR";
	plygonLayout[1].SemanticIndex = 0;
	plygonLayout[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	plygonLayout[1].InputSlot = 0;
	plygonLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	plygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	plygonLayout[1].InstanceDataStepRate = 0;
	
	// ���̾ƿ��� ��� ������ �����ɴϴ�.
	numElements = sizeof(plygonLayout) / sizeof(plygonLayout[0]);

	// ���� �Է� ���̾ƿ��� �����մϴ�.
	result = device->CreateInputLayout(plygonLayout, numElements, vertexShaderBuffer->GetBufferPointer(),
		vertexShaderBuffer->GetBufferSize(), &m_layout);
	if (FAILED(result))
	{
		return false;
	}

	// �� �̻� ������ �ʴ� ���� ���̴� ���ۿ� �ȼ� ���̴� ���۸� �����մϴ�.
	vertexShaderBuffer->Release();
	vertexShaderBuffer = 0;

	pixelShaderBuffer->Release();
	pixelShaderBuffer = 0;

	// ���� ���̴��� �ִ� ��� ��� ������ description�� �ۼ��մϴ�.
	matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	matrixBufferDesc.ByteWidth = sizeof(MatrixBufferType);
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;

	// ��� ���� �����͸� ����� �� Ŭ�������� ���� ���̴� ��� ���ۿ� �����Ҽ� �ְ� �մϴ�.
	result = device->CreateBuffer(&matrixBufferDesc, NULL, &m_matrixBuffer);
	if (FAILED(result))
	{
		return false;
	}

	return true;
}

void ColorShaderClass::ShutdownShader()
{
	// ��� ���۸� �����մϴ�.
	if (m_matrixBuffer)
	{
		m_matrixBuffer->Release();
		m_matrixBuffer = 0;
	}

	// ���̾ƿ��� �����մϴ�.
	if (m_layout)
	{
		m_layout->Release();
		m_layout = 0;
	}

	// ���� ���̴��� �����մϴ�.
	if (m_vertexShader)
	{
		m_vertexShader->Release();
		m_vertexShader = 0;
	}

	return;
}

void ColorShaderClass::OutputShaderErrorMessage(ID3D10Blob* errorMessage, HWND hwnd, WCHAR* shaderFilename)
{
	char* compileErrors;
	unsigned long bufferSize;
	ofstream fout;


	// ���� �޼����� ��� �ִ� ���ڿ� ������ �����͸� �����ɴϴ�.
	compileErrors = (char*)(errorMessage->GetBufferPointer());

	// �޼����� ���̸� �����ɴϴ�.
	bufferSize = errorMessage->GetBufferSize();

	// ������ ���� �ȿ� �޼����� ����մϴ�.
	fout.open("shader-error.txt");

	// ���� �޼����� �ۼ��մϴ�.
	for (int i = 0; i < bufferSize; i++)
	{
		fout << compileErrors[i];
	}

	// ������ �ݽ��ϴ�.
	fout.close();

	// ���� �޼����� �����մϴ�.
	errorMessage->Release();
	errorMessage = 0;

	// ������ ������ ������ �˾� �޼����� �˷��ݴϴ�.
	MessageBox(hwnd, L"Error compiling shader. Check shader-error.txt for message.", shaderFilename, MB_OK);

	return;
}

bool ColorShaderClass::SetShaderParameters(ID3D11DeviceContext* deviceContext, XMMATRIX worldMatrix,
	XMMATRIX viewMatrix, XMMATRIX projectionMatrix)
{
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	MatrixBufferType* dataPtr;
	unsigned int bufferNumber;


	// ����� transpose�Ͽ� ���̴����� ����� �� �ְ� �մϴ�.
	worldMatrix = XMMatrixTranspose(worldMatrix);
	viewMatrix = XMMatrixTranspose(viewMatrix);
	projectionMatrix = XMMatrixTranspose(projectionMatrix);

	// ��� ������ ������ �� �� �ֵ��� ��޴ϴ�.
	result = deviceContext->Map(m_matrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
	{
			return false;
	}

	// ��� ������ �����Ϳ� ���� �����͸� �����ɴϴ�.
	dataPtr = (MatrixBufferType*)mappedResource.pData;

	// ��� ���ۿ� ����� �����մϴ�.
	dataPtr->world = worldMatrix;
	dataPtr->view = viewMatrix;
	dataPtr->projection = projectionMatrix;

	// ��� ������ ����� Ǳ�ϴ�.
	deviceContext->Unmap(m_matrixBuffer, 0);

	// ���� ���̴����� ��� ������ ��ġ�� �����մϴ�.
	bufferNumber = 0;

	// ���������� ���� ���̴��� ��� ���۸� �ٲ� ������ �ٲߴϴ�.
	deviceContext->VSSetConstantBuffers(bufferNumber, 1, &m_matrixBuffer);

	return true;
}

void ColorShaderClass::RenderShader(ID3D11DeviceContext* deviceContext, int indexCount)
{
	// ���� �Է� ���̾ƿ��� �����մϴ�.
	deviceContext->IASetInputLayout(m_layout);

	// �ﰢ���� �׸� ���� ���̴��� �ȼ� ���̴��� �����մϴ�.
	deviceContext->VSSetShader(m_vertexShader, NULL, 0);
	deviceContext->PSSetShader(m_pixelShader, NULL, 0);

	// �ﰢ���� �׸��ϴ�.
	deviceContext->DrawIndexed(indexCount, 0, 0);

	return;
}
