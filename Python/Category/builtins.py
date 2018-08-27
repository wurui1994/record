
# print([callable(getattr(__builtins__, attr)) for attr in dir(__builtins__)])
print([(attr,type(getattr(__builtins__, attr))) for attr in dir(__builtins__)])
# print 'hello'*100
