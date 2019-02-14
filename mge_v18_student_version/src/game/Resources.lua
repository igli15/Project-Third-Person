print("Hello LUA");

--DONT FORGET TO PUT A COMMA AFTER EVERY RESOURCE!!!

meshesLoadPath = "../assets/mge/models/"
texturesLoadPath = "../assets/mge/textures/"
musicLoadPath = "../assets/mge/music/"

meshes = 
{
	["planeMesh"] = meshesLoadPath.."plane.obj",
	["cubeMesh"] = meshesLoadPath.."cube_smooth.obj",
	["carMesh"] = meshesLoadPath.."Car.obj",
	["testMesh"] = meshesLoadPath.."arena.obj",
	["cylinderMesh"] = meshesLoadPath.."cylinder_smooth.obj",
}


diffuseTextures = 
{
	["brickTex"] = texturesLoadPath.."bricks.jpg",
	["carTex"] = texturesLoadPath.."carTex.png",
	["containerDiffuse"] = texturesLoadPath.."container2.png",
	["buildingTex"] = texturesLoadPath.."arenaDiffuse.png",
	
}

specularTextures = 
{
	["containerSpecular"] = texturesLoadPath.."container2_specular.png",
	["buildingSpec"] = texturesLoadPath.."stuffSpec.png",
}

emissionTextures = 
{
	["matrix"] = texturesLoadPath.."matrix.jpg",
}

--Yes sound and music are 2 diffrent things...
--Sounds Are small clips that are played from a buffer in high quality ex: SFX
--Music are big chunks of memory that play music. This is used for music that loops or that is large
sounds = 
{
	["cannonShot"] = musicLoadPath.."cannonShot.wav",
}

musics =
{
	["expmusic"] = musicLoadPath.."expmusic.wav",
}