# 仮想マシンの命令
# Push, Add, Sub, Mul, Div

def execute(code):
    stack = []
    pc = 0
    while pc < len(code):
        print("({}, {})".format(code[pc:], stack))
        op = code[pc]
        pc = pc + 1
        if op == "Push":
            operand = code[pc]
            pc = pc + 1
            stack.append(operand)
        elif op == "Add":
            n1 = stack.pop()
            n2 = stack.pop()
            stack.append(n2 + n1)
        elif op == "Sub":
            n1 = stack.pop()
            n2 = stack.pop()
            stack.append(n2 - n1)
        elif op == "Mul":
            n1 = stack.pop()
            n2 = stack.pop()
            stack.append(n2 * n1)
        elif op == "Div":
            n1 = stack.pop()
            n2 = stack.pop()
            stack.append(n2 / n1)
    print(stack[-1])   # -1は「いちばん後ろの要素」

# (1 + 2) * (4 / 2) = 2 * 3 = 6

execute(["Push", 1, "Push", 2, "Add", "Push", 4, "Push", 2, "Div", "Mul"])
