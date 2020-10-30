# Master's Degree in Video game programming at U-Tad
## Software Engineering

*Final practice for Software Engineering subject.*

This practice consists in a simple **1D Game** but with the particularity that it has to be very carefully structured.
For this purpose I've chosen a **component based architecture**, in which every entity is formed by several components and the type of the components in an entity is what makes it different from others. To keep all components updated there's a **messaging system** that allows a component to pass a message to the rest using the entity to broadcast it.
In order to control the logic and the render of the game I've created a singleton manager called **world** and another called **graphics** respectively.

