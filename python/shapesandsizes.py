import shapefile
import numpy as np
import matplotlib as plt
sf = shapefile.Reader('/Users/francopettigrosso/ws/redisticting_game/python/shapefiles/tr42_d00')
#first feature of the shapefile
print(f'number of shapes imported:{len(sf.shapes())}')

shape_ex = sf.shape(5)

x_lon = np.zeros((len(shape_ex.points),1))
y_lat = np.zeros((len(shape_ex.points),1))
for ip in range(len(shape_ex.points)):
    x_lon[ip] = shape_ex.points[ip][0]
    y_lat[ip] = shape_ex.points[ip][1]

plt.pyplot.plot(x_lon,y_lat)