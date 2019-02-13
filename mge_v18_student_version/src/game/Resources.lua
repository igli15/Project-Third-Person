print("Hello LUA");

meshesLoadPath = "../assets/mge/models/"
texturesLoadPath = "../assets/mge/textures/"

meshes = 
{
	["planeMesh"] = meshesLoadPath.."plane.obj",
	["cubeMesh"] = meshesLoadPath.."cube_smooth.obj",
	["carMesh"] = meshesLoadPath.."Car.obj",
	["testMesh"] = meshesLoadPath.."stuff.obj",
	["cylinderMesh"] = meshesLoadPath.."cylinder_smooth.obj",
}


diffuseTextures = 
{
	["brickTex"] = texturesLoadPath.."bricks.jpg",
	["carTex"] = texturesLoadPath.."carTex.png",
	["containerDiffuse"] = texturesLoadPath.."container2.png",
	["buildingTex"] = texturesLoadPath.."stuffTex.png",
	
}

specularTextures = 
{
	["containerSpecular"] = texturesLoadPath.."container2_specular.png",
	["buildingSpec"] = texturesLoadPath.."stuffSpec.png",
}