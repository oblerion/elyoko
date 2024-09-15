
loadtexture("asset/title_elyoko.png")
loadplanetexture("title_elyoko.png") -- use loaded texture for create plane textured model
loadmodel("asset/7130-snwspeeder_opti.glb")
function torad(deg)
  return deg*(math.pi/180)
end
camerasetpos(0,2,-10)
--camerarotate(0,torad(180),0)

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
  --          string name              ,x,y,z,rx,ry,rz,scale
  drawmodel("7130-snwspeeder_opti.glb",-5,1,0,0,0,0,0.01)
  drawmodel("7130-snwspeeder_opti.glb",0,2,0,0,0,0,0.02)
  drawmodel("7130-snwspeeder_opti.glb",8,3,0,0,0,0,0.03)
  drawmodel("7130-snwspeeder_opti.glb",19,3,0,0,0,0,0.04)
  drawmodel("title_elyoko.png",0,6,10,torad(90),0,torad(180),0.25)
end
