# Manis-RunnerGame
 Infinite runner game created as an assignment for Futuregames
 Target grade: VG
 
 ## Part 2:
 After completing part 1 I started integrating local multiplayer so now the game is a race between the two player. So each player moves in their own lanes and have to out live the other player.
 One player moves with the A and D keys and the other with the left and right arrow keys. I changed my scoring system from being calculated by how long you have survived to how many obstacles you have dodged. This made it easier to implement the second spec change. <br>
After that I implemented all the missing featurs which were:
- High Score (each player has seperate score tracking and different high scores)
- Increasing Difficuly (basically inscreasing speed of players with a cap)
- Proper health management (each player is allowed to get hit 3 times)
- UI (for score and health)
 
 ### What I did for VG:
 #### Procedural mesh obstacle
<img src="https://user-images.githubusercontent.com/57400375/233956819-25687f43-464f-47c0-856d-6c2aa569c4f9.jpg" alt="drawing" width="600"/> <br>
One of the obstacle I have is a procedural mesh which creates 3 quads that will form a randomly placed door. <br>
I use Unreal's UProceduralMeshComponent to construct my own mesh. I calculate the points and extents for the door so it places a point in the bounds of the lane. <br>
![image](https://user-images.githubusercontent.com/57400375/236412583-ede566e3-b14b-46b5-bacd-38439ac527ff.png) <br>
The AddQuad function handles the calculation for the indices of the Triangles plus mapping of UVs and Normals. <br>
![image](https://user-images.githubusercontent.com/57400375/236413100-b6e6a342-1b89-4f4d-ba1f-8684227b3a29.png) <br>

#### Spawning with probabilty instead of complete randomness
I have implemented a probability system for the selection of obstacles. This function takes an array of desiered elements and an array of floats which add up to 1. <br>
This enables me to control how often every obstacle should apear. <br>
![image](https://user-images.githubusercontent.com/57400375/236413797-c697ab48-96b9-48a4-b073-a311a7b5f8cc.png) 

## Part 1:

### What it has:
- Infinte Platform Generation
- Two types of obstacles
  - A moving rock
  - A proceduraly generated door mesh
- Movement (move with AD or mouse)
- Pause Menu (pause with M key)
- 🌻

### What it doesn't have:
- Health
- Increasing dificulty
- Keeping track of high score
- Move varried obstacles


### Bugs:
- if you hit an obstacle the pawn's position will reset and it might appear in a blank space.

### How it works:
#### Spawning platforms
<img src="https://user-images.githubusercontent.com/57400375/233607813-d4cae418-cd44-48c4-ac5b-b8f292a82a63.jpg" alt="drawing" width="600"/>
Everything that is generated on runtime drives from Spawnable. All Spawnables get destroyed after they are to far from the moving player. <br>
The PlatformSpawner spawns a GroundBlock (also a Spawnable) every time the next spawn point is less than 5 meters close to the player. <br>
The GroundBlock spawns a predefined amount of obstacles on top of it self. Choosing an obstacle is controlled by a probability system. <br>
