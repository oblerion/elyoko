function torad(deg)
  return deg*(math.pi/180)
end

function dist(x,y,x2,y2)
	return math.abs(y2-y) + math.abs(x2-x)
end

function collide2d(x,y,w,h,x2,y2,w2,h2)
	return (x<x2+w2) and (y<y2+h2) and (x2<x+w) and (y2<y+h)
end


