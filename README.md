# Texture manager 

## Introduction :

Help support animation management in the Game.

##### Advantages:

- Manage by name (string)

- Simple creation manipulation

- Collision support (normal , cricle , pixel perfect)

- Load texture from file (.xml) <br>
	```xml 
	<textureatlas>
		<texture name={name} path={path_image_source} createmask={sp_collision_perfect} 
			spritesheet={path_data_sprite}>
		</texture>
	</textureatlas>
	```
	Ex: [d_texture.xml](TextureManager/TextureManager/assets/d_texture.xml)<br>
- Load Spritesheet from the xml file 
	```xml 
	<spritesheet>
		<animation name="animation_name">
			<subsprite x="left" y="right" width="widhtRect" height="heighRect" >
				
			</subsprite>
		</animation>
	</spritesheet>
	```
	Example: [human.xml](TextureManager/TextureManager/spritesheets/human.xml)

**PS**: These are just my subjective opinions in the process of capturing and handling events with SFML
## Version :
+ v1.0 
+ v1.1.2
+ v1.1.3
## Content:
##### Version 1.0
	-> Create
	-> Collision

##### Version 1.1.2
	-> Load data texture from the xml file
	-> Update texturemanger
	-> Load spritesheet
	-> Fix collision cricle 
##### Version 1.1.3
	-> Update load intRect texture

## Update : 

## Conclude :
I am not sure it is a good solution. I look forward to contributing to development. Thanks

## References :
- [SFML Game Development By Example](https://www.amazon.com/SFML-Development-Example-Raimondas-Pupius/dp/1785287346)



