# f(x,y)=x+y
# function test(a,b)
#     return a+b
# end
# println(f(2,3),f(4,5))
# println(test(3,3))

# using Plots
# display(plot([sin,cos],0, 2*pi))
# using Random

# using GLMakie
# GLMakie.activate!()
# function scatters_in_3D()
#     seed!(123)
#     xyz = randn(10, 3)
#     x, y, z = xyz[:, 1], xyz[:, 2], xyz[:, 3]
#     fig = Figure(resolution=(1600, 400))
#     ax1 = Axis3(fig[1, 1]; aspect=(1, 1, 1), perspectiveness=0.5)
#     ax2 = Axis3(fig[1, 2]; aspect=(1, 1, 1), perspectiveness=0.5)
#     ax3 = Axis3(fig[1, 3]; aspect=:data, perspectiveness=0.5)
#     scatter!(ax1, x, y, z; markersize=50)
#     meshscatter!(ax2, x, y, z; markersize=0.25)
#     hm = meshscatter!(ax3, x, y, z; markersize=0.25,
#         marker=FRect3D(Vec3f(0), Vec3f(1)), color=1:size(xyz)[2],
#         colormap=:plasma, transparency=false)
#     Colorbar(fig[1, 4], hm, label="values", height=Relative(0.5))
#     fig
# end
# scatters_in_3D()
using GLMakie
GLMakie.activate!() # hide
scene = Scene()
Makie.inline!(true) # hide

f = Figure()
Axis3(f[1, 1], aspect=(0.5,0.5,1), perspectiveness=0.75)

xs = ys = LinRange(-0.5, 0.5, 100)
zs = [sqrt(x^2+y^2) for x in xs, y in ys]

contour3d!(xs, ys, -zs, linewidth=2, color=:blue2)
contour3d!(xs, ys, +zs, linewidth=2, color=:red2)
f
scene

# using Plots
# gui()
# gr()
# unicodeplots()
# plot(rand(10,2))
# mainloop()
# sleep(30)
# readline()