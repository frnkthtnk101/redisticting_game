import csv
import pyodbc

server = 'Driver={ODBC Driver 13 for SQL Server};Server=tcp:drexelcensus.database.windows.net,1433;Database=census_database;Uid=luigi@drexelcensus;Pwd=Itwillbe@b@dd@yInhellIfwef@il10105959;Encrypt=yes;TrustServerCertificate=no;Connection Timeout=30;'
cnxn = pyodbc.connect(server)
cursor = cnxn.cursor()


with open('/Users/francopettigrosso/ws/redisticting_game/python/census_file_1.csv', 'r') as csvfile:
    reader = csv.reader(csvfile)
    next(reader,None)
    for row in reader:
        limit = len(row)
        attribute_limit = limit - 2
        sqlstatement='INSERT INTO census_table_1 VALUES('
        for j in range(0,attribute_limit):
                sqlstatement+= row[j]
                if j < attribute_limit-1:
                        sqlstatement += ','
        sqlstatement+=')'
        cursor.execute(sqlstatement)
        cursor.commit()
    
with open('/Users/francopettigrosso/ws/redisticting_game/python/census_file_2.csv','r') as csvfile:
    reader = csv.reader(csvfile)
    next(reader,None)
    for row in reader:
        limit = len(row)
        attribute_limit = limit - 2
        sqlstatement='INSERT INTO census_table_2 VALUES('
        for j in range(0,attribute_limit):
                sqlstatement+= row[j]
                if j < attribute_limit-1:
                        sqlstatement += ','
        sqlstatement+=')'
        cursor.execute(sqlstatement)
        cursor.commit() 