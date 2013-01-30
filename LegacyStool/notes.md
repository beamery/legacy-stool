CS 559 Project 1 Notes

Basic Flow of Rendering
-------------------------- 
- Scene is initialized with a given number of stools. (some randomly placed, some not?)
- Scene initializes each stool with a position, relative to the floor's grid
- main does camera setup and transformations
  - calls Scene to render the scene
- Scene renders Floor
  - Keep the transforms for Floor when rendering Stools
- Scene then renders Stools, using the positions as offsets on the Floor


Possible Extras
---------------
- Move camera with mouse