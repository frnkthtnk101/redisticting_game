#https://chrishavlin.com/2016/11/16/shapefiles-tutorial/
#https://gis.stackexchange.com/questions/131716/plot-shapefile-with-matplotlib
#https://stackoverflow.com/questions/30447790/displaying-a-shapefile/48056459#48056459
#https://chrishavlin.com/2016/12/01/shapely-polygons-coloring/
import shapefile
import numpy as np
import csv
from matplotlib import pyplot as plt
from descartes import PolygonPatch
from shapely.geometry import Polygon
sf = shapefile.Reader('/Users/francopettigrosso/ws/redisticting_game/python/shapefiles/tr42_d00')
#first feature of the shapefile
tract_info = []
with open('/Users/francopettigrosso/ws/redisticting_game/python/districts.csv','r') as csvfile:
    reader = csv.DictReader(csvfile)
    for row in reader:
        tract_info.append(row)

colors = [
    '#02ff85',
    '#ff027c',
    '#ff8502',
    '#027cff',
    '#0004ff',
    '#fffb00',
    '#04ff00',
    '#fb00ff',
    '#a5a7ff',
    '#fffea5',
    '#a7ffa5',
    '#fea5ff',
    '#ffacda',
    '#acffd3',
    '#acdaff',
    '#ffd3ac',
    '#ff01fb',
    '#ff0901',
    '#01fbff',
    '#01ff09'

]

print(f'number of shapes imported:{len(sf.shapes())}')
length = len(sf.fields)
for i in range(length):
    print(i,sf.fields[i][0])


plt.figure()
ax = plt.axes()
ax.set_aspect('equal')

    
i = 0
for shaperec in list(sf.iterShapeRecords()):
    shape = shaperec.shape
    rec = shaperec.record
    row = ([i for i in tract_info if int(i['county']) == rec[5] and int(i['tract']) == rec[6] ])
    color= colors[int((row[i]['Districtnum']).replace('-',-1)]
    print(f"TR42_D00: {rec[3]} TR42_D00_I {rec[4]} state: {rec[4]} county: {rec[5]} tract: {rec[6]} Name: {rec[7]}")
    nparts = len(shape.parts)
    if nparts == 1:
        polygon = Polygon(shape.points)
        patch = PolygonPatch(polygon,facecolor=color,alpha=1,zorder=1)
        patch.set_linewidth(None)
        #patch.set_edgecolor('none')
        patch.set_edgecolor(color)
        ax.add_patch(patch)
    else:
        for ip in range(nparts):
            i0=shape.parts[ip]
            if ip < nparts - 1:
                i1 = shape.parts[ip+1]-1
            else:
                i1 = len(shape.points)
            polygon = Polygon(shape.points[i0:i1+1])
            patch = PolygonPatch(polygon,facecolor=color,alpha = 1 , zorder = 1)
            patch.set_linewidth(None)
            #patch.set_edgecolor('none')
            patch.set_edgecolor(color)
            ax.add_patch(patch)
    if (i < 18):
        i+= 1
    else:
        i=0



plt.xlim(-81,-74.5)
plt.ylim(39.7,42.5)
plt.show()