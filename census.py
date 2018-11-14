import requests
key="a240c63f4d5f8800f399ea2bf7219f27a5e11aff"

response = requests.get(f'https://api.census.gov/data/2010/sf1?get=P0010001,P0030002,P0030003,P0030004,P0030005,P0030006,P0030007,P0030008,P0040001,P0130001,P0180002,BLOCK,BLKGRP&for=tract:*&in=state:42&in=county:*&key={key}')
print(response.text)