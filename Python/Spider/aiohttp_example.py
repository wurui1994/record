# time python aiohead.py
import os
from asyncio import Semaphore, ensure_future, gather, get_event_loop
from functools import wraps

from aiohttp import ClientSession


def limit(number):
    sem = Semaphore(number)

    def wrapper(func):
        @wraps(func)
        async def wrapped(*args):
            async with sem:
                return await func(*args)
        return wrapped
    return wrapper


async def download(response):
    url = str(response.url)
    if not url.startswith('http'):
        return

    filename = url.replace('http://', '').replace('https://', '')
    filename = filename.replace(':', '_').replace('?', '_')
    if not filename.endswith('.html'):
        if filename.endswith('/'):
            filename += 'index.html'
        elif not filename.endswith('.jpg'):
            filename += '.html'

    path = os.path.dirname(filename)
    if not os.path.exists(path):
        os.makedirs(path)

    if not os.path.exists(filename):
        print(url)
        data = await response.read()
        with open(filename, 'wb') as f:
            f.write(data)


@limit(32)
async def fetch(url):
    try:
        async with ClientSession() as session:
            async with session.get(url) as response:
                await download(response)
    except:
        print("Error.Try Again")
        await fetch(url)


async def run(urls):
    tasks = [ensure_future(fetch(url)) for url in urls]
    await gather(*tasks)

base = 'https://www.website.com/item/'
urls = [base + str(index) + '.html' for index in range(1, 10000)]
get_event_loop().run_until_complete(ensure_future(run(urls)))
