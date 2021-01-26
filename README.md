<img src="https://github.com/Bram-Pl/Crossy_Road_GBA/blob/master/Images/Extra/GitTitle.png">

## Crossy Road GBA Clone using [GBA-Sprite-Engine](https://github.com/wgroeneveld/gba-sprite-engine)

The GBA-Sprite-Engine on which this game is build can be found via the hyperlink above. And is created by Groeneveld, W., Tielemans, J. and Alfonso, R. The GBA-Sprite-Engine is a high-level object-oriented Gameboy Advance sprite engine library that uses C++ 11 object-oriented approach. The project is forked from this engine.

## Course Information [INFCP_3433]
The course called: "Softwareontwerp met C/C++ [INFCP_3433]" at Hasselt University given by [Groeneveld W.](https://github.com/wgroeneveld) required us to make a GBA game using the above mentioned GBA engine. 
<details>
<summary>Click to see the minimum requirements</summary>

1. The code will be available in a repository on Github under your own username with the [MIT](https://docs.github.com/en/free-pro-team@latest/github/creating-cloning-and-archiving-repositories/licensing-a-repository#disclaimer) license.

2. You'll start from the [GBA-Sprite-Engine](https://github.com/wgroeneveld/gba-sprite-engine) and you will stay within `MODE0` and work with sprites. C++11 is also a requirement.

3. In case you use others people code, use **source reference!** Plagiarism will be punished badly.

4. Your project needs to compile.

5. Your repository `README.md` contains a small functional description of the game.

6. Beside the functional description you'll  also upload a sketch of your **domain model**, in combination with an explanation.

</details>

The source code for our game can be found under `crossy_road` -> `src`.

## Crossy Road

The Crossy Road Gameboy Advanced Edition is based on the very popular Crossy Road game for mobile devices. Try to reach the finish line as quickly as possible by completing a parkour full of obstacles and barriers. Do this in the fastest time possible. Along the way there are some coins you can collect, which will give you a bonus at the end. Can you set the fastest time?

<details>
<summary>Click to see the controls</summary>

* ↑ - Move forward

* → - Move to the right

* ← - Move to the left

</details>

<details>
<summary>Click to see the gameflow</summary>

<img src="https://github.com/Bram-Pl/Crossy_Road_GBA/blob/master/Images/Extra/GameFlowSchematic.png">
</details>

## Domain Model for Crossy Road

<img src="https://github.com/Bram-Pl/Crossy_Road_GBA/blob/master/Images/Extra/DomainModel.png">

*Click on the domain model to get a better and more clear overview.*

### Explanation for each scene
<details>
<summary>HomeStartScene</summary>

At the start of the game, the HomeStartScene gets loaded. This scene is the startmenu of the game. On this scene there are a few clouds that move to make the game feel more alive. The timer implements the movement of the clouds and enables them to move at different speeds. The scene is called using the constructor and loads the sprites and backgrounds into a vector to be displayed. The load method allows this to be done. The tick method gets called every game tick and this tick increases the timer and depending on the value of the timer the clouds move. This method also checks if the “START” button is pressed. If this is the case, this scene gets terminated including all the sprites, backgrounds and palettes. The GameScreen gets loaded.
<p align="center">
<img src="https://github.com/Bram-Pl/Crossy_Road_GBA/blob/master/Images/Extra/HomeStartScene.gif">
</p>
</details>

<details>
<summary>GameScreen</summary>

The GameScreen is the main game environment in which the game is played. The sprites that get loaded in are: car, treeTrunk, coin and bird. These have their own movement abilities. The car gets loaded in and moves in a set direction at a default speed. Multiple cars get loaded into a vector which makes it easier to manage the objects. The tree trunk has the same properties as the car. The coin spawns at default places across the map in a total of four. The bird is the player class which is used to move/navigate across the map.

According to the virtual y position of the bird in the map objects get loaded and unloaded when progress is made. This improves performance. To construct objects, we use the template set for each individual object. For example: “car → someCarSprite”. Every game tick the collision between the bird player and an object. If the bird collides with a coin a sound will be played that notifies the player of a pickup. The number of coins picked up will be increased with every pickup. If the bird collides with a car a tire screech sound will be played and the game will terminate the GameScreen and move on to carCollisionScene. If the bird collides with a tree trunk, the bird will follow along the path of the tree trunk. If the bird misses the treetrunk or moves off of the tree trunk a water drop sound will be played and the GameScreen will be terminated and move on to riverCollisionScene. If the player reaches the end of the map, which is checked using the y position of the bird. The GameScreen gets terminated and the finishScene gets called. 
<p align="center">
<img src="https://github.com/Bram-Pl/Crossy_Road_GBA/blob/master/Images/Extra/GameScreen.gif">
</p>
</details>

<details>
<summary>carCollisionScene</summary>

The car collision scene shows a short animation of the car and the bird moving towards each other. When they collide the bird and car blow up and an explosion occurs including sound effect. If the player presses the “START” button. The game restarts.
<p align="center">
<img src="https://github.com/Bram-Pl/Crossy_Road_GBA/blob/master/Images/Extra/carCollisionScene.gif">
</p>
</details>


<details>
<summary>riverCollisionScene</summary>

The river collision scene shows a short animation of the bird moving towards the water strip in the middle of the screen. When the bird reaches the middle, a water drop sound and animation plays. If the player presses “START” button. The game restarts.
<p align="center">
<img src="https://github.com/Bram-Pl/Crossy_Road_GBA/blob/master/Images/Extra/riverCollisionScene.gif">
</p>
</details>


<details>
<summary>finishScene</summary>

The finish scene shows the end screen which shows the total time the player took to get to the finish line. If the player picked up coins while heading for the finish line, these coins get added up, multiplied by one second and deducts from the total time. The result of this deduction gets shown and is the resulting time.
<p align="center">
<img src="https://github.com/Bram-Pl/Crossy_Road_GBA/blob/master/Images/Extra/finishScene.png">
</p>
</details>

## Authors

* *Wouter Groeneveld*       - Lecturer  - [GitHub](https://github.com/wgroeneveld)
* *Bram Plessers*        - Student   - [GitHub](https://github.com/Bram-Pl)
* *Arne Niesten*   - Student   - [GitHub](https://github.com/arneniesten)

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments
* Groeneveld, W., Tielemans, J. and Alfonso, R. for providing the [GBA-Sprite-Engine](https://github.com/wgroeneveld/gba-sprite-engine) for making the game.
* [Piskel](https://www.piskelapp.com/) for providing the very useful tool for designing our sprites.
* [Grit](https://www.coranac.com/man/grit/html/grit.htm) for converting our images.
* [raw2gba](https://github.com/IanFinlayson/raw2gba) for converting raw music files to header files.