progressive(10)
shadows(false)
ambient(0.0,0.0,0.0)
recursiveLimit(4)
sky(0.1, 0.3, 0.8)
skybox("KKZ5V.bmp")
resolution(1024, 1024)

--camera{pos = {0, 0, -10}, lookat = {0, 0, 0}, ortho = {5, 5}}

light{pos = {4, 10, -5}, colour = {1.5, 1.5, 1.5}}
light{pos = {-10, 3, -3}, colour = {0.8, 0.01, 0.01}}

file = io.open("mesh.points","r")
l = file:read("*l")
print(l)
count = tonumber(l)
ax=0
ay=0
az=0
p={}

for i = 1,count do
	x = tonumber(file:read("*l"))
	y = tonumber(file:read("*l"))
	z = tonumber(file:read("*l"))
	r = tonumber(file:read("*l"))
	g = tonumber(file:read("*l"))
	b = tonumber(file:read("*l"))
	p[i]={x,y,z,r,g,b,0.01}
	ax=ax+x
	ay=ay+y
	az=az+z
	--print(l)
end

--for i = 1,count do
--	m=1000
--	for j = 1,count do
--		if i~=j then
--			dx = p[i][1]-p[j][1]
--			dy = p[i][2]-p[j][2]
--			dz = p[i][3]-p[j][3]
--			d = math.sqrt(dx*dx+dy*dy+dz*dz)
--			if d<m then
--				m=d
--			end
--		end
--	end
--	p[i][7] = m
	--print(i)
--end

for i = 1,count do
	sphere{
		radius = p[i][7] *2, 
		pos = {-p[i][1],p[i][2],p[i][3]},
		diffuse = {p[i][4], p[i][5], p[i][6]},
		specular = {0.05,0.05,0.05},
		reflective = {0.1, 0.1, 0.1}
	}
end


ax=ax/count
ay=ay/count
az=az/count

camera{pos = {ax, ay+1, az-3}, lookat = {ax, ay, az}, fov = 0.5}