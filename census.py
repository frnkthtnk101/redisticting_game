import requests
key="a240c63f4d5f8800f399ea2bf7219f27a5e11aff"
#https://api.census.gov/data/2010/dec/sf1 #October 31st
url1 ='https://api.census.gov/data/2000/sf1?get='+\
'STATE'+\
',TRACT'+\
',AREALAND'+\
',POP100'+\
',H001001'+\
',H002001'+\
',H002005'+\
',H003001'+\
',H003002'+\
',H003002'+\
',P001001'+\
',P002001'+\
',P002002'+\
',P002005'+\
',P003001'+\
',P003002'+\
',P003003'+\
',P003004'+\
',P003005'+\
',P003006'+\
',P003007'+\
',P003008'+\
',P003009'+\
',P003010'+\
',P003026'+\
',P003047'+\
',P003063'+\
',P003070'+\
',P004001'+\
',P004002'+\
',P004003'+\
',P012001'+\
',P012002'+\
',P012026'+\
',P012A001'+\
f'&for=tract:*&in=state:42&key={key}'

url2 ='https://api.census.gov/data/2000/sf1?get='+\
'STATE'+\
',TRACT'+\
',P012A002'+\
',P012A026'+\
',P012B001'+\
',P012B002'+\
',P012B026'+\
',P012C001'+\
',P012C002'+\
',P012C026'+\
',P012D001'+\
',P012D002'+\
',P012D026'+\
',P012E001'+\
',P012E002'+\
',P012E026'+\
',P012F001'+\
',P012F002'+\
',P012F026'+\
',P012G001'+\
',P012G002'+\
',P012G026'+\
',P012H001'+\
',P012H002'+\
',P012H026'+\
',P012I001'+\
',P012I002'+\
',P012I026'+\
',P013001'+\
',P013A001'+\
',P013B001'+\
',P013C001'+\
',P013D001'+\
',P013E001'+\
',P013F001'+\
',P013G001'+\
',P013H001'+\
',P013I001'+\
f'&for=tract:*&in=state:42&key={key}'

response1 = requests.get(url1)
data1 = response1.json()
response2 = requests.get(url2)
data2 = response2.json()

limit = len(data1)
for i in range(1,limit):
    if data1[i][1] != data2[i][1]:
        print("bad!")