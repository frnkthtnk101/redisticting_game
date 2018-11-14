#!/bin/bash

echo 'simple test of what we can get out of the census api'

key="a240c63f4d5f8800f399ea2bf7219f27a5e11aff"

columns="B00001_001E,B00002_001E"

echo $key



#curl "https://api.census.gov/data/2016/acs/acs5?get=$columns,NAME&for=tract:*&in=state:42&key=$key"p
curl "https://api.census.gov/data/2010/sf1?get=P0010001,P0030002,P0030003,P0030004,P0030005,P0030006,P0030007,P0030008,P0040001,P0130001,P0180002,BLOCK,BLKGRP&for=tract:*&in=state:42&in=county:*&key=$key"
