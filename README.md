# Manis-RunnerGame
 Infinite runner game created as an assignment for Futuregames

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

#### Procedural mesh obstacle
<img src="https://user-images.githubusercontent.com/57400375/233956819-25687f43-464f-47c0-856d-6c2aa569c4f9.jpg" alt="drawing" width="600"/>
One of the obstacle I have is a procedural mesh which creates 3 quads that will form a randomly placed door.
