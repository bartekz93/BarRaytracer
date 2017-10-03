#define MAXITERATIONS 4

//--------------------------------------------------------------------------------------
struct VS_INPUT
{
    float2 Pos : POSITION;
};

struct PS_INPUT
{
    float4 Pos : SV_POSITION;
	float2 Tex : TEXCOORD0;
};

struct Ray
{
	float3 start;
	float3 dir;
};

struct Obj
{
	int type;
	float3 pos;

	float r;
	float3 normal;

	float3 color;
	float reflect;

	float3 specColor;
	int spec;
};

StructuredBuffer<Obj> Objs : register(t1);

cbuffer Settings : register(b1)
{
	float4x4 cameraWorld;
	float3 light;			// 12
	int numObjects;			// 4

	float screenH;			// 4
	float zNear;			// 4
	float screenW;			// 4
	float alignation2;		// 4
};


//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
PS_INPUT VS( VS_INPUT input )
{
	PS_INPUT output = (PS_INPUT)0;
	output.Pos = float4(input.Pos.x, input.Pos.y, 0, 1);
	output.Tex = input.Pos;
	return output;
}

//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------

void CreateRay(float3 start, float3 at, out Ray r)
{
	r.start = start;
	r.dir = normalize(at - start);
}

float ComputeLighting(int id, float3 p, float3 light, float3 normal, float3 cam)
{
	float3 toCamera = normalize(cam - p);
	float3 toLight = normalize(light - p);
	float3 reflection = normalize(reflect(-toLight, normal));

	float attenuation = saturate(1.0 - length(light - p) / 200.0);
	float col = saturate(dot(normal, toLight)*attenuation);

	if (Objs[id].spec) {
		col += pow(saturate(dot(toCamera, reflection)), 16);
	}

	return saturate(col);
}

float HitTest(int id, Ray ray)
{
	float dist = -1;
	if (Objs[id].type == 0) //sphere
	{
		float b = dot((ray.start - Objs[id].pos) * 2, ray.dir);
		float c = dot((ray.start - Objs[id].pos), (ray.start - Objs[id].pos)) - pow(Objs[id].r, 2);

		float d = pow(b, 2.0) - 4.0 * c;

		float t1 = (-b + sqrt(d)) / 2;
		float t2 = (-b - sqrt(d)) / 2;

		if (d >= 0)
		{
			if (t1 > 0.0f && t2 > 0) dist = min(t1, t2);
		}
	}
	else // plane
	{
		dist = dot(Objs[id].pos - ray.start, Objs[id].normal) / dot(ray.dir, Objs[id].normal);
	}

	return dist;
}

float3 GetNormalInPoint(int id, float3 p)
{
	if (Objs[id].type == 0) //sphere
	{
		return normalize(p - Objs[id].pos);
	}
	else
	{
		return Objs[id].normal;
	}
}

float CastRay(inout Ray ray, out float3 hitPoint, out int objIndex, int except = -1)
{
	float minDist = -1.0;
	float dist;

	for (int j = 0; j<numObjects; j++) {

		if (j == except) continue;

		dist = HitTest(j, ray);
		if (dist > 0.0 && (minDist < 0.0 || dist < minDist)) {
			minDist = dist;
			objIndex = j;
		}
	}

	if (minDist > 0.0)
	{
		hitPoint = ray.start + ray.dir*minDist;
	}

	return minDist;
}

float4 PSRaytracing(PS_INPUT input) : SV_Target
{
	float3 pixel = float3(0, 0, 0);

	float3 cameraPos = float3(cameraWorld[3][0], cameraWorld[3][1], cameraWorld[3][2]);

	pixel.x = input.Tex.x * (screenW / 2.0);
	pixel.y = input.Tex.y * (screenH / 2.0);
	pixel.z = zNear;
	pixel = mul(float4(pixel, 1.0), cameraWorld).xyz;


	float3 color = float3(0, 0, 0);
	float cumulatedDiffuse = 1.0;
	float cumulatedReflection = 1.0;

	//-----------------------------

	Ray ray;
	float3 hitPoint;
	int hitObjectId = -1;

	Ray shadowRay;
	float shadowDist;
	float3 shadowHitPoint;
	int shadowObjectId = -1;
	
	int i = 0;
	for (; i < MAXITERATIONS; i++) {
		if (i == 0) {
			CreateRay(cameraPos, pixel, ray);	
		}
		else {
			if (Objs[hitObjectId].reflect > 0) {
				float3 n = GetNormalInPoint(hitObjectId, hitPoint);
				ray.start = hitPoint;
				ray.dir = normalize(reflect(ray.dir, n));
			}
		}

		if (CastRay(ray, hitPoint, hitObjectId, hitObjectId) > 0) {
			CreateRay(hitPoint, hitPoint + (light - hitPoint), shadowRay);
			shadowDist = CastRay(shadowRay, shadowHitPoint, shadowObjectId, hitObjectId);
			if (shadowDist > 0.0 && shadowDist < length(light - hitPoint)) {
				cumulatedDiffuse *= 0.2;
			}
			
			cumulatedDiffuse *= ComputeLighting(hitObjectId, hitPoint, light, GetNormalInPoint(hitObjectId, hitPoint), ray.start);;
			color += Objs[hitObjectId].color*cumulatedDiffuse*cumulatedReflection*(1.0 - Objs[hitObjectId].reflect);
			color = saturate(color);
			cumulatedReflection *= Objs[hitObjectId].reflect;

			if (!(Objs[hitObjectId].reflect > 0.0)) break;
		}
		else break;
	}

	return float4(color, 1);
}



float4 PSTest(PS_INPUT input) : SV_Target
{
	return float4(input.Tex.x, input.Tex.y, 0, 1);
}

