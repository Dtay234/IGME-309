FPS  
500 particles \- 435  
5,000 particles \- 7  
50,000 particles \- 1  
500,000 particles \- 0  
5,000,000 particles \- 0

All particles start with a random velocity, lifetime and color. They update their position every frame and are affected by gravity. Over their lifetime, they become more transparent, and when they expire, they are put back to the origin to repeat the process. The particle system class draws each particle in its draw() function using GL\_POINTS. Something I couldn’t figure out is why the particles’ speed depended on the framerate, even though I used deltaTime in my calculations. 