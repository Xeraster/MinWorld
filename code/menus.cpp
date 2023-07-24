void setupMainMenu()
{
    textSizeSmall = 8 * gscreenx / 800;
    textSizeMedium = 12 * gscreenx / 800;
    textSizeLarge = 18 * gscreenx / 800;

    //main menu buttons
    mainMenu_newGame = button("New Game", color(255, 255, 255), 45, 200, textSizeMedium);
    mainMenu_newGame.setBorder(true);

    mainMenu_loadGame = button("Load Game", color(255, 255, 255), 45, mainMenu_newGame.sizeY() + mainMenu_newGame.posY() + 10, textSizeMedium);
    mainMenu_loadGame.setBorder(true);

    mainMenu_mods = button("Mods", color(255, 255, 255), 45, mainMenu_loadGame.sizeY() + mainMenu_loadGame.posY() + 10, textSizeMedium);
    mainMenu_mods.setBorder(true);

    mainMenu_settings = button("Settings", color(255, 255, 255), 45, mainMenu_mods.sizeY() + mainMenu_mods.posY() + 10, textSizeMedium);
    mainMenu_settings.setBorder(true);

    mainMenu_quitGame = button("Quit", color(255, 255, 255), 45, mainMenu_settings.sizeY() + mainMenu_settings.posY() + 10, textSizeMedium);
    mainMenu_quitGame.setBorder(true);

    //main menu screen1/2 buttons
    mainScreen1Next = button("Next", color(255, 255, 255), 0, 0, textSizeMedium);
    mainScreen1Back = button("Back", color(255, 255, 255), 0, 0, textSizeMedium);
    mainScreen1Back.setPos(20, gscreeny - mainScreen1Next.sizeY() - 20);
    mainScreen1Next.setPos(gscreenx - mainScreen1Next.sizeX() - 20, mainScreen1Back.posY());
    mainScreen1Back.setBorder(true);
    mainScreen1Next.setBorder(true);

    //screen1 specific ui elements
    startingPawns = sideScroll(200 * gscreenx / 800, 200 * gscreeny / 600, textSizeMedium, 8);
    aiIqbar = sideScroll(200 * gscreenx / 800, startingPawns.posY() + startingPawns.sizeY() + getTextYSize(textSizeMedium) + 4, textSizeMedium, 8);
    difficultyBar = sideScroll(200 * gscreenx / 800, aiIqbar.posY() + aiIqbar.sizeY() + getTextYSize(textSizeMedium) + 4, textSizeMedium, 8);

    for (int i = 0; i < 8; i++)
    {
        startingPawns.addItem(to_string(i+1));
    }

    aiIqbar.addItem("dumb");
    aiIqbar.addItem("normal");

    difficultyBar.addItem("default");

    //main menu screen2 specific elements
    //planetSeedBox("test label", color(255,255,255), 200, 200, textSizeMedium, 10);
    planetSeedBox = textbox("test label", color(255, 255, 255), 100 * gscreenx / 800, 100 * gscreeny / 600, textSizeMedium, 10);
    randomizeSeedButton = button("randomize", color(255, 150, 150), planetSeedBox.posX() + planetSeedBox.sizeX(), planetSeedBox.posY(), textSizeMedium);
    planetSizeSideScroll = sideScroll(planetSeedBox.posX(), planetSeedBox.posY() + planetSeedBox.sizeY() + getTextYSize(textSizeMedium) + 5, textSizeMedium, 10);
    planetSizeSideScroll.addItem("100 x 100");

    planetTempSlider = slider(color(255, 255, 255), planetSizeSideScroll.posX(), planetSizeSideScroll.posY() + planetSizeSideScroll.sizeY() + getTextYSize(textSizeMedium), 200 * gscreenx / 800, 20 * gscreeny / 600);
    planetOrbitEccentricity = slider(color(255, 255, 255), planetTempSlider.posX(), planetTempSlider.posY() + planetTempSlider.sizeY() + getTextYSize(textSizeMedium), 200 * gscreenx / 800, 20 * gscreeny / 600);
    planetAxialTilt = slider(color(255, 255, 255), planetOrbitEccentricity.posX(), planetOrbitEccentricity.posY() + planetOrbitEccentricity.sizeY() + getTextYSize(textSizeMedium), 200 * gscreenx / 800, 20 * gscreeny / 600);
    planetWaterAbundance = slider(color(255, 255, 255), planetAxialTilt.posX(), planetAxialTilt.posY() + planetAxialTilt.sizeY() + getTextYSize(textSizeMedium), 200 * gscreenx / 800, 20 * gscreeny / 600);
    planetPopulation = slider(color(255, 255, 255), planetWaterAbundance.posX(), planetWaterAbundance.posY() + planetWaterAbundance.sizeY() + getTextYSize(textSizeMedium), 200 * gscreenx / 800, 20 * gscreeny / 600);
}

