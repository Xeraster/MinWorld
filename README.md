Here is a simple project i've been working on. It is a seed based world generator also with the ability to spawn animals, plants and buildings.

<del>Note that the speed is currently linked to your framerate with no frame limiter.</del> Now there is a rudimentary frame limiter. If your monitor's refresh rate is equal tp 60fps, the game will target 60fps. If the refresh rate is higher than 60fps, the framerate is limited to 62.5 fps. I haven't found a way to count time increments smaller than 1 millisecond yet and 60fps means 1 frame every 16.6667 ms.

Also note there is no time ticking feature yet and all spawnable things don't interact with anything.

# Dependencies:

SDL2

SDL_ttf

SDL_image

Pthread

I don't know if they make linux distros without pthread so you shouldn't have to install that. For the others, just search for how to install them in your distro. It's theoretically possible to run this on Windows but I've never tried to run any of my SDL or pthread projects on Windows before.

# Tips for getting it to actually run and not crash:
when creating a new world, be sure to press the "randomize" button before clicking next or it will crash

since the game speed is linked directly to the framerate, if your monitor refresh rate is really high, you may be skipping entire menus without noticing. If all you ever get are crashes, try clicking on the buttons fast enough that you aren't instantly clicking whatever button is in that spot on the next screen.

don't go outside the world bounds

don't try to go to a z level lower than -50 or higher than 50

# Controls:
wasd to move around, m to toggle map mode. ~tilde to open the console (which has no useful commands in it yet), hold left or right ctrl (I forgot which) while turing the mouse wheel to change z levels. Mouse wheel without holding control to zoom in or out.
