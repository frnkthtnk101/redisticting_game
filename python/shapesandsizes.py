#https://chrishavlin.com/2016/11/16/shapefiles-tutorial/
#https://gis.stackexchange.com/questions/131716/plot-shapefile-with-matplotlib
#https://stackoverflow.com/questions/30447790/displaying-a-shapefile/48056459#48056459
import shapefile
import numpy as np
from matplotlib import pyplot as plt
from descartes import PolygonPatch
sf = shapefile.Reader('/Users/francopettigrosso/ws/redisticting_game/python/shapefiles/tr42_d00')
#first feature of the shapefile
print(f'number of shapes imported:{len(sf.shapes())}')


plt.figure()
t =plt.gca()
i =1
for shape in list(sf.iterShapes()):
    npoints = len(shape.points)
    nparts = len(shape.parts)
    poly = shape.__geo_interface__
    if i % 6 == 0:
        color = '#663300'
    elif i %5 == 0:
        color = '#663300'
    elif i %4 == 0:
        color = '#663300'
    elif i %3 == 0:
        color = '#cc0066'
    elif i %2 == 0:
        color = '#cc0066'
    else:
        color = '#cc0066'
    i+=1
    t.add_patch(PolygonPatch(poly, facecolor=[0,0,0.5],edgecolor=[0,0,0], alpha=0.7, zorder=2))
    t.axis('equal')
    if nparts == 1:
        x_lon = np.zeros((len(shape.points),1))
        y_lat = np.zeros((len(shape.points),1))
        for ip in range(len(shape.points)):
            x_lon[ip] = shape.points[ip][0]
            y_lat[ip] = shape.points[ip][1]
        plt.plot(x_lon,y_lat)
    else:
        for ip in range(nparts):
            i0=shape.parts[ip]
            if ip < nparts-1:
                i1 = shape.parts[ip+1]-1
            else:
                i1 = npoints
            seg = shape.points[i0:i1+1]
            x_lon = np.zeros((len(seg),1))
            y_lat = np.zeros((len(seg),1))
            for ip in range(len(seg)):
                x_lon[ip] = seg[ip][0]
                y_lat[ip] = seg[ip][1]

        plt.plot(x_lon,y_lat)
plt.show()