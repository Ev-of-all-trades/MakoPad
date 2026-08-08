# MakoPad
This is a 6 key macropad that I designed in KiCad and is programmed with QMK. It features a 2.8" LCD display, 6 hot-swappable keys, a rotary encoder, and 2 buttons to switch the layers. This Project has been made specially for Rohan Patel and Cyrus Contractor to help them with FRC Programming. 

PCB and Schematic
-----------------------------------------------------
<img width="2078" height="1543" alt="image" src="https://github.com/user-attachments/assets/92ee47e6-2d54-49a4-b359-50bd2f3b2339" />
<img width="3107" height="1631" alt="image" src="https://github.com/user-attachments/assets/62b76fd1-a980-49db-94bc-8498295702bf" />

Below is are pictures of some of the assemblies I made in Fusion 360.
------------------------------------------------------------------------------------
PCB Assembly
<img width="2263" height="1373" alt="image" src="https://github.com/user-attachments/assets/aed1f652-3dd8-4e57-ba46-faaf52856536" />

Full PCB Assembly [mind the crappy screen model, i couldn't find a better one since there wasn't any for the specific onw i wanted to use]
<img width="2356" height="1253" alt="image" src="https://github.com/user-attachments/assets/54f817a4-e1f1-4183-9e54-34b0d2069917" />

Here is the plan for developing the programming
--------------------------------------------------
Phase 1: Keyboard matrix
> Program the keyboard matrix and build the layers
> Test matrix to make sure it works

Phase 2: Rotary encoder
> Add the rotary encoder and rotary encoder switch into the programming
> Program the special functions for the rotary encoder
  - Make it so that whenever the rotary encoder is pressed down, you can rotate the knob to select what function you want to rotary encoder to do
> Test rotation and clicking

Phase 3: Layer buttons
> Program the button to change the keyboard matrix layers
  - The top button switches to the next layer and the bottom one switches to the previous layer

Phase 4: The display
> Make the display interface with the microcontroller

Phase 5: Make it awesome
> Layer-dependent key labels
> Encoder modes
> Custom macros
> Startup screen
> MakoPad logo
> Current layer display
> Key function display
