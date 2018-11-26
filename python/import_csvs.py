import csv
with open('census_file_1.csv', 'r') as csvfile:
    reader = csv.reader(csvfile)
    for row in reader:
        print(row[0])
