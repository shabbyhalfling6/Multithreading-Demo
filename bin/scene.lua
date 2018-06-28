progressive(10)
shadows(true)
ambient(0,0,0)
recursiveLimit(4)
sky(0.1, 0.3, 0.8)
skybox("KKZ5V.bmp")
resolution(1024, 1024)
camera{pos = {0, 0, -10}, lookat = {0, 0, 0}, fov = 0.5}
--camera{pos = {0, 0, -10}, lookat = {0, 0, 0}, ortho = {5, 5}}

light{pos = {4, 15, 0}, colour = {1, 1, 1}}
light{pos = {-10, 3, -3}, colour = {0.7, 0.01, 0.01}}

for i = 0, 1080, 20 do
	sphere{
		radius = 0.8, 
		pos = {math.cos(i/57.29) * 2, i / 170.0 - 4, math.sin(i/57.29)*2},
		diffuse = {0.3, 0.3, 0.3},
		reflective = {0.7, 0.7, 0.7}
	}
end

for y = 0, 29 do
	for x = 0, 29 do
		sphere{
			radius = 0.4,
			pos = {(x - 15)*0.8, -3, (y - 15)*0.8},
			diffuse = {0.3, 0.8, 0.3},
			reflective = {0.05, 0.05, 0.05},
			specular = {0.2, 0.2, 0.2},
			power = 4
		}
	end
end
