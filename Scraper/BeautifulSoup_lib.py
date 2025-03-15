import requests
from bs4 import BeautifulSoup

r = requests.get('https://www.geeksforgeeks.org/python-programming-language/')

print(r)

soup = BeautifulSoup(r.content, 'html.parser')
print(soup.prettify())