void drawMainMenu(int mouseX, int mouseY, int lastMouse)
{
    if (mainMenu_newGame.draw(ren, mouseX, mouseY, lastMouse, tex))
    {
        atMainMenu = false;
        newGameScreen1 = true;
        newGameScreen2 = false;
    }
    mainMenu_loadGame.draw(ren, mouseX, mouseY, lastMouse, tex);
    mainMenu_mods.draw(ren, mouseX, mouseY, lastMouse, tex);
    mainMenu_settings.draw(ren, mouseX, mouseY, lastMouse, tex);
    mainMenu_quitGame.draw(ren, mouseX, mouseY, lastMouse, tex);
}

void drawNewgameScreen1(int mouseX, int mouseY, int lastMouse)
{
    /*menu mockup design (I hate and suck at ui design) calls for:
    1 vertical scroll view
    1 readonly text box/label
    3 "sidescroll" elements
    2 buttons
    */
    startingPawns.draw(ren, mouseX, mouseY, lastMouse);
    aiIqbar.draw(ren, mouseX, mouseY, lastMouse);
    difficultyBar.draw(ren, mouseX, mouseY, lastMouse);

    //draw the label text right above the starting pawn side scroll ui element
    drawText(ren, textSizeMedium, color(255, 255, 255), "Starting crew:", startingPawns.posX(), startingPawns.posY() - getTextYSize(textSizeMedium) - 2);

    //draw the label text right above the ai intelligence side scroll ui element
    drawText(ren, textSizeMedium, color(255, 255, 255), "AI intelligence:", aiIqbar.posX(), aiIqbar.posY() - getTextYSize(textSizeMedium) - 2);

    //draw the label text right above the difficulty side scroll ui element
    drawText(ren, textSizeMedium, color(255, 255, 255), "Difficulty:", difficultyBar.posX(), difficultyBar.posY() - getTextYSize(textSizeMedium) - 2);

    drawText(ren, textSizeSmall, color(255, 255, 255), "starting scenario and options", 200, 20);
    if (mainScreen1Back.draw(ren, mouseX, mouseY, lastMouse, tex))
    {
        atMainMenu = true;
        newGameScreen1 = false;
        newGameScreen2 = false;
    }

    if (mainScreen1Next.draw(ren, mouseX, mouseY, lastMouse, tex))
    {
        //create a new planet with the specifiec settings
        playerData.setPlanet(&newPlanet);

        atMainMenu = false;
        newGameScreen1 = false;
        newGameScreen2 = true;
    }
}

