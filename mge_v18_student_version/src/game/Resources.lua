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
	["suzanna"] = meshesLoadPath.. "suzanna_smooth.obj",
	["Sphere"] = meshesLoadPath.."sphere_smooth.obj",
	["GroundTile"] = meshesLoadPath.."GroundTile.obj",
	["players"] = meshesLoadPath.."players.obj",
	["orb"] = meshesLoadPath.."orb.obj",
	["refillStation"] = meshesLoadPath.."refillStation.obj",
	["balloon"] = meshesLoadPath.."Balloon.obj",
	["cannon"] = meshesLoadPath.."cannon.obj",


	--walls

	["WallBlock1x1"] = meshesLoadPath.."WallBlock1x1.obj",
	["WallBlock2x2"] = meshesLoadPath.."WallBlock2x2.obj",
	["wall_msingle"] = meshesLoadPath.."wall_msingle.obj",
	["wall_ocorner"] = meshesLoadPath.."wall_ocorner.obj",
	["wall_icorner"] = meshesLoadPath.."wall_icorner.obj",
	["wall_flat"] = meshesLoadPath.."wall_flat.obj",
	["wall_single"] = meshesLoadPath.."wall_single.obj",

	["bigTemple"] = meshesLoadPath.. "BackgroundModels/bigTemple.obj",
	["borderLeft"] = meshesLoadPath.. "BackgroundModels/borderLeft.obj",
	["borderRight"] = meshesLoadPath.. "BackgroundModels/borderRight.obj",
	["bottomBorder"] = meshesLoadPath.. "BackgroundModels/bottomBorder.obj",
	["bush1"] = meshesLoadPath.. "BackgroundModels/bush1.obj",
	["bush2"] = meshesLoadPath.. "BackgroundModels/bush2.obj",
	["cornerPillar"] = meshesLoadPath.. "BackgroundModels/cornerPillar.obj",
	["refillPoint"] = meshesLoadPath.. "BackgroundModels/refillPoint.obj",
	["rocks"] = meshesLoadPath.. "BackgroundModels/rocks.obj",
	["sidePillar"] = meshesLoadPath.. "BackgroundModels/sidePillar.obj",
	["sideTemple"] = meshesLoadPath.. "BackgroundModels/sideTemple.obj",
	["statue"] = meshesLoadPath.. "BackgroundModels/statue.obj",
	--["templeBackground"] = meshesLoadPath.. "BackgroundModels/templeBackground.obj",
	["topBorder"] = meshesLoadPath.. "BackgroundModels/topBorder.obj",
	["topBorderDetail"] = meshesLoadPath.. "BackgroundModels/topBorderDetail.obj",
	["tree1"] = meshesLoadPath.. "BackgroundModels/tree1.obj",
	["respawnPointIce"] = meshesLoadPath.. "BackgroundModels/respawnPointIce.obj",
	["tree2"] = meshesLoadPath.. "BackgroundModels/tree2.obj",
	["respawnPointLava"] = meshesLoadPath.. "BackgroundModels/respawnPointLava.obj",
 



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
	["cannonDiffuse"] = texturesLoadPath.."cannonDiffuse.jpg",
	["topBorderDetailDiffuse"] = texturesLoadPath.."topBorderDetailDiffuse.jpg",
	["bigTempleDiffuse"] = texturesLoadPath.."bigTempleDiffuse.jpg",


	--walls

	["WallBlock1x1Diffuse"] = texturesLoadPath.."WallBlock1x1Diffuse.jpg",
	["WallBlock2x2Diffuse"] = texturesLoadPath.."WallBlock2x2Diffuse.jpg",
	["wall_msingleDiffuse"] = texturesLoadPath.."wall_msingleDiffuse.jpg",
	["wall_ocornerDiffuse"] = texturesLoadPath.."wall_ocornerDiffuse.jpg",
	["wall_icornerDiffuse"] = texturesLoadPath.."wall_icornerDiffuse.jpg",
	["wall_flatDiffuse"] = texturesLoadPath.."wall_flatDiffuse.jpg",
	["wall_singleDiffuse"] = texturesLoadPath.."wall_singleDiffuse.jpg",
	

	--backgroundDiffuse


	["borderLeftDiffuse"] = texturesLoadPath.."BackgroundTextures/borderLeftDiffuse.jpg",
	["borderRightDiffuse"] = texturesLoadPath.."BackgroundTextures/borderRightDiffuse.jpg",
	["bottomBorderDiffuse"] = texturesLoadPath.."BackgroundTextures/bottomBorderDiffuse.jpg",
	["bush1Diffuse"] = texturesLoadPath.."BackgroundTextures/bush1Diffuse.jpg",
	["respawnPointDiffuse"] = texturesLoadPath.."BackgroundTextures/respawnPointDiffuse.jpg",
	["sidePillarDiffuse"] = texturesLoadPath.."BackgroundTextures/sidePillarDiffuse.jpg",
	["statueDiffuse"] = texturesLoadPath.."BackgroundTextures/statueDiffuse.jpg",
	["topBorderDiffuse"] = texturesLoadPath.."BackgroundTextures/topBorderDiffuse.jpg",
	["tree1Diffuse"] = texturesLoadPath.."BackgroundTextures/tree1Diffuse.jpg",
	["tree2Diffuse"] = texturesLoadPath.."BackgroundTextures/tree2Diffuse.jpg",
	["sideTempleBlueDiffuse"] = texturesLoadPath.."BackgroundTextures/sideTempleBlueDiffuse.jpg",
	["sideTempleRedDiffuse"] = texturesLoadPath.."BackgroundTextures/sideTempleRedDiffuse.jpg",
	["cornerPillarDiffuse"] = texturesLoadPath.."BackgroundTextures/cornerPillarDiffuse.jpg",
	["rocksLightDiffuse"] = texturesLoadPath.."BackgroundTextures/rocksLightDiffuse.jpg",
	["rocksMediumDiffuse"] = texturesLoadPath.."BackgroundTextures/rocksMediumDiffuse.jpg",
	["rocksDarkDiffuse"] = texturesLoadPath.."BackgroundTextures/rocksDarkDiffuse.jpg",

	
	["iceSelectionDiffuse"] = texturesLoadPath.."iceSelectionDiffuse.jpg",
	["lavaSelectionDiffuse"] = texturesLoadPath.."lavaSelectedDiffuse.jpg",


	


}

