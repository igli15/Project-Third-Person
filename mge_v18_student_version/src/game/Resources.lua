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
	--["testMesh"] = meshesLoadPath.."arena.obj",
	["cylinderMesh"] = meshesLoadPath.."cylinder_smooth.obj",
	--["goodBoyMesh"] = meshesLoadPath.."goodBoy.obj",
	["model"] = meshesLoadPath.."orb.obj",
	["Cube"] = meshesLoadPath.."tile_test.obj",
	["Sphere"] = meshesLoadPath.."sphere_smooth.obj",
	["playerOneModel"] = meshesLoadPath.."playerOnePrototypeModel.obj",
	["playerTwoModel"] = meshesLoadPath.."playerTwoPrototypeModel.obj",
}


diffuseTextures = 
{
	["brickTex"] = texturesLoadPath.."bricks.jpg",
	["carTex"] = texturesLoadPath.."carTex.png",
	["containerDiffuse"] = texturesLoadPath.."container2.png",
	["buildingTex"] = texturesLoadPath.."arenaDiffuse.png",
	["brickWall"] = texturesLoadPath.."wall.png",
	["goodBoyDiffuse"] = texturesLoadPath.."goodBoyDiffuse.png",
	["lavaDiffuse"] = texturesLoadPath.."lavaDiffuse.jpg",
	["iceDiffuse"] = texturesLoadPath.."iceDiffuse.jpg",
	["NeutralMat"] = texturesLoadPath.."neutralDiffuse.jpg",
	["player1ShadowDiffuse"] = texturesLoadPath.."player1ShadowDiffuse.png",
	["player2NeckDiffuse"] = texturesLoadPath.."player2NeckDiffuse.png",
	["catHeadDiffuse"] = texturesLoadPath.."catHeadTexture.png",
	["orbDiffuse"] = texturesLoadPath.."orbDiffuse.png",
}

specularTextures = 
{
	["containerSpecular"] = texturesLoadPath.."container2_specular.png",
	["buildingSpec"] = texturesLoadPath.."stuffSpec.png",
	["lavaSpecular"] = texturesLoadPath.."lavaSpecular.jpg",
	["iceSpecular"] = texturesLoadPath.."iceSpecular.jpg",
}

emissionTextures = 
{
	["lavaEmission"] = texturesLoadPath.."lavaEmission.jpg",
	["goodBoyEmission"] = texturesLoadPath.."goodBoyEmission.png",
	["iceEmission"] = texturesLoadPath.."iceEmission.jpg",
	["player1ShadowEmissive"] = texturesLoadPath.."player1ShadowEmissive.png",
	["player2NeckEmissive"] = texturesLoadPath.."player2NeckEmissive.png",
	["orbEmissive"] = texturesLoadPath.."orbEmissive.png",
}

--normal maps here
normalMapTextures = 
{
	["brickWallNormal"] = texturesLoadPath.."wallNormal.png",
	["lavaNormal"] = texturesLoadPath.."lavaNormal.jpg",
	["iceNormal"] = texturesLoadPath.."iceNormal.jpg",
	["wallNormal"] = texturesLoadPath.."wallNormal.png",
}

--Since we are using SFML for ui textures we need to load the sepperatly here!
sfmlTextures = 
{
	["brickTex"] = texturesLoadPath.."bricks.jpg",
	["playerOneInkText"] = texturesLoadPath.."playerInkText.png",
	["playerTwoInkText"] = texturesLoadPath.."playerInkText.png",
	["inkPlayerOne"] = texturesLoadPath.."iceFillBar.png",
	["inkPlayerTwo"] = texturesLoadPath.."lavaFillBar.png",
	["inkUIOverlay"] = texturesLoadPath.."inkUIOverlay.png",
	["inkUIBackground"] = texturesLoadPath.."inkUIBackground.png",

}

--Yes sound and music are 2 diffrent things...
--Sounds Are small clips that are played from a buffer in high quality ex: SFX
--Music are big chunks of memory that play music. This is used for music that loops or that is large
sounds = 
{
	["cannonShot"] = musicLoadPath.."cannonShot.wav",
	["iceAttack"] = musicLoadPath.."IceAttack.wav",
	["iceDeath"] = musicLoadPath.."IceDeath.wav",
	["lavaAttack"] = musicLoadPath.."LavaAttack.wav",
	["lavaDeath"] = musicLoadPath.."LavaDeath.wav",
}

musics =
{
	["expmusic"] = musicLoadPath.."expmusic.wav",
}