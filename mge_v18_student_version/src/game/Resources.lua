print("Hello LUA");

--DONT FORGET TO PUT A COMMA AFTER EVERY RESOURCE!!!

meshesLoadPath = "../assets/mge/models/"
texturesLoadPath = "../assets/mge/textures/"
fontsLoadPath = "../assets/mge/fonts/"
musicLoadPath = "../assets/mge/music/"

meshes = 
{
	["planeMesh"] = meshesLoadPath.."plane.obj",
	["cubeMesh"] = meshesLoadPath.."cube_smooth.obj",
	["cylinderMesh"] = meshesLoadPath.."cylinder_smooth.obj",
	["Sphere"] = meshesLoadPath.."sphere_smooth.obj",
	["GroundTile"] = meshesLoadPath.."GroundTile.obj",
	["players"] = meshesLoadPath.."players.obj",
	["orb"] = meshesLoadPath.."orb.obj",
	["Wall"] = meshesLoadPath.."WallBlock1x1.obj",






}


diffuseTextures = 
{
	["lavaDiffuse"] = texturesLoadPath.."lavaDiffuse.jpg",
	["iceDiffuse"] = texturesLoadPath.."iceDiffuse.jpg",
	["neutralDiffuse"] = texturesLoadPath.."neutralDiffuse.jpg",
	["playerIceDiffuse"] = texturesLoadPath.."playerIceDiffuse.jpg",
	["orbIceDiffuse"] = texturesLoadPath.."orbIceDiffuse.jpg",
	["iceDiffuse"] = texturesLoadPath.."iceDiffuse.jpg",
	["lavaDiffuse"] = texturesLoadPath.."lavaDiffuse.jpg",
	["wallDiffuse"] = texturesLoadPath.."wall.png",
	["playerLavaDiffuse"] = texturesLoadPath.."player2Diffuse.jpg",
	["orbLavaDiffuse"] = texturesLoadPath.."orbLavaDiffuse.jpg",

}

specularTextures = 
{
	["lavaSpecular"] = texturesLoadPath.."lavaSpecular.jpg",
	["iceSpecular"] = texturesLoadPath.."iceSpecular.jpg",
	["neutralSpecular"] = texturesLoadPath.."neutralSpecular.png",
}

emissionTextures = 
{
	["lavaEmission"] = texturesLoadPath.."lavaEmission.jpg",
	["iceEmission"] = texturesLoadPath.."iceEmission.jpg",
	["playerIceEmissive"] = texturesLoadPath.."playerIceEmissive.jpg",
	["orbIceEmissive"] = texturesLoadPath.."orbIceEmissive.jpg",
	["lavaEmission"] = texturesLoadPath.."lavaEmission.jpg",
	["iceEmission"] = texturesLoadPath.."iceEmission.jpg",
	["playerLavaEmissive"] = texturesLoadPath.."player2Emissive.jpg",
	["orbLavaEmissive"] = texturesLoadPath.."orbLavaEmissive.jpg",
}

--normal maps here
normalMapTextures = 
{
	["lavaNormal"] = texturesLoadPath.."lavaNormal.jpg",
	["iceNormal"] = texturesLoadPath.."iceNormal.jpg",
	["wallNormal"] = texturesLoadPath.."wallNormal.png",
}

--Since we are using SFML for ui textures we need to load the sepperatly here!
sfmlTextures = 
{
	--HUD
	["brickTex"] = texturesLoadPath.."bricks.jpg",
	["playerOneInkText"] = texturesLoadPath.."playerInkText.png",
	["playerTwoInkText"] = texturesLoadPath.."playerInkText.png",
	["inkPlayerOne"] = texturesLoadPath.."iceFillBar.png",
	["inkPlayerTwo"] = texturesLoadPath.."lavaFillBar.png",
	["inkUIOverlay"] = texturesLoadPath.."inkUIOverlay.png",
	["inkUIBackground"] = texturesLoadPath.."inkUIBackground.png",

	--MENU
	["menuBG"] = texturesLoadPath.."background.png",
	["playSelected"] = texturesLoadPath.."playSelected.png",
	["controlsSelected"] = texturesLoadPath.."controlsSelected.png",
	["exitSelected"] = texturesLoadPath.."exitSelected.png",

}

sfmlFonts =
{
	["theBoldFont"] = fontsLoadPath.."theboldfont.ttf",
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