#pragma once
#include"../App/Common.h"
#include"./Objects.h"

namespace raytracer 
{
	class Scene 
	{
	protected:
		typedef vector<const Sphere*> SpheresCollection;
		typedef vector<const Plane*> PlanesCollection;
		typedef vector<const Light*> LightsCollection;
	
		SpheresCollection spheres;
		PlanesCollection planes;
		
		math::Vec3 light;
		bool IsBuilt;
	public:
		Scene() {
			IsBuilt = false;
		}

		void AddSphere(const Sphere& sphere) {
			spheres.push_back(&sphere);
		}
		
		void AddPlane(const Plane& plane) {
			planes.push_back(&plane);
		}

		void SetLight(math::Vec3 l) {
			light = l;
		}

		const SpheresCollection& GetSpheres() const {
			return spheres;
		}

		const PlanesCollection& GetPlanes() const {
			return planes;
		}

		const math::Vec3& GetLight() const {
			return light;
		}

		virtual void Build() {}
	};
}
