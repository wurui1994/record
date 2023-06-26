import threading
def loop(arg):
    while True:
        print(arg)

t1 = threading.Thread(target=loop, args=("t1",))
t2 = threading.Thread(target=loop, args=("t2",))
t1.start()
t2.start()