specularTextures = 
{
	["lavaSpecular"] = texturesLoadPath.."lavaSpecular.jpg",
	["iceSpecular"] = texturesLoadPath.."iceSpecular.jpg",
	["neutralSpecular"] = texturesLoadPath.."neutralSpecular.jpg",
	["playerLavaSpecular"] = texturesLoadPath.."playerLavaSpecular.jpg",
	["playerIceSpecular"] = texturesLoadPath.."playerIceSpecular.jpg",
	["playerLavaSpecular"] = texturesLoadPath.."playerLavaSpecular.jpg",
	["refillStationSpecular"] = texturesLoadPath.."refillStationSpecular.jpg",
	["BalloonSpecular"] = texturesLoadPath.."BalloonSpecular.png",
	["cannonSpecular"] = texturesLoadPath.."cannonSpecular.jpg",
	["topBorderDetailSpecular"] = texturesLoadPath.."topBorderDetailSpecular.jpg",
	["bigTempleSpecular"] = texturesLoadPath.."bigTempleSpecular.jpg",


	--walls

	["WallBlock1x1Specular"] = texturesLoadPath.."WallBlock1x1Specular.jpg",
	["WallBlock2x2Specular"] = texturesLoadPath.."WallBlock2x2Specular.jpg",
	["wall_msingleSpecular"] = texturesLoadPath.."wall_msingleSpecular.jpg",
	["wall_ocornerSpecular"] = texturesLoadPath.."wall_ocornerSpecular.jpg",
	["wall_icornerSpecular"] = texturesLoadPath.."wall_icornerSpecular.jpg",
	["wall_flatSpecular"] = texturesLoadPath.."wall_flatSpecular.jpg",
	["wall_singleSpecular"] = texturesLoadPath.."wall_singleSpecular.jpg",

	--backgroundSpecular

	["bush1Specular"] = texturesLoadPath.."BackgroundTextures/bush1Specular.jpg",
	["respawnPointIceSpecular"] = texturesLoadPath.."BackgroundTextures/respawnPointIceSpecular.jpg",
	["respawnPointLavaSpecular"] = texturesLoadPath.."BackgroundTextures/respawnPointLavaSpecular.jpg",
	["statueSpecular"] = texturesLoadPath.."BackgroundTextures/statueSpecular.jpg",
	["tree1Specular"] = texturesLoadPath.."BackgroundTextures/tree1Specular.jpg",
	["tree2Specular"] = texturesLoadPath.."BackgroundTextures/tree2Specular.jpg",
	["sideTempleRedSpecular"] = texturesLoadPath.."BackgroundTextures/sideTempleRedSpecular.jpg",
	["sideTempleBlueSpecular"] = texturesLoadPath.."BackgroundTextures/sideTempleBlueSpecular.jpg",
	



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
	["cannonEmission"] = texturesLoadPath.."cannonEmission.jpg",
	["cannonRedEmission"] = texturesLoadPath.."cannonRedEmission.jpg",
	["cannonBlueEmission"] = texturesLoadPath.."cannonBlueEmission.jpg",
	["bigTempleEmission"] = texturesLoadPath.."bigTempleEmission.jpg",
	["statueEmission"] = texturesLoadPath.."statueEmission.jpg",

	--backgroundEmission


	["borderLeftEmission"] = texturesLoadPath.."BackgroundTextures/borderLeftEmission.jpg",
	["borderRightEmission"] = texturesLoadPath.."BackgroundTextures/borderRightEmission.jpg",
	["respawnPointIceEmission"] = texturesLoadPath.."BackgroundTextures/respawnPointIceEmission.jpg",
	["respawnPointLavaEmission"] = texturesLoadPath.."BackgroundTextures/respawnPointLavaEmission.jpg",
	["sideTempleRedEmission"] = texturesLoadPath.."BackgroundTextures/sideTempleRedEmission.jpg",
	["sideTempleBlueEmission"] = texturesLoadPath.."BackgroundTextures/sideTempleBlueEmission.jpg",


	["iceSelectionEmission"] = texturesLoadPath.."iceSelectionEmission.jpg",
	["lavaSelectionEmission"] = texturesLoadPath.."lavaSelectedEmission.jpg",
}

