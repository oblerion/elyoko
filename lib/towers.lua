require("lib.math")
loadmodel("lib/tower.glb")
loadmodel("lib/tower_inter.glb")
_towers={
	model="tower.glb",
	model_inter="tower_inter.glb",
	list={}
}

function towers_model(name)
	_towers.model=name
end
function towers_add(px,py,pz,pmodel)
	local tower = {model=_towers.model,x=px,y=py,z=pz}
	if pmodel~=nil then
		tower.model=pmodel
	end
	table.insert(_towers.list,tower)
end
function towers_draw()
	for _,v in pairs(_towers.list) do
		if dist(camerax(),cameraz(),v.x,v.z)>9 then
			drawmodel(v.model,v.x,v.y,v.z,0,0,0,1)
		else
			drawmodel(_towers.model_inter,v.x,v.y,v.z,0,0,0,1)
		end
	end
end
