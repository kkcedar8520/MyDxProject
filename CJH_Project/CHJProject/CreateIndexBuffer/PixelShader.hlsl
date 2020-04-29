
Texture2D	g_txDiffuseA:register(t0);
Texture2D	g_txDiffuseB:register(t1);
SamplerState	g_Sample:register(s0);

struct PS_IN
{
	float4 p : SV_POSITION;
	float4 c : COLOR0;

};
struct PS_OUT
{
	
	float4 c : SV_TARGET;
};
PS_OUT XXXX(PS_IN inData)
{
	PS_OUT pOut;

	pOut.c = inData.c;
	return pOut;
}