--normal maps here
normalMapTextures = 
{
	["lavaNormal"] = texturesLoadPath.."lavaNormal.jpg",
	["iceNormal"] = texturesLoadPath.."iceNormal.jpg",
	["wallNormal"] = texturesLoadPath.."wallNormal.png",
	["neutralNormal"] = texturesLoadPath.."neutralNormal.jpg",
	["refillStation"] = texturesLoadPath.."refillStationNormal.jpg",
	["topBorderDetailNormal"] = texturesLoadPath.."topBorderDetailNormal.jpg",
	["bigTempleNormal"] = texturesLoadPath.."bigTempleNormal.jpg",

	--walls

	["WallBlock1x1Normal"] = texturesLoadPath.."WallBlock1x1Normal.jpg",
	["WallBlock2x2Normal"] = texturesLoadPath.."WallBlock2x2Normal.jpg",
	["wall_msingleNormal"] = texturesLoadPath.."wall_msingleNormal.jpg",
	["wall_ocornerNormal"] = texturesLoadPath.."wall_ocornerNormal.jpg",
	["wall_icornerNormal"] = texturesLoadPath.."wall_icornerNormal.jpg",
	["wall_flatNormal"] = texturesLoadPath.."wall_flatNormal.jpg",
	["wall_singleNormal"] = texturesLoadPath.."wall_singleNormal.jpg",

	--backgroundNormal



	["borderLeftNormal"] = texturesLoadPath.."BackgroundTextures/borderLeftNormal.jpg",
	["borderRightNormal"] = texturesLoadPath.."BackgroundTextures/borderRightNormal.jpg",
	["bottomBorderNormal"] = texturesLoadPath.."BackgroundTextures/bottomBorderNormal.jpg",
	["cornerPillarNormal"] = texturesLoadPath.."BackgroundTextures/cornerPillarNormal.jpg",
	["respawnPointIceNormal"] = texturesLoadPath.."BackgroundTextures/respawnPointIceNormal.jpg",
	["respawnPointLavaNormal"] = texturesLoadPath.."BackgroundTextures/respawnPointLavaNormal.jpg",
	["sidePillarNormal"] = texturesLoadPath.."BackgroundTextures/sidePillarNormal.jpg",
	["sideTempleRedNormal"] = texturesLoadPath.."BackgroundTextures/sideTempleRedNormal.jpg",
	["sideTempleBlueNormal"] = texturesLoadPath.."BackgroundTextures/sideTempleBlueNormal.jpg",
	["statueNormal"] = texturesLoadPath.."statueNormal.jpg",
	

	

	



}

