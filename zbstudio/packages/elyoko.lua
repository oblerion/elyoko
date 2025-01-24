local name = "ELYOKO"
local interpreter={}
local api={}
local win = ide.osname == "Windows"
local mac = ide.osname == "Macintosh"

interpreter = {
  name = "ELYOKO",
  description = "3d game egine, ",
  api = {name,"baselib"},
  frun = function(self,wfilename,rundebug)
    local projdir = self:fworkdir(wfilename)
    if win==true then
      return CommandLineRun("elyoko.exe "..wfilename:GetFullPath(),projdir)
    elseif mac==true then
      return CommandLineRun("wine ".."elyoko.exe "..wfilename:GetFullPath(),projdir)
    else
      return CommandLineRun("./elyoko "..wfilename:GetFullPath(),projdir)
    end
  end
}


api = {
	egba={
	description = "ELYOKO functions.",
	 	type = "lib",
	 	version = "a0.2"
	},
  ELYOKO2D={
    args="()",
    description="loop 2d function, call 60/secs",
    returns="()",
    type="function"
  },
  ELYOKO3D={
    args="()",
    description="loop 3d function, call 60/secs",
    returns="()",
    type="function"
  },
  deltatime={
    args="()",
    description="get time between 2 frame",
    returns="(dt:number)",
    type="function"
  },
  color={
    args="(r:number, g:number, b:number, ?a:number=255)",
    description="create color number",
    returns="(icolor:number)",
    type="function"
  },
  getcamerax={
    args="()",
    description="get camera x",
    returns="(x:number)",
    type="function"
  },
  getcameray={
    args="()",
    description="get camera y",
    returns="(y:number)",
    type="function"
  },
  getcameraz={
    args="()",
    description="get camera z",
    returns="(z:number)",
    type="function"
  },
  
  cameramove={
    args="(x:number, y:number, z:number)",
    description="move camera",
    returns="()",
    type="function"
  },
  camerarotate={
    args="(x:number, y:number, z:number)",
    description="rotate camera in radiant",
    returns="()",
    type="function"
  },
  camerasettarget={
    args="(x:number, y:number, z:number)",
    description="set camera look",
    returns="()",
    type="function"
  },
  cameralock={
    args="(state:bool)",
    description="state=true -> camera not move/rotate",
    returns="()",
    type="function"
  },
  
  loadmodel={
    args="(path:string)",
    description="load model (obj,glb) with path",
    returns="()",
    type="function"
  },
  loadtexture={
    args="(path:string)",
    description="load texture with path",
    returns="()",
    type="function"
  },
  loadplanetexture={
    args="(texture_file:string)",
    description="load plane model with texture",
    returns="()",
    type="function"
  },
  
  btn={
    args="(id:number)",
    description="key is down",
    returns="()",
    type="function"
  },
  btnp={
    args="(id:number)",
    description="key is pressed",
    returns="()",
    type="function"
  },
  mouse={
    args="()",
    description="get mouse",
    returns="(x:number, y:number, btnl:bool, btnm:bool, btnr:bool)",
    type="function"
  },
  
  pix={
    args="(x:number,y:number,idcolor:number)",
    description="draw pixel in x y with idcolor",
    returns="()",
    type="function"
  },
  rect={
    args="(x:number,y:number,width:number,height:number,idcolor:number)",
    description="draw fill rectangle in x y with size width/height and idcolor",
    returns="()",
    type="function"
  },
  rectb={
    args="(x:number,y:number,width:number,height:number,idcolor:number)",
    description="draw line rectangle in x y with size width/height and idcolor",
    returns="()",
    type="function"
  },
  circle={
    args="(x:number,y:number,radius:number,icolor:number)",
    description="draw fill circle with color()",
    returns="()",
    type="function"
  },
  circleb={
    args="(x:number,y:number,radius:number,icolor:number)",
    description="draw line circle with color()",
    returns="()",
    type="function"
  },
  text={
    args="(text:string,x:number,y:number,fontsize:number,idcolor:number,)",
    description="print text in x y with idcolor and fontsize",
    returns="()",
    type="function"
  },
  deltexture={
    args="(file:string)",
    description="unload texture",
    returns="()",
    type="function"
  },
  drawtexture={
    args="(file:string,x:number,y:number)",
    description="draw texture",
    returns="()",
    type="function"
  },
  
  cube={
    args="(x:number,y:number,z:number,width:number,height:number,depth:number,icolor:number)",
    description="draw cube",
    returns="()",
    type="function"
  },
  sphere={
    args="(x:number,y:number,z:number,radius:number,icolor:number)",
    description="draw sphere",
    returns="()",
    type="function"
  },
  delmodel={
    args="(file:string)",
    description="unload model",
    returns="()",
    type="function"
  },
  drawmodel={
    args="(file:string,x:number,y:number,z:number,rotx:number,roty:number,rotz:number,scale:number)",
    description="draw model",
    returns="()",
    type="function"
  },
-----------------------------------------
}

-- only copy relevant Lua functions and ones I don't know anything about
local lua = dofile("api/lua/baselib.lua")
-- @see TIC-80/luaapi.c:initLua
local included = {coroutine=true, table=true, string=true, math=true, debug=true}

for item, def in pairs(lua) do
  if included[item] then
    api[item] = def
  end
end

-- package EGBA
return {
  name = name,
  description = "Implements integration with ELYOKO.",
  author = "oblerion",
  version = 0.1,
  onRegister = function(self)
    ide:AddInterpreter(name, interpreter)
    ide:AddAPI("lua", name, api)
  end,
  onUnRegister = function(self)
    ide:RemoveInterpreter(name)
    ide:RemoveAPI("lua", name)
  end,
}
