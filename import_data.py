import pyodbc
import csv

server = 'Driver={ODBC Driver 13 for SQL Server};Server=tcp:drexelcensus.database.windows.net,1433;Database=census_database;Uid=luigi@drexelcensus;Pwd=Itwillbe@b@dd@yInhellIfwef@il10105959;Encrypt=yes;TrustServerCertificate=no;Connection Timeout=30;'
cnxn = pyodbc.connect(server)
cursor = cnxn.cursor()

 
 #read in tract information
#cursor.execute('TRUNCATE TABlE tracts')
#cursor.commit()
cursor.execute('TRUNCATE TABlE nlist_2000')
cursor.commit()
'''with open('/Users/francopettigrosso/Desktop/tract00co/tract_2000.csv') as csvfile:
    reader = csv.reader(csvfile,delimiter = ',')
    next(reader)
    i = 0
    information = []
    print('getting information')
    for row in reader:
        information.append(f'INSERT INTO tracts (gisjoin,state,county,tract,fid) VALUES(\'{row[0]}\',{row[2]},{row[3]},{row[4]},{row[5]})')
    info_length = len(information)
    print('upload information')
    while i < info_length:
        cursor.execute(information.pop(0))
        cursor.commit()'''
 #read in adjanceties
with open('/Users/francopettigrosso/Desktop/tract00co/nlist_2000.csv') as csvfile:
    reader = csv.reader(csvfile,delimiter = ',')
    next(reader)
    i = 0
    information = []
    print('getting information')
    for row in reader:
        information.append(f'INSERT INTO nlist_2000 (fid,nid) VALUES({row[0]},{row[1]})')
    info_length = len(information)
    print('upload information')
    while i < info_length:
        cursor.execute(information.pop(0))
        cursor.commit()
print('[DONE]')