--Since we are using SFML for ui textures we need to load the sepperatly here!
sfmlTextures = 
{
	--HUD
	["brickTex"] = texturesLoadPath.."bricks.jpg",
	["playerOneInkText"] = texturesLoadPath.."playerInkText.png",
	["playerTwoInkText"] = texturesLoadPath.."playerInkText.png",
	["iceFillBar"] = texturesLoadPath.."iceFillBar.png",
	["lavaFillBar"] = texturesLoadPath.."lavaFillBar.png",
	["inkUIOverlay"] = texturesLoadPath.."inkUIOverlay.png",
	["inkUIBackground"] = texturesLoadPath.."inkUIBackground.png",
	["percentageLavaBar"] = texturesLoadPath.."percentageLavaBar.png",
	["percentageIceBar"] = texturesLoadPath.."percentageIceBar.png",

	--MENU
	["menuBG"] = texturesLoadPath.."background.png",
	["playSelected"] = texturesLoadPath.."playSelected.png",
	["controlsSelected"] = texturesLoadPath.."controlsSelected.png",
	["exitSelected"] = texturesLoadPath.."exitSelected.png",
	["controlsScreen"] = texturesLoadPath.."controlsScreen.png",
	["controlsScreenPressed"] = texturesLoadPath.."controlsScreenPressed.png",

	["levelSelectedNone"] = texturesLoadPath.."levelSelectedNone.png",
	["levelSelected1"] = texturesLoadPath.."levelSelected1.png",
	["levelSelected2"] = texturesLoadPath.."levelSelected2.png",
	["levelSelectedBack"] = texturesLoadPath.."levelSelectedBack.png",

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
	["balloonExplode"] = musicLoadPath.."BalloonExplode.wav",
	["cannonShot"] = musicLoadPath.."CanonShot.wav",
	["iceAttack"] = musicLoadPath.."IceAttack.wav",
	--["iceCharge"] = musicLoadPath.."iceCharge.wav",
	["iceDeath"] = musicLoadPath.."IceDeath.wav",
	["lavaAttack"] = musicLoadPath.."LavaAttack.wav",
	--["lavaCharge"] = musicLoadPath.."LavaCharge.wav",
	["lavaDeath"] = musicLoadPath.."LavaDeath.wav",
	--["noAmmo"] = musicLoadPath.."Outofammo.wav",
	["refillSound"] = musicLoadPath.."refilling.wav",
	
	["playerRespawnSound"] = musicLoadPath.."Respawn.wav",
	["briskWins"] = musicLoadPath.."briskWins.wav",
	["blazeWins"] = musicLoadPath.."blazeWins.wav",

	["pressingButton"] = musicLoadPath.."PressingButton.wav",
	["selectingButton"] = musicLoadPath.."SelectingButtons.wav",

}

musics =
{
	--["expmusic"] = musicLoadPath.."expmusic.wav",
	["menuMusic"] = musicLoadPath.."MenuMusic.wav",
	["levelMusic"] = musicLoadPath.."Music2Minutes.wav",
}