struct VS_OUT
{
	float4 p : SV_POSITION;
	float4 c : COLOR0;
	float2 t : TEXCOORD0;
};
struct VS_IN
{
	float4 p : POSITION;
	float4 c : COL;
	float2 t : TEX;
};
cbuffer cb_Data:register(b0)
{

	float4x4 g_matWorld : packoffset(c0);
	float4x4 g_matView : packoffset(c4);
	float4x4 g_matProj : packoffset(c8);
	float4 time : packoffset(c12);
}
VS_OUT VS(VS_IN inData)
{
	VS_OUT vOut;
	float4 vLocal = float4(inData.p);

	float4 vWorld = mul(vLocal, g_matWorld);
	float4 vView = mul(vWorld, g_matView);
	float4 vProj = mul(vView, g_matProj);
	//vOut.p = vProj;

	vOut.p = vProj;
	vOut.c = inData.c;
	vOut.t = inData.t;
	return vOut;
}
VS_OUT VS3(float4 p : POSITION,
	float4 c : COLOR)
{
	VS_OUT vOut;
	vOut.p = p;
	vOut.c = c;
	return vOut;
}
float4 XXXX(float4 p : POSITION) : SV_POSITION
{
	float4 vOut = 0;
	vOut.x = (p.x / 800.0f) * 2.0f - 1.0f;
	vOut.y = ((p.y / 600.0f) * 2.0f - 1.0f)*-1.0f;
	vOut.z = p.z;
	vOut.w = 1.0f;
	return vOut;
}

