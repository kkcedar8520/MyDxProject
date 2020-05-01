
Texture2D<float4> InputMap: register(t0)
RWTexture2D<float4> OuputMap : register(u0);

struct BufType
{
	float3 vPickPos;
	float3 vRect[4];
	float	g_fRadius;
	int		iTIndex;

};

StructuredBuffer<BufType> Buffer0: register(t1)
#define size_x 17
#define size_y 17

[numthreads(size_x,size_y,1)]
void CSMAIN( uint3 DTid : SV_DispatchThreadID )
{
	float3 vPos = float3(texturelocation.x / 1024.0f*200.0f, texturelocation.y / 768.0f*200.0f, 0.0f);
	//OutputMap[texturelocation.xy] = float4(vPos.x, vPos.y, vPos.z, 1.0f);

	float fRadius = distance(vPos.xyz, Buffer0[0].vPickPos.xyz);
	float fDot = 1.0f - (fRadius / Buffer0[0].g_fRadius);
	if (fRadius < Buffer0[0].g_fRadius)
	{
		float4 fAlpha = float4(0, 0, 0, 0);// *float4(fDot, fDot, fDot, fDot);
		switch (Buffer0[0].iIndex)
		{
		case 0: fAlpha.x = fDot; break;
		case 1: fAlpha.y = fDot; break;
		case 2: fAlpha.z = fDot; break;
		case 3: fAlpha.w = fDot; break;
		}
		OutputMap[texturelocation.xy] = fAlpha;// Color * float4(fDot, fDot, fDot, fDot);
	}
	else
	{
		OutputMap[texturelocation.xy] = float4(1.0f, 0.0f, 0.0f, 1.0f);// -Color;
	}
}