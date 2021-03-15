#pragma once
/*..Used as a transform wrapper..*/
#include "GameObject.h"

/*..Mesh with animations data..*/
#include "graphics/skinned_mesh_instance.h"

/*..Collisions..*/
#include "ObjectType.h"

class AnimatedGameObject : public GameObject, public virtual gef::SkinnedMeshInstance
{
protected:

	AnimatedGameObject(const gef::Skeleton& skeleton, gef::Platform& platform, b2World* world, bool is_dynamic);

public:

	~AnimatedGameObject();

	static AnimatedGameObject* Create(const gef::Skeleton& skeleton, gef::Platform& platform, b2World* world, bool is_dynamic);

	/// @brief Initialises and sets the static mesh for the Actor.
	/// @param[in] Takes a pointer to a primitive builder.
	/// @param[in] Filepath to the .scn file on disc.
	virtual void SetMeshFromDisc(PrimitiveBuilder* primitive_builder, std::string filepath) override;

	// @brief Loads an asset with a specified filepath.
	// @param[in] A reference to the platform.
	// @param[in] A string representing the filepath.
	gef::Scene* LoadSceneAssets(gef::Platform& platform, const char* filename) override;

	// @brief Grab a mesh from the scene object. Returns a mesh from the front of the list.
	// @param[in] Takes a pointer to the scene object.
	//gef::Mesh* GameObject::GetMeshFromSceneAssets(gef::Scene* scene) override;




	/*..Standard functions..*/

	/// @brief Renders this actor.
	/// @param[in] Takes the scene 3D renderer.
	virtual void Render(gef::Renderer3D* renderer) override;

	/// @brief Updates the gameobjets behaviour.
	/// @param[in] Change in time since the last frame.
	virtual void Update(float delta_time) override;

	/// @brief Builds the objects transform 
	virtual void BuildTransform() override;



private:



};

