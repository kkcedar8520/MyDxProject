Texture2D		g_txDiffuseA : register(t0);
Texture2D		g_txDiffuseB : register(t1);
SamplerState	g_Sample0 : register(s0);

struct PS_IN
{
	float4 p : SV_POSITION;
	float4 c : COLOR0;
	float2 t : TEXCOORD0;
	float time : TEXCOORD1;
};
struct PS_IN_LINE
{
	float4 p : SV_POSITION;
	float4 c : COLOR0;
};
struct PS_OUT
{
	float4 c : SV_TARGET;
};
PS_OUT PS(PS_IN inData)
{
	PS_OUT vOut;
	float4 vFinal = g_txDiffuseA.Sample(g_Sample0, inData.t);
	vOut.c = vFinal;
	return vOut;
}
float4 PSLine(PS_IN_LINE inData) : SV_TARGET
{
	return inData.c;
}
PS_OUT PSBlend(PS_IN inData)
{
	PS_OUT vOut;
	float4 SRC = g_txDiffuseA.Sample(g_Sample0, inData.t);
	if (SRC.a < 0.5f)
	{
		discard;
	}
	//float4 DESK = g_txDiffuseB.Sample(g_Sample0, inData.t);
	//vOut.c = SRC * SRC.a + DESK * (1.0f- SRC.a);
	vOut.c = SRC;
	//vOut.c.a = 1.0f;// (1.0f - DESK.g) *inData.time;
	return vOut;
}