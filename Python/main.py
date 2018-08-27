# [callable(getattr(__builtins__, attr)) for attr in dir(__builtins__)]
# [(attr,type(getattr(__builtins__, attr))) for attr in dir(__builtins__)]
# print('hello'*100)
class Test:
    def __repr__(self):
        return "test"
        
    def __str__(self):
        return "test2"

t = Test()
print(t)