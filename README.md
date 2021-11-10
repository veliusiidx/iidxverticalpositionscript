Automatically repositions the screen depending on if you're in song select, in a song, or if you are trying set options.

Step 1 Make sure you have Bemanitools 5.36, set -p gfx.windowed=true -p gfx.framed=true at the end of your gamestart.bat script.

Step 2 Set your monitor in vertical orientation to 1080x1440.

Step 3 Start game, log in, get to song select, set your pacemaker (you won't be able to see this part of the screen for the remainder of your session).

Step 4 Start the script in admin mode, tab back into the game and it should resize your game to 2560x1440 automatically and do all of the necessary positioning for you automatically. No need for any other application except this one.

Known issues: Trying to set your options may make the game flicker between centering the screen or being stuck on the right side of the screen every 5-10 seconds. It's very inconsistent and I'm not sure what the issue is here exactly so if anyone knows, feel free to make a pull request.
