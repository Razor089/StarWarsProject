#ifndef MODELLO_H
#define MODELLO_H
#include <Windows.h>
#include <glut.h>
#include <map>
#include <assimp/assimp.h>
#include <assimp/aiVector3D.h>
#include <assimp/aiTypes.h>
#include <FreeImage.h>


class Modello{
private:
	
	const struct aiScene* scene;
	GLuint scene_list;
	struct aiVector3D scene_min, scene_max, scene_center;
	GLuint*	textureIds;
	std::map<std::string, GLuint*> textureIdMap;
	
	#define aisgl_min(x,y) (x<y?x:y)
	#define aisgl_max(x,y) (y>x?y:x)
	
public:
	Modello();
	~Modello();

	void get_bounding_box_for_node (const struct aiNode* nd, 
	struct aiVector3D* min, 
	struct aiVector3D* max, 
	struct aiMatrix4x4* trafo
	);

	void get_bounding_box (struct aiVector3D* min, struct aiVector3D* max);
	void color4_to_float4(const struct aiColor4D *c, float f[4]);
	void set_float4(float f[4], float a, float b, float c, float d);
	void apply_material(const struct aiMaterial *mtl);
	void Color4f(const struct aiColor4D *color);
	void recursive_render (const struct aiScene *sc, const struct aiNode* nd);
	int loadasset (const char* path);
	bool abortGLInit(const char* abortMessage);
	int LoadGLTextures(const aiScene* scene);
	void prepare(int value);
	void draw();
	void loadScene();
};

#endif