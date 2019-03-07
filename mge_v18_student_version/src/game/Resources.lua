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
	["refillStation"] = meshesLoadPath.."refillStation.obj",
	["balloon"] = meshesLoadPath.."Balloon.obj",


	--walls

	["WallBlock1x1"] = meshesLoadPath.."WallBlock1x1.obj",
	["WallBlock2x2"] = meshesLoadPath.."WallBlock2x2.obj",
	["wall_msingle"] = meshesLoadPath.."wall_msingle.obj",
	["wall_ocorner"] = meshesLoadPath.."wall_ocorner.obj",
	["wall_icorner"] = meshesLoadPath.."wall_icorner.obj",
	["wall_flat"] = meshesLoadPath.."wall_flat.obj",
	["wall_single"] = meshesLoadPath.."wall_single.obj",








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
	["playerLavaDiffuse"] = texturesLoadPath.."playerLavaDiffuse.jpg",
	["orbLavaDiffuse"] = texturesLoadPath.."orbLavaDiffuse.jpg",
	["refillStationDiffuse"] = texturesLoadPath.."refillStationDiffuse.jpg",
	["BalloonDiffuse"] = texturesLoadPath.."BalloonDiffuse.png",

	--walls

	["WallBlock1x1Diffuse"] = texturesLoadPath.."WallBlock1x1Diffuse.jpg",
	["WallBlock2x2Diffuse"] = texturesLoadPath.."WallBlock2x2Diffuse.jpg",
	["wall_msingleDiffuse"] = texturesLoadPath.."wall_msingleDiffuse.jpg",
	["wall_ocornerDiffuse"] = texturesLoadPath.."wall_ocornerDiffuse.jpg",
	["wall_icornerDiffuse"] = texturesLoadPath.."wall_icornerDiffuse.jpg",
	["wall_flatDiffuse"] = texturesLoadPath.."wall_flatDiffuse.jpg",
	["wall_singleDiffuse"] = texturesLoadPath.."wall_singleDiffuse.jpg",

}

specularTextures = 
{
	["lavaSpecular"] = texturesLoadPath.."lavaSpecular.jpg",
	["iceSpecular"] = texturesLoadPath.."iceSpecular.jpg",
	["neutralSpecular"] = texturesLoadPath.."neutralSpecular.jpg",
	["playerLavaSpecular"] = texturesLoadPath.."playerLavaSpecular.jpg",
	["playerIceSpecular"] = texturesLoadPath.."playerIceSpecular.jpg",
	["playerLavaSpecular"] = texturesLoadPath.."playerLavaSpecular.jpg",
	["refillStationSpecular"] = meshesLoadPath.."refillStationSpecular.jpg",
	["BalloonSpecular"] = texturesLoadPath.."BalloonSpecular.png",

	--walls

	["WallBlock1x1Specular"] = meshesLoadPath.."WallBlock1x1Specular.jpg",
	["WallBlock2x2Specular"] = meshesLoadPath.."WallBlock2x2Specular.jpg",
	["wall_msingleSpecular"] = meshesLoadPath.."wall_msingleSpecular.jpg",
	["wall_ocornerSpecular"] = meshesLoadPath.."wall_ocornerSpecular.jpg",
	["wall_icornerSpecular"] = meshesLoadPath.."wall_icornerSpecular.jpg",
	["wall_flatSpecular"] = meshesLoadPath.."wall_flatSpecular.jpg",
	["wall_singleSpecular"] = meshesLoadPath.."wall_singleSpecular.jpg",

}

emissionTextures = 
{
	["lavaEmission"] = texturesLoadPath.."lavaEmission.jpg",
	["iceEmission"] = texturesLoadPath.."iceEmission.jpg",
	["playerIceEmissive"] = texturesLoadPath.."playerIceEmissive.jpg",
	["orbIceEmissive"] = texturesLoadPath.."orbIceEmissive.jpg",
	["lavaEmission"] = texturesLoadPath.."lavaEmission.jpg",
	["iceEmission"] = texturesLoadPath.."iceEmission.jpg",
	["playerLavaEmissive"] = texturesLoadPath.."playerLavaEmissive.jpg",
	["orbLavaEmissive"] = texturesLoadPath.."orbLavaEmissive.jpg",
	["refillStationEmission"] = texturesLoadPath.."refillStationEmission.jpg",
	["BalloonEmission"] = texturesLoadPath.."BalloonEmission.png",
}

--normal maps here
normalMapTextures = 
{
	["lavaNormal"] = texturesLoadPath.."lavaNormal.jpg",
	["iceNormal"] = texturesLoadPath.."iceNormal.jpg",
	["wallNormal"] = texturesLoadPath.."wallNormal.png",
	["neutralNormal"] = texturesLoadPath.."neutralNormal.jpg",
	["refillStation"] = texturesLoadPath.."refillStationNormal.jpg",

	--walls

	["WallBlock1x1Normal"] = meshesLoadPath.."WallBlock1x1Normal.jpg",
	["WallBlock2x2Normal"] = meshesLoadPath.."WallBlock2x2Normal.jpg",
	["wall_msingleNormal"] = meshesLoadPath.."wall_msingleNormal.jpg",
	["wall_ocornerNormal"] = meshesLoadPath.."wall_ocornerNormal.jpg",
	["wall_icornerNormal"] = meshesLoadPath.."wall_icornerNormal.jpg",
	["wall_flatNormal"] = meshesLoadPath.."wall_flatNormal.jpg",
	["wall_singleNormal"] = meshesLoadPath.."wall_singleNormal.jpg",
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
	["controlsScreen"] = texturesLoadPath.."controlsScreen.png",
	["controlsScreenPressed"] = texturesLoadPath.."controlsScreenPressed.png",

	--RESO
	["blazePrevails"] = texturesLoadPath.."blazePrevails.png",
	["briskPrevails"] = texturesLoadPath.."briskPrevails.png",
	["draw"] = texturesLoadPath.."draw.png",

	["resoLavaBar"] = texturesLoadPath.."resoLavaBar.png",
	["resoIceBar"] = texturesLoadPath.."resoIceBar.png",
	["scoreBarBG"] = texturesLoadPath.."scoreBarBG.png";
	["scoreBarOverlay"] = texturesLoadPath.."scoreBarOverlay.png",

	["resoNone"] = texturesLoadPath.."resoNone.png",
	["resoReplay"] = texturesLoadPath.."resoReplay.png",
	["resoMenu"] = texturesLoadPath.."resoMenu.png",
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