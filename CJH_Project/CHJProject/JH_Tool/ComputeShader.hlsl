


Texture2D<float4>		InputMap : register(t0);
RWTexture2D<float4>		OutputMap : register(u0);

struct BufType
{
	float3 vPickPos;
	float3 vRect[4];
	float  g_fRadius;
	int    iIndex;
};
StructuredBuffer<BufType> Buffer0 : register(t1);
// Group size
#define size_x 2
#define size_y 2

[numthreads(size_x, size_y, 1)]
void CSMAIN(uint3 GroupID : SV_GroupID, uint3 DispatchThreadID : SV_DispatchThreadID, uint3 GroupThreadID : SV_GroupThreadID, uint GroupIndex : SV_GroupIndex)
{
	int3 texturelocation = int3(0, 0, 0);
	//texturelocation.x = GroupID.x * size_x + GroupThreadID.x;
	//texturelocation.y = GroupID.y * size_y + GroupThreadID.y;
	texturelocation.x = DispatchThreadID.x;
	texturelocation.y = DispatchThreadID.y;

	float4 Color = InputMap.Load(texturelocation);
	float3 vPos = float3(texturelocation.x / 1024.0f*200.0f, texturelocation.y / 768.0f*200.0f, 0.0f);
	//OutputMap[texturelocation.xy] = float4(vPos.x, vPos.y, vPos.z, 1.0f);

	float fRadius = distance(vPos.xyz, Buffer0[0].vPickPos.xyz);
	float fDot = 1.0f - (fRadius / Buffer0[0].g_fRadius);
	if (true)//fRadius < Buffer0[0].g_fRadius)
	{
		float4 fAlpha = float4(0, 0, 0, 0);// *float4(fDot, fDot, fDot, fDot);
		switch (Buffer0[0].iIndex)
		{
		case 0: fAlpha.x = 1; break;
		case 1: fAlpha.y = 1; break;
		case 2: fAlpha.z = 1; break;
		case 3: fAlpha.w = 1; break;
		default:
			fAlpha.x = 1; break;
		}
		OutputMap[texturelocation.xy] = fAlpha;// Color * float4(fDot, fDot, fDot, fDot);
	}
	else
	{
		OutputMap[texturelocation.xy] = float4(1.0f, 0.0f, 0.0f, 1.0f);// -Color;
	}

}