void drawNewgameScreen2(int mouseX, int mouseY, int lastMouse)
{
    /*menu mockup design for this screen calls for:
    1 r/w textbox
    1 "sidescroll" element
    5 horizontal sliders
    1 image preview block
    1 vertical scrollview
    */

   //draw all the sliders and their labels
    drawText(ren, textSizeMedium, color(255, 255, 255), "planet temperature:", planetTempSlider.posX(), planetTempSlider.posY() - 2 - getTextYSize(textSizeMedium));
    planetTempSlider.draw(ren, mouseX, mouseY, lastMouse);
    drawText(ren, textSizeMedium, color(255, 255, 255), "orbit eccentricity", planetOrbitEccentricity.posX(), planetOrbitEccentricity.posY() - 2 - getTextYSize(textSizeMedium));
    planetOrbitEccentricity.draw(ren, mouseX, mouseY, lastMouse);
    drawText(ren, textSizeMedium, color(255, 255, 255), "axial tilt", planetAxialTilt.posX(), planetAxialTilt.posY() - 2 - getTextYSize(textSizeMedium));
    planetAxialTilt.draw(ren, mouseX, mouseY, lastMouse);
    drawText(ren, textSizeMedium, color(255, 255, 255), "water", planetWaterAbundance.posX(), planetWaterAbundance.posY() - 2 - getTextYSize(textSizeMedium));
    planetWaterAbundance.draw(ren, mouseX, mouseY, lastMouse);
    drawText(ren, textSizeMedium, color(255, 255, 255), "population", planetPopulation.posX(), planetPopulation.posY() - 2 - getTextYSize(textSizeMedium));
    planetPopulation.draw(ren, mouseX, mouseY, lastMouse);

    //convert user slider data to data that can be used to show planet stats
    string planetTempString = to_string((planetTempSlider.getValue()*8.0f)-4.0f);//planet temp adjusts the global average planet temperature
    string yearLengthString = to_string((planetOrbitEccentricity.getValue()*60)+60);//orbit eccentricity modifies year length
    string axialTiltString = to_string(planetAxialTilt.getValue());//water body coverage of planet
    string waterCoverageString = to_string(planetWaterAbundance.getValue());
    string globalPopulationString = to_string(planetPopulation.getValue());


    //draw a quick reference planet stats box
    drawText(ren, textSizeSmall, color(255, 255, 255), "Global avg. temperature: "+planetTempString, randomizeSeedButton.posX() + randomizeSeedButton.sizeX() + 20, 100 * gscreeny / 600);
    drawText(ren, textSizeSmall, color(255, 255, 255), "Year length: "+yearLengthString, randomizeSeedButton.posX() + randomizeSeedButton.sizeX() + 20, (100 * gscreeny / 600) + getTextYSize(textSizeSmall));
    drawText(ren, textSizeSmall, color(255, 255, 255), "Water coverage: "+waterCoverageString, randomizeSeedButton.posX() + randomizeSeedButton.sizeX() + 20, (100 * gscreeny / 600) + (getTextYSize(textSizeSmall)*2));
    drawText(ren, textSizeSmall, color(255, 255, 255), "Global population: "+globalPopulationString, randomizeSeedButton.posX() + randomizeSeedButton.sizeX() + 20, (100 * gscreeny / 600) + (getTextYSize(textSizeSmall)*3));

    //draw the text label for the planet seed text box
    drawText(ren, textSizeMedium, color(255, 255, 255), "Planet seed:", planetSeedBox.posX(), planetSeedBox.posY() - getTextYSize(textSizeMedium) - 2);
    planetSeedBox.draw(ren, mouseX, mouseY, lastMouse);

    //if randomize button clicked, fill the planet seed box with a random value
    if (randomizeSeedButton.draw(ren, mouseX, mouseY, lastMouse, nullptr))
    {
        int randomSeed = betterRand(time(0) + additionalSalt) % 1000000;
        planetSeedBox.replaceText(to_string(randomSeed));
        additionalSalt++;
    }

    //draw the text label for the planet size selector
    drawText(ren, textSizeMedium, color(255, 255, 255), "Planet size:", planetSizeSideScroll.posX(), planetSizeSideScroll.posY() - getTextYSize(textSizeMedium) - 5);
    planetSizeSideScroll.draw(ren, mouseX, mouseY, lastMouse);

    drawText(ren, textSizeSmall, color(255, 255, 255), "planet settings", 200, 20);
    if (mainScreen1Back.draw(ren, mouseX, mouseY, lastMouse, tex))
    {
        atMainMenu = false;
        newGameScreen1 = true;
        newGameScreen2 = false;
    }

    if (mainScreen1Next.draw(ren, mouseX, mouseY, lastMouse, tex))
    {
        //go to next menu screen
        //atMainMenu = false;
        //newGameScreen1 = true;
        //newGameScreen2 = false;

        //the game starts after this button
        //generate the planet based on inputs
        double globalAvgTemp = (planetTempSlider.getValue()*8.0f)-4.0f;
        double yearLength = (planetOrbitEccentricity.getValue()*60)+60;
        double axialTilt = planetAxialTilt.getValue()*50;
        double waterCoverage = planetWaterAbundance.getValue();
        double population = planetPopulation.getValue();

        cout << "main menu fuck poop" << endl;
        newPlanet = planet(stoi(planetSeedBox.text()), globalAvgTemp, yearLength, axialTilt, waterCoverage, population);//bro where tf is the seed stored on the main menu 2 screen? nvm found it

        normalInGame = true;

    }
    
}

void drawMenus(int mouseX, int mouseY, int lastMouse)
{
    if (atMainMenu)
    {
        drawMainMenu(mouseX, mouseY, lastMouse);
    }
    else if (newGameScreen1)
    {
        drawNewgameScreen1(mouseX, mouseY, lastMouse);
    }
    else if (newGameScreen2)
    {
        drawNewgameScreen2(mouseX, mouseY, lastMouse);
    }
}

//initialize handles all the one-time setups for the ui elements
void ui_initialize()
{

}

