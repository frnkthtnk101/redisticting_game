import csv
tract_info=[]
with open('/Users/francopettigrosso/ws/redisticting_game/python/districts.csv','r') as csvfile:
    reader = csv.DictReader(csvfile)
    for row in reader:
        tract_info.append(row)
print(tract_info[0].keys())
row = ([i for i in tract_info if int(i['Districtnum']) == 1 and int(i['tract']) == 7 ])
print(row[0]['Districtnum'])