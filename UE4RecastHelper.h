
#ifndef UE4_RECAST_HELPER__
#define UE4_RECAST_HELPER__

#include "DetourNavMesh.h"
#include "DetourNavMeshQuery.h"
#include "DetourNavMeshQuery.h"
#include <math.h>
#include <inttypes.h>
#include <vector>

namespace UE4RecastHelper
{
	struct NavMeshSetHeader
	{
		int32_t magic;
		int32_t version;
		int32_t numTiles;
		dtNavMeshParams params;
	};

	struct NavMeshTileHeader
	{
		dtTileRef tileRef;
		int32_t dataSize;
	};

	static const int NAVMESHSET_MAGIC = 'M' << 24 | 'S' << 16 | 'E' << 8 | 'T'; //'MSET';
	static const int NAVMESHSET_VERSION = 1;

	struct FVector3
	{
		float X;
		float Y;
		float Z;
	public:
		inline FVector3() :X(0.f), Y(0.f), Z(0.f) {}
		inline FVector3(float* InV) : X(InV[0]), Y(InV[1]), Z(InV[2]) {}
		inline FVector3(float px, float py, float pz) : X(px), Y(py), Z(pz) {}
		FVector3(const FVector3&) = default;

		inline FVector3 operator-(const FVector3& V) const {
			return FVector3(X - V.X, Y - V.Y, Z - V.Z);
		}
		inline FVector3 operator+(const FVector3& V)const {
			return FVector3(X + V.X, Y + V.Y, Z + V.Z);
		}
		inline FVector3 operator-(const float& V)const {
			return FVector3(X - V, Y - V, Z - V);
		}
		inline FVector3 operator+(const float& V)const {
			return FVector3(X + V, Y + V, Z + V);
		}
		inline FVector3 GetAbs()const
		{
			return FVector3{ fabsf(X),fabsf(Y),fabsf(Z) };
		}
	};

	FVector3 Recast2UnrealPoint(const FVector3& Vector);
	FVector3 Unreal2RecastPoint(const FVector3& Vector);

	void SerializedtNavMesh(const char* path, const dtNavMesh* mesh);
	dtNavMesh* DeSerializedtNavMesh(const char* path);

	bool dtIsValidNavigationPoint(dtNavMesh* InNavMeshData, const FVector3& InPoint, const FVector3& InExtent = FVector3{ 10.f,10.f,10.f });

	bool FindDetourPathByNavMesh(dtNavMesh* InNavMesh ,const FVector3& InStart, const FVector3& InEnd, std::vector<FVector3>& OutPaths);
};


#endif