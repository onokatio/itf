from dataclasses import dataclass

class Expression:
    pass

@dataclass
class BinExp(Expression):
    op: str
    left: Expression
    right: Expression

@dataclass
class Leaf(Expression):
    value: int

def evaluate(exp: Expression) -> Leaf:
    if isinstance(exp, BinExp):
        l = evaluate(exp.left).value
        r = evaluate(exp.right).value
        if exp.op == '+':
            return Leaf(l + r)
        elif exp.op == '-':
            return Leaf(l - r)
        elif exp.op == '*':
            return Leaf(l * r)
        elif exp.op == '/':
            return Leaf(l // r)
        else:
            raise Exception("Unknown op: " + exp.op)
    elif isinstance(exp, Leaf):
        return exp
    else:
        raise Exception("Unknown expression: " + str(exp))

test_exp1: Expression = BinExp('/',
                            BinExp('*', 
                                Leaf(2),
                                BinExp('-', Leaf(5), Leaf(2))),
                            Leaf(4))
test_exp2: Expression = BinExp('*', 
                            BinExp('+', Leaf(1), Leaf(2)),
                            BinExp('+', Leaf(3), Leaf(4)))

print(evaluate(test_exp1))
print(evaluate(test_exp2))