//resize handles all the setup for the ui elements taht have to be rerun every time the screen resolution changes
void on_resize()
{
    textSizeSmall = 8 * gscreeny / 600;
    textSizeMedium = 12 * gscreeny / 600;
    textSizeLarge = 18 * gscreeny / 600;

    //first set all the font sizes to the new values
    mainMenu_newGame.setFontSize(textSizeMedium);
    mainMenu_loadGame.setFontSize(textSizeMedium);
    mainMenu_mods.setFontSize(textSizeMedium);
    mainMenu_settings.setFontSize(textSizeMedium);
    mainMenu_quitGame.setFontSize(textSizeMedium);

    //next set the button positions so that they are correcrtly positioned after resize
    mainMenu_newGame.setPos(45, 200);
    mainMenu_loadGame.setPos(45, mainMenu_newGame.sizeY() + mainMenu_newGame.posY() + 10);
    mainMenu_mods.setPos(45, mainMenu_loadGame.sizeY() + mainMenu_loadGame.posY() + 10);
    mainMenu_settings.setPos(45, mainMenu_mods.sizeY() + mainMenu_mods.posY() + 10);
    mainMenu_quitGame.setPos(45, mainMenu_settings.sizeY() + mainMenu_settings.posY() + 10);

    mainScreen1Next.setFontSize(textSizeMedium);
    mainScreen1Back.setFontSize(textSizeMedium);
    mainScreen1Back.setPos(20, gscreeny - mainScreen1Next.sizeY() - 20);
    mainScreen1Next.setPos(gscreenx - mainScreen1Next.sizeX() - 20, mainScreen1Back.posY());

    //screen1 specific ui elements
    //startingPawns = sideScroll(200 * gscreenx / 800, 200 * gscreeny / 600, textSizeMedium, 8);
    //aiIqbar = sideScroll(200 * gscreenx / 800, startingPawns.posY() + startingPawns.sizeY() + textSizeMedium, textSizeMedium, 10);

    startingPawns.setPos(200 * gscreenx / 800, 200 * gscreeny / 600);
    aiIqbar.setPos(200 * gscreenx / 800, startingPawns.posY() + startingPawns.sizeY() + getTextYSize(textSizeMedium) + 4);
    difficultyBar.setPos(200 * gscreenx / 800, aiIqbar.posY() + aiIqbar.sizeY() + getTextYSize(textSizeMedium) + 4);
    startingPawns.setFontSize(textSizeMedium);
    aiIqbar.setFontSize(textSizeMedium);
    difficultyBar.setFontSize(textSizeMedium);

    //screen2 specific ui elements
    planetSeedBox.setPos(100 * gscreenx / 800, 100 * gscreeny / 600);
    planetSeedBox.setFontSize(textSizeMedium);
    randomizeSeedButton.setFontSize(textSizeMedium);
    randomizeSeedButton.setPos(planetSeedBox.posX() + planetSeedBox.sizeX(), planetSeedBox.posY());
    planetSizeSideScroll.setPos(planetSeedBox.posX(), planetSeedBox.posY() + planetSeedBox.sizeY() + getTextYSize(textSizeMedium) + 5); //= sideScroll(planetSeedBox.posX(), planetSeedBox.posY() + planetSeedBox.sizeY() + getTextYSize(textSizeMedium) + 5, textSizeMedium, 10);
    planetSizeSideScroll.setFontSize(textSizeMedium);

    planetTempSlider.setPos(planetSeedBox.posX(), planetSizeSideScroll.posY() + planetSizeSideScroll.sizeY() + getTextYSize(textSizeMedium));
    planetOrbitEccentricity.setPos(planetTempSlider.posX(), planetTempSlider.posY() + planetTempSlider.sizeY() + getTextYSize(textSizeMedium));
    planetAxialTilt.setPos(planetOrbitEccentricity.posX(), planetOrbitEccentricity.posY() + planetOrbitEccentricity.sizeY() + getTextYSize(textSizeMedium));
    planetWaterAbundance.setPos(planetAxialTilt.posX(), planetAxialTilt.posY() + planetAxialTilt.sizeY() + getTextYSize(textSizeMedium));
    planetPopulation.setPos(planetWaterAbundance.posX(), planetWaterAbundance.posY() + planetWaterAbundance.sizeY() + getTextYSize(textSizeMedium));

    //200 * gscreenx / 800, 20 * gscreeny / 600
    planetTempSlider.setSizeX(200 * gscreenx / 800);
    planetTempSlider.setSizeY(20 * gscreeny / 600);

    planetOrbitEccentricity.setSizeX(200 * gscreenx / 800);
    planetOrbitEccentricity.setSizeY(20 * gscreeny / 600);

    planetAxialTilt.setSizeX(200 * gscreenx / 800);
    planetAxialTilt.setSizeY(20 * gscreeny / 600);

    planetWaterAbundance.setSizeX(200 * gscreenx / 800);
    planetWaterAbundance.setSizeY(20 * gscreeny / 600);

    planetPopulation.setSizeX(200 * gscreenx / 800);
    planetPopulation.setSizeY(20 * gscreeny / 600);
}