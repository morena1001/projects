import requests
from bs4 import BeautifulSoup

def getdata (url):
    r = requests.get (url)
    return r.text

htmldata = getdata ("https://x.com/s1120411/status/1900544068356358303")
soup = BeautifulSoup (htmldata, "html.parser")
for item in soup.find_all ('a'):
    print (item)
