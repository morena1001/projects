import requests
from bs4 import BeautifulSoup

r = requests.get('https://x.com/s1120411/status/1900544068356358303')

soup = BeautifulSoup(r.content, 'html.parser')

s = soup.find ('div', class_='css-175oi2r')
content = soup.find_all ('p')

print(content)
print(r)

