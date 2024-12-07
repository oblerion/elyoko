
loadmodel("asset/mcube.glb")
loadtexture("asset/icon.png")
loadplanetexture("icon.png") -- use loaded texture for create plane textured model

function torad(deg)
  return deg*(math.pi/180)
end

function help_message(x,y)
  text("wasd / left gamepag stick for move",x,y,20,color(255,255,255))
  text("arrow / mouse / right gamepad stick for rotate camera",x,y+18,20,color(255,255,255))
end

function ELYOKO2D()
  local x,y = mouse()
  rect(3,3,990,60,color(0,0,0))
  help_message(23,10)
  circle(x,y,5,color(255,255,255))
end

function ELYOKO3D()
  cube(0,1,2,5,0.6,0.6,color(255,255,255,80))
  drawmodel("mcube.glb",0,0.5,0,0,5,0)
  drawmodel("mcube.glb",10,0.5,0,0,0,0)
  drawmodel("mcube.glb",0,0.5,10,0,0,0)
  sphere(0,2,2,2,color(255,255,255))
  cube(10,0,10,2,3,2,color(255,0,0))
  drawmodel("icon.png",0,5,0,torad(180),0,0)
end
