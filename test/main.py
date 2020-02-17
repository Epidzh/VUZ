import ast
import _ast

with open('source.py', 'r') as file:
    tree = ast.parse(file.read())
    print(ast.dump(tree))
    for i in ast.walk(tree):
        #print(i)
        #print(type(i))
        if type(i) is ast.ImportFrom:
            print("import; module=", i.module)
        elif type(i) is ast.alias:
            print("alias; name=", i.name)
        elif type(i) is ast.Module:
            print("length=", len(i.body))