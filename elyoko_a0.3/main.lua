loadtexture("asset/title_elyoko.png")
loadplanetexture("title_elyoko.png") -- use loaded texture for create plane textured model
require("lib.towers")
require("lib.math")

towers_add(10,0,0)
towers_add(40,0,0)

camerasetpos(0,2,-10)

function help_message(x,y)
  text("wasd / left gamepag stick for move ",x,y,20,color(255,255,255))
  text("arrow / mouse / right gamepad stick for rotate camera",x,y+18,20,color(255,255,255))
end
function ELYOKO2D()
  local x,y = mouse()
  rect(3,3,990,60,color(0,0,0))
  help_message(23,10)
  circle(x,y,5,color(255,255,255))
end

function ELYOKO3D()
  towers_draw()
  drawmodel("title_elyoko.png",0,6,10,torad(90),0,torad(180),0.25